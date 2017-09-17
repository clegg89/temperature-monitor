/*
 * @file main.cpp
 *
 * @author C. Smith
 */

#include <Arduino.h>
#include <Task.h>
#include <memory>

#include "led-task.hpp"
#include "network-health-task.hpp"
#include "network-messaging-task.hpp"
#include "sensor-task.hpp"
#include "network-queue.hpp"
#include "wifi-information.hpp"

static app::LedTask* ledTask;
static app::NetworkHealthTask* networkHealthTask;
static app::NetworkMessagingTask* networkMessagingTask;
static app::SensorTask* sensorTask;
static TaskManager taskManager;

static void initSerialPort(HardwareSerial& serial, const bool enableDebug);

void setup()
{
  const uint32_t msPerMinute = (1000 * 60);
  const uint32_t ledTaskPeriod = MsToTaskTime(1000);
  const uint32_t networkHealthTaskPeriod = MsToTaskTime(100);
  const uint32_t sensorTaskPeriod = MsToTaskTime(msPerMinute);
  const uint32_t networkMessaginTaskPeriod = sensorTaskPeriod/2;

  std::shared_ptr<app::NetworkQueue> networkQueue(std::make_shared<app::NetworkQueue>());

  initSerialPort(Serial, false);

  ledTask = new app::LedTask(BUILTIN_LED, ledTaskPeriod);
  networkHealthTask = new app::NetworkHealthTask(networkHealthTaskPeriod);
  networkMessagingTask = new app::NetworkMessagingTask(
      networkHealthTask->client(), networkQueue, networkMessaginTaskPeriod);
  sensorTask = new app::SensorTask(D3, DHT11, networkQueue, sensorTaskPeriod);

  taskManager.StartTask(ledTask);
  taskManager.StartTask(sensorTask);
  taskManager.StartTask(networkHealthTask);
  taskManager.StartTask(networkMessagingTask);
}

void loop()
{
  taskManager.Loop();
}

/* Never called */
void teardown()
{
  delete sensorTask;
  delete networkHealthTask;
  delete networkMessagingTask;
  delete ledTask;
}

static void initSerialPort(HardwareSerial& serial, const bool enableDebug)
{
  serial.begin(115200);
  serial.setDebugOutput(enableDebug);
  delay(1000);
}
