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

#include <secrets.h>

static DHT_Unified g_dht(D4, DHT11);

void initSerialPort(HardwareSerial& serial);
void initWifi(ESP8266WiFiClass& wifi,
              const String& ssid,
              const String& password);
void initDhtSensor(DHT_Unified& dht);

void setup()
{
  initSerialPort(Serial);
  initWifi(WiFi, getSSID(), getPassword());
  initDhtSensor(g_dht);
}

void loop()
{
}

void initSerialPort(HardwareSerial& serial)
{
  serial.begin(115200);
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
