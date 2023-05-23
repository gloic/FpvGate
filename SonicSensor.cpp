#include "SonicSensor.h"
#include "Arduino.h"

int thresholdDistance = 30;
int minThreshold = 2 * thresholdDistance / 0.034;

SonicSensor::SonicSensor(int triggerPin, int echoPin) {
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
}

void SonicSensor::setup() {
  pinMode(this->triggerPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}

bool SonicSensor::checkPass() {
  // trigger the sensor by sending a 10us pulse to the trig pin
  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->triggerPin, LOW);
  // measure the time it takes for the echo pin to go from HIGH to LOW
  long duration = pulseIn(this->echoPin, HIGH);
  // check if something is within the threshold of the sensor
  // float distance = duration * 0.034 / 2;
  return duration < minThreshold;
}
