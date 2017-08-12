/*
 * @file main.cpp
 *
 * @author C. Smith
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <time.h>

#include "wifi-information.hpp"

/*
 * TODO I'm not fond of this solution. It will work for now.
 *
 * These are binary representations of the Root CA certificate and it's
 * length (the Root CA is required, and should be self-signed). To obtain
 * the Root CA, use openssl to find the issure of the last Certificate in
 * the chain sent by the client:
 *    
 *    openssl s_client -showcerts -connect ${SERVERNAME}:${SERVERPORT} < /dev/null 2> /dev/null | \
 *      openssl x509 -noout -text
 *
 * The issuer of the last certificate should be the Root CA. For example
 * "Addtrust External CA Root." The certificate should be somewhere on your
 * system (location will vary). You can typically export it from your browser
 * in some fashion. You will want to get the certificate into DER form. If it
 * is in PEM format you can use the following command:
 *
 *    openssl x509 -in ${ROOTCA}.pem -out ${ROOTCA}.der -outform DER
 *
 * Finally you can create a C file which will contain the array and length
 * using xxd -i:
 *
 *    xxd -i ${ROOTCA}.der > ca-certificate.c
 *
 * Change the name of the array and length to the names below and place
 * the file in the src directory (same directory as this file).
 *
 * Possible future improvements:
 *   - Automating at least a portion of the process. It would be difficult
 *     to automate obtaining the Root CA as that varies based on browser
 *     and system.
 *   - Using SPIFFS to store the CA certificate, allowing for certificate
 *     updates without the need to upgrade the entire firmware.
 */
extern const unsigned char ca_certificate[];
extern const uint32_t ca_certificate_len;

static DHT_Unified g_dht(D4, DHT11);
static WiFiClientSecure g_client;

void initSerialPort(HardwareSerial& serial, const bool enableDebug);
void initWifi(ESP8266WiFiClass& wifi,
              const String& ssid,
              const String& password);
void initDhtSensor(DHT_Unified& dht);

void setup()
{
  const WifiInformation& wifiInfo = WifiInformation::instance();
  initSerialPort(Serial, false);
  initWifi(WiFi, wifiInfo.ssid(), wifiInfo.password());
  initDhtSensor(g_dht);

  Serial.print("Configure time..");
  /* Need to synchronize time so TLS can verify certificates */
  /* First parameter is offset from GMT, second is daylight savings (ignored,
   * and then servers (up to three, minimum two).
   */
  configTime(-(4*3600), 1, "pool.ntp.org", "time.nist.gov");

  /* Wait until we have the current time */
  time_t now = time(nullptr);
  while (now < 1000)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println(" Done");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.println(asctime(&timeinfo));

  Serial.println("Set CA Cert");
  if (!g_client.setCACert(ca_certificate, ca_certificate_len ))
  {
    Serial.println("Failed to load CA certificate");
    while(true) yield();
  }
  Serial.println("CA Cert set");
}

void loop()
{
  const char * host = "m10.cloudmqtt.com";
  const int port = 28367;

  Serial.print("Connecting to ");
  Serial.println(host);
  if(!g_client.connect(host, port))
  {
    Serial.println("Connection failed");
    return;
  }

  if(g_client.verifyCertChain(host))
  {
    Serial.println("Server certificate verified");
  }
  else
  {
    Serial.println("ERROR: certificate verification failed!");
    return;
  }

  g_client.stop();
}

void initSerialPort(HardwareSerial& serial, const bool enableDebug)
{
  serial.begin(115200);
  serial.setDebugOutput(enableDebug);
  delay(10);
}

void initWifi(ESP8266WiFiClass& wifi,
              const String& ssid,
              const String& password)
{
  wifi.begin(ssid.c_str(), password.c_str());

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while(wifi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("Connected");
}

void initDhtSensor(DHT_Unified& dht)
{
  dht.begin();
  Serial.println("DHT Initialized");

  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
}
