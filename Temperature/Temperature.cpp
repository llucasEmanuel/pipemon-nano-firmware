#include "Temperature.h"

TemperatureSensor::TemperatureSensor(const unsigned int sensorPin) : oneWire(sensorPin), sensor(&oneWire) {
  this->last_temperature = 25;
}

bool TemperatureSensor::isConnected() {
  this->sensors.requestTemperatures();
  float tempC = this->sensors.getTempCByIndex(0);
  return (tempC == DEVICE_DISCONNECTED_C);
}

float TemperatureSensor::getTemperaure() {
  this->sensors.requestTemperatures();
  float tempC = this->sensors.getTempCByIndex(0);
  this->last_temperature = tempC;
  return tempC;
}