/**
 * @file sensor-task.hpp
 *
 * @author C. Smith
 */

#ifndef _SENSOR_TASK_HPP_
#define _SENSOR_TASK_HPP_

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Task.h>
#include <memory>

#include "network-queue.hpp"

namespace app
{

class SensorTask : public Task
{
  public:

    SensorTask(const uint8_t pin,
               const uint8_t type,
               const std::shared_ptr<NetworkQueue>& queue,
               const uint32_t timeInterval);
    virtual ~SensorTask() = default;

  private:

    std::shared_ptr<NetworkQueue> m_queue;
    DHT_Unified m_dht;

    bool OnStart() override;
    void OnStop() override;
    void OnUpdate(uint32_t deltaTime) override;
};

}

#endif /* _SENSOR_TASK_HPP_ */
