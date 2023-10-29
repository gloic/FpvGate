#include "Arduino.h"
#include "SonicSensor.h"

const float minDistance = 10.0;
const float maxDistance = 300.0;
const int margin = 5;

SonicSensor::SonicSensor(int triggerPin, int echoPin, int potPin, int ledPin) {
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  this->potPin = potPin;
  this->ledPin = ledPin;
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

  pinMode(this->triggerPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
  pinMode(this->potPin, INPUT);
  pinMode(this->ledPin, OUTPUT);

  this->refreshDistance();
}

boolean SonicSensor::checkPass() {
  this->ledOn();
  this->refreshDistance();

  this->sendPulse();  
  long pulseDuration = pulseIn(this->echoPin, HIGH);
  float passDistance = pulseDuration * 0.034 / 2;

  boolean isDetected = passDistance < this->_thresholdDistance;
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
    
    this->ledOff();
  }
  return isDetected;
}

void SonicSensor::stop() {
  this->ledOff();
}

void SonicSensor::refreshDistance() {
  int newThresHoldDistance = map(analogRead(potPin), 0, 4095, minDistance, maxDistance);
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
  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->triggerPin, LOW);
}

void SonicSensor::ledOn() {
  digitalWrite(this->ledPin, HIGH);
}

void SonicSensor::ledOff() {
  digitalWrite(this->ledPin, LOW);
}