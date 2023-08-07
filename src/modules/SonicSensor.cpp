#include "Arduino.h"
#include "headers/modules/SonicSensor.h"

long duration;
float distance;

const float minDistance = 10.0;
const float maxDistance = 300.0;

SonicSensor::SonicSensor(int triggerPin, int echoPin, int potPin) {
  this->_triggerPin = triggerPin;
  this->_echoPin = echoPin;
  this->_potPin = potPin;
  this->_thresholdDistance = 40.0;
}

void SonicSensor::setup() {
  pinMode(this->_triggerPin, OUTPUT);
  pinMode(this->_echoPin, INPUT);
  pinMode(this->_potPin, INPUT);
}

bool SonicSensor::checkPass() {
  
  refreshDistance();

  sendPulse();
  
  duration = pulseIn(this->_echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance < this->_thresholdDistance;
}

void SonicSensor::refreshDistance() {
  this->_thresholdDistance = map(analogRead(_potPin), 0, 4095, minDistance, maxDistance);
}

void sendPulse() {
  digitalWrite(this->_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->_triggerPin, LOW);
}
