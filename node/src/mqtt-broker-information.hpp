/**
 * @file mqtt-broker-information.hpp
 *
 * @author C. Smith
 */

#ifndef _MQTT_BROKER_INFORMATION_HPP_
#define _MQTT_BROKER_INFORMATION_HPP_

#include <Arduino.h>

namespace app
{

struct MqttBrokerInformation
{
  const String hostname;
  const uint32_t port;
  const String username;
  const String password;
};

extern const MqttBrokerInformation g_brokerInformation;

}

#endif /* _MQTT_BROKER_INFORMATION_HPP_ */
