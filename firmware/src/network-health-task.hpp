/**
 * @file network-health-task.hpp
 *
 * @author C. Smith
 */

#ifndef _NETWORK_HEALTH_TASK_HPP_
#define _NETWORK_HEALTH_TASK_HPP_

#include <Arduino.h>
#include <Task.h>
#include <MqttClient.h>
#include <memory>
#include <memory>

#include "verified-wifi-client.hpp"

namespace app
{

class NetworkHealthTask : public Task
{
  public:

    NetworkHealthTask(const uint32_t timeInterval);
    virtual ~NetworkHealthTask();

    virtual std::shared_ptr<MqttClient> client() const { return m_mqttClient; }

  private:

    static uint32_t clientIdCount;

    /* System class to pass to MQTT client */
    class System : public MqttClient::System
    {
      public:

        unsigned long millis() const { return ::millis(); }
        void yield(void) { ::yield(); }
    };

    bool OnStart() override;
    void OnStop() override;
    void OnUpdate(uint32_t deltaTime) override;

    void connectWifi();
    void connectNetwork();
    void connectMqtt();

    VerifiedWifiClient m_wifiClient;
    String m_mqttClientId;
    std::shared_ptr<MqttClient> m_mqttClient;
    System m_system;
    MqttClient::LoggerImpl<HardwareSerial> m_logger;
    MqttClient::NetworkClientImpl<VerifiedWifiClient> m_mqttNetwork;
    MqttClient::ArrayBuffer<200> m_sendBuffer;
    MqttClient::ArrayBuffer<128> m_recvBuffer;
    MqttClient::MessageHandlersImpl<1> m_msgHandlers;
    MqttClient::Options m_mqttOptions;
};

}

#endif /* _NETWORK_HEALTH_TASK_HPP_ */
