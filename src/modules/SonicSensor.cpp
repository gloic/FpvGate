#include "Arduino.h"
#include "headers/modules/SonicSensor.h"

long duration;
float distance;

const float minDistance = 10.0;
const float maxDistance = 300.0;

SonicSensor::SonicSensor(int triggerPin, int echoPin, int potPin, int ledPin) {
  this->_triggerPin = triggerPin;
  this->_echoPin = echoPin;
  this->_potPin = potPin;
  this->_thresholdDistance = 40.0;
  this->_ledPin = ledPin;
}

void SonicSensor::setup() {
  pinMode(this->_triggerPin, OUTPUT);
  pinMode(this->_echoPin, INPUT);
  pinMode(this->_potPin, INPUT);
  pinMode(this->_ledPin, OUTPUT);
}

bool SonicSensor::checkPass() {
  ledOn();
  refreshDistance();
  sendPulse();  
  duration = pulseIn(this->_echoPin, HIGH);
  distance = duration * 0.034 / 2;

  bool isDetection = distance < this->_thresholdDistance;
  if(isDetection) {
    ledOff();
  }
  return isDetection;
}

void SonicSensor::refreshDistance() {
  int newThresHoldDistance = map(analogRead(_potPin), 0, 4095, minDistance, maxDistance);
  if(this->_thresholdDistance != newThresHoldDistance) {
    Serial.println("Threshold distance changed.");
    Serial.print("actual thresholdDistance=");
    Serial.println(this->_thresholdDistance);
    Serial.print("new ThresHoldDistance=");
    Serial.println(newThresHoldDistance);
    this->_thresholdDistance = newThresHoldDistance;
  }
}

void SonicSensor::sendPulse() {
  digitalWrite(this->_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->_triggerPin, LOW);
}

void SonicSensor::ledOn() {
  digitalWrite(this->_ledPin, HIGH);
}

void SonicSensor::ledOff() {
  digitalWrite(this->_ledPin, LOW);
}