/*
 * @file main.cpp
 *
 * @author C. Smith
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <secrets.h>

void initSerialPort(HardwareSerial& serial);
void initWifi(ESP8266WiFiClass& wifi,
              const String& ssid,
              const String& password);

void setup()
{
  initSerialPort(Serial);
  initWifi(WiFi, getSSID(), getPassword());
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
