/*
 * @file led-task.cpp
 *
 * @author C. Smith
 */

#include "led-task.hpp"

namespace app
{

LedTask::LedTask(const uint8_t ledPin, const uint32_t timeInterval)
  : Task(timeInterval), m_pin(ledPin)
{
}

bool LedTask::OnStart()
{
  pinMode(m_pin, OUTPUT);
  digitalWrite(m_pin, LOW);

  return true;
}

void LedTask::OnStop()
{
  digitalWrite(m_pin, LOW);
}

void LedTask::OnUpdate(uint32_t deltaTime)
{
  const uint8_t state = digitalRead(m_pin);

  digitalWrite(m_pin, (state == LOW) ? HIGH : LOW);
}

}
