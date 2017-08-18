/**
 * @file network-health-task.hpp
 *
 * @author C. Smith
 */

#ifndef _NETWORK_HEALTH_TASK_HPP_
#define _NETWORK_HEALTH_TASK_HPP_

#include <Arduino.h>
#include <Task.h>

#include "verified-wifi-client.hpp"

namespace app
{

class NetworkHealthTask : public Task
{
  public:

    NetworkHealthTask(const uint32_t timeInterval);
    virtual ~NetworkHealthTask() = default;

  private:

    bool OnStart() override;
    void OnStop() override;
    void OnUpdate(uint32_t deltaTime) override;

    VerifiedWifiClient m_client;
};

}

#endif /* _NETWORK_HEALTH_TASK_HPP_ */
