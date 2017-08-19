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
#include "sensor-task.hpp"
#include "network-queue.hpp"

static app::LedTask ledTask(BUILTIN_LED, MsToTaskTime(1000));
static app::NetworkHealthTask networkHealthTask(MsToTaskTime(100));
static app::SensorTask sensorTask(
    D3,
    DHT11,
    std::make_shared<app::NetworkQueue>(),
    MsToTaskTime(1000)); // TODO make 1 minute
static TaskManager taskManager;

void initSerialPort(HardwareSerial& serial, const bool enableDebug);

void setup()
{
  initSerialPort(Serial, false);

  taskManager.StartTask(&ledTask);
  taskManager.StartTask(&sensorTask);
  taskManager.StartTask(&networkHealthTask);
}

void loop()
{
  taskManager.Loop();
}

void initSerialPort(HardwareSerial& serial, const bool enableDebug)
{
  serial.begin(115200);
  serial.setDebugOutput(enableDebug);
  delay(1000);
}
