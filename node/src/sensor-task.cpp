/*
 * @file sensor-task.cpp
 *
 * @author C. Smith
 */

#include "sensor-task.hpp"

namespace app
{

SensorTask::SensorTask(
    const uint8_t pin, const uint8_t type, const uint32_t timeInterval)
  : Task(timeInterval), m_dht(pin ,type)
{
}

bool SensorTask::OnStart()
{
  int32_t taskInterval = TaskTimeToMs(getTimeInterval());

  m_dht.begin();

  Serial.println("DHT Initialized");

  // Print temperature sensor details.
  sensor_t sensor;
  m_dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  m_dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");

  taskInterval = (taskInterval > sensor.min_delay) ? taskInterval : sensor.min_delay;

  setTimeInterval(taskInterval);

  return true;
}

void SensorTask::OnStop()
{
}

void SensorTask::OnUpdate(uint32_t deltaTime)
{
}

}
