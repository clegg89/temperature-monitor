/*
 * @file network-health-task.cpp
 *
 * @author C. Smith
 */

#include "network-health-task.hpp"

#include <ESP8266WiFi.h>
#include <time.h>

#include "root-ca.hpp"
#include "wifi-information.hpp"

namespace app
{

NetworkHealthTask::NetworkHealthTask(const uint32_t timeInterval)
  : Task(timeInterval), m_client(RootCaCertificate)
{
}

bool NetworkHealthTask::OnStart()
{
  const WifiInformation& wifiInfo = WifiInformation::instance();

  WiFi.begin(wifiInfo.ssid().c_str(), wifiInfo.password().c_str());

  Serial.print("Connecting to ");
  Serial.println(wifiInfo.ssid());

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("Connected");

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

  return true;
}

void NetworkHealthTask::OnStop()
{
}

void NetworkHealthTask::OnUpdate(uint32_t deltaTime)
{
  if(!m_client.connected())
  {
    const char * host = "m10.cloudmqtt.com";
    const int port = 28367;

    Serial.print("Connecting to ");
    Serial.println(host);

    if(!m_client.connect(host, port))
    {
      Serial.println("Connection failed");
    }
    else
    {
      Serial.println("Connection succeeded, disconnecting");
      m_client.stop();
    }
  }
}

}
