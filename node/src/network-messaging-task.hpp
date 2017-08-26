/**
 * @file network-messaging-task.hpp
 *
 * @author C. Smith
 */

#ifndef _NETWORK_MESSAGING_TASK_HPP_
#define _NETWORK_MESSAGING_TASK_HPP_

#include <Arduino.h>
#include <Task.h>
#include <MqttClient.h>
#include <memory>

#include "network-queue.hpp"

namespace app
{

class NetworkMessagingTask : public Task
{
  public:

    NetworkMessagingTask(const std::shared_ptr<MqttClient>& client,
                         const std::shared_ptr<NetworkQueue>& queue,
                         const uint32_t timeInterval);
    virtual ~NetworkMessagingTask() = default;

  private:

    bool OnStart() override;
    void OnStop() override;
    void OnUpdate(uint32_t deltaTime) override;

    String encrypt(const String& message) const;

    std::shared_ptr<NetworkQueue> m_queue;
    std::shared_ptr<MqttClient> m_client;
};

}

#endif /* _NETWORK_MESSAGING_TASK_HPP_ */
