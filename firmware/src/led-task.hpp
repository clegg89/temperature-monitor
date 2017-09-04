/**
 * @file led-task.hpp
 *
 * @author C. Smith
 */

#ifndef _LED_TASK_HPP_
#define _LED_TASK_HPP_

#include <Arduino.h>
#include <Task.h>

namespace app
{

class LedTask : public Task
{
  public:

    LedTask(const uint8_t ledPin, const uint32_t timeInterval);
    virtual ~LedTask() = default;

  private:

    const uint8_t m_pin;

    bool OnStart() override;
    void OnStop() override;
    void OnUpdate(uint32_t deltaTime) override;
};

}

#endif /* _LED_TASK_HPP_ */
