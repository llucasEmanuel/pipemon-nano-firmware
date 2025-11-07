#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "OneWire.h"
#include "DallasTemperature.h"
#include <Arduino.h>

class TemperatureSensor {
private: 
  OneWire oneWire;
  DallasTemperature sensor;
  float last_temperature;

public:
  TemperatureSensor(const unsigned int sensorPin);

  bool isConnected();

  float getTemperaure();
}

#endif /* TEMPERATURE_H */