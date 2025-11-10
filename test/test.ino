#include <Temperature.h>

TemperatureSensor sensor(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensor.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = sensor.getTemperature();
  if (sensor.isConnected()) {
    Serial.println(temp);
  }
  else {
    Serial.println("Sensor disconnected");
  }
}
