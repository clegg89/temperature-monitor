/*
 * @file network-health-task.cpp
 *
 * @author C. Smith
 */

#include "network-health-task.hpp"

#include <Esp.h>
#include <ESP8266WiFi.h>
#include <time.h>

#include "root-ca.hpp"
#include "wifi-information.hpp"
#include "mqtt-broker-information.hpp"

namespace app
{

uint32_t NetworkHealthTask::clientIdCount = 0;

NetworkHealthTask::NetworkHealthTask(const uint32_t timeInterval)
  : Task(timeInterval), m_wifiClient(RootCaCertificate),
    m_logger(Serial), m_mqttNetwork(m_wifiClient, m_system),
    m_mqttClient(std::make_shared<MqttClient>(m_mqttOptions, m_logger,
          m_system, m_mqttNetwork, m_sendBuffer, m_recvBuffer, m_msgHandlers))
{
  m_mqttOptions.commandTimeoutMs = 10 * 1000;
  m_mqttClientId = String(ESP.getChipId()) + String(clientIdCount++);
}

NetworkHealthTask::~NetworkHealthTask()
{
  clientIdCount--;
}

bool NetworkHealthTask::OnStart()
{
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  while(WiFi.status() != WL_CONNECTED)
  {
    connectWifi();
  }

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

  connectNetwork();
  
  if(m_wifiClient.connected())
  {
    connectMqtt();
  }

  return true;
}

void NetworkHealthTask::OnStop()
{
}

void NetworkHealthTask::OnUpdate(uint32_t deltaTime)
{
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi disconnected. Reconnect.");
    connectWifi();
  }
  else if(!m_wifiClient.connected())
  {
    Serial.println("Client disconnected. Reconnect.");
    connectNetwork();
  }
  else if(!m_mqttClient->isConnected())
  {
    Serial.println("MQTT disconnected. Reconnect.");
    connectMqtt();
  }
}

void NetworkHealthTask::connectWifi()
{
  for(auto info : g_wifiNetworks)
  {
    uint32_t count = 0;
    const uint32_t failureCount = 10;

    WiFi.begin(info.ssid.c_str(), info.password.c_str());

    Serial.print("Connecting to ");
    Serial.print(info.ssid);

    while(WiFi.status() != WL_CONNECTED &&
          count++ < failureCount)
    {
      delay(500);
    }

    if(WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Connected");
      return;
    }
    else
    {
      Serial.println("Failed to connect, try next network");
    }
  }

}

void NetworkHealthTask::connectNetwork()
{
  const char * host = g_brokerInformation.hostname.c_str();
  const int port = g_brokerInformation.port;

  Serial.print("Connecting to ");
  Serial.println(host);

  if(!m_wifiClient.connect(host, port))
  {
    Serial.println("Connection failed");
  }
  else
  {
    Serial.println("Connection succeeded");
  }
}

void NetworkHealthTask::connectMqtt()
{
  MqttClient::ConnectResult connectionResult;
  MqttClient::Error::type result;
  MQTTPacket_connectData options = MQTTPacket_connectData_initializer;

  options.MQTTVersion = 4;
  options.clientID.cstring = const_cast<char*>(m_mqttClientId.c_str());
  options.cleansession = true;
  options.keepAliveInterval = 30; // seconds
  options.username.cstring = const_cast<char*>(g_brokerInformation.username.c_str());
  options.password.cstring = const_cast<char*>(g_brokerInformation.password.c_str());

  Serial.println("Connecting to MQTT Broker");

  result = m_mqttClient->connect(options, connectionResult);

  if(result != MqttClient::Error::SUCCESS)
  {
    Serial.print("Error connecting to broker: ");
    Serial.println(result);
  }
}

}
