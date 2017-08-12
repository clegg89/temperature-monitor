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
#include "root-ca.hpp"
#include "verified-wifi-client.hpp"

static DHT_Unified g_dht(D4, DHT11);
static VerifiedWifiClient g_client(RootCaCertificate);

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
