/*
 * @file sensor-task.cpp
 *
 * @author C. Smith
 */

#include "sensor-task.hpp"

#include <ArduinoJson.hpp>

namespace app
{

SensorTask::SensorTask(const uint8_t sdaPin,
                       const uint8_t sclPin,
                       const std::shared_ptr<NetworkQueue>& queue,
                       const uint32_t timeInterval)
  : Task(timeInterval), m_queue(queue)
{
  Wire.begin(sdaPin, sclPin);
}

bool SensorTask::OnStart()
{
  int32_t taskInterval = TaskTimeToMs(getTimeInterval());

  while (!m_sensor.begin())
  {
    Serial.println("ERROR Initializing BME280");
    delay(1000);
  }

  Serial.println("BME280 Initialized");

  /* Let sensor boot */
  delay(100);

  taskInterval = (taskInterval > 1000) ? taskInterval : 1000;

  setTimeInterval(MsToTaskTime(taskInterval));

  return true;
}

void SensorTask::OnStop()
{
}

void SensorTask::OnUpdate(uint32_t deltaTime)
{
  ArduinoJson::StaticJsonBuffer<200> jsonBuffer;
  ArduinoJson::JsonObject& jsonObj = jsonBuffer.createObject();
  bool error = false;
  float temperature;
  float humidity;
  String result;

  temperature = m_sensor.readTemperature();
  humidity = m_sensor.readHumidity();

  Serial.println("Take sensor measurements");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  jsonObj["temperature"] = temperature;

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  jsonObj["humidity"] = humidity;

  jsonObj.printTo(result);

  while(!m_queue->enqueue(result))
  {
    m_queue->dequeue();
  }
}

}
