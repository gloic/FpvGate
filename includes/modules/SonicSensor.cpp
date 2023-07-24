#include "../headers/SonicSensor.h"
#include "Arduino.h"

float thresholdDistance;
//int minThreshold = 2 * thresholdDistance / 0.034;
long duration;
float distance;

SonicSensor::SonicSensor(int triggerPin, int echoPin) {
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  this->thresholdDistance = 40.0;
}

void SonicSensor::setup() {
  pinMode(this->triggerPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}

bool SonicSensor::checkPass() {
  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->triggerPin, LOW);
  
  duration = pulseIn(this->echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance < this->thresholdDistance;
}
