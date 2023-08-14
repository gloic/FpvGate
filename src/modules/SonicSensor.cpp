#include "Arduino.h"
#include "headers/modules/SonicSensor.h"

const float minDistance = 10.0;
const float maxDistance = 300.0;
const int margin = 5;

SonicSensor::SonicSensor(int triggerPin, int echoPin, int potPin, int ledPin) {
  this->_triggerPin = triggerPin;
  this->_echoPin = echoPin;
  this->_potPin = potPin;
  this->_ledPin = ledPin;
}

void SonicSensor::setup() {
  Serial.println("SonicSensor setup");

  // Serial.print("triggerPin=");
  // Serial.println(this->_triggerPin);
  // Serial.print("echoPin=");
  // Serial.println(this->_echoPin);
  // Serial.print("potPin=");
  // Serial.println(this->_potPin);
  // Serial.print("ledPin=");
  // Serial.println(this->_ledPin);

  pinMode(this->_triggerPin, OUTPUT);
  pinMode(this->_echoPin, INPUT);
  pinMode(this->_potPin, INPUT);
  pinMode(this->_ledPin, OUTPUT);

  this->refreshDistance();
}

bool SonicSensor::checkPass() {
  this->ledOn();
  this->refreshDistance();

  this->sendPulse();  
  long pulseDuration = pulseIn(this->_echoPin, HIGH);
  float passDistance = pulseDuration * 0.034 / 2;

  bool isDetected = passDistance < this->_thresholdDistance;
  if(isDetected) {
    Serial.print("Passage detected at ");
    Serial.print(passDistance);
    Serial.println("cm");
    
    // Serial.print("pulseDuration=");
    // Serial.println(pulseDuration);
    // Serial.print("passDistance=");
    // Serial.println(passDistance);
    // Serial.print("thresholdDistance=");
    // Serial.println(this->_thresholdDistance);
    
    ledOff();
  }
  return isDetected;
}

void SonicSensor::refreshDistance() {
  int newThresHoldDistance = map(analogRead(_potPin), 0, 4095, minDistance, maxDistance);
  if (abs(this->_thresholdDistance - newThresHoldDistance) > margin) {
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