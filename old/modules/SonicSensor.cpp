#include "SonicSensor.h"

#include "Arduino.h"
#include <NewPing.h>
#include <ArduinoLog.h>

const float minDistance = 10.0;
const float maxDistance = 300.0;
const int step = 5;

void SonicSensor::setup() {
  Log.infoln("SonicSensor setup");
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);
  updateThreshold();  
}

boolean SonicSensor::checkPass() {
  updateThreshold();
  ledOn();
  
  boolean result = false;
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  long distance = sonar.ping_cm(thresholdDistance);  
  if(distance > 0) {
    Log.infoln("Passage detected at %d cm", distance);
    result = true;
    ledOff();
  }
  return result;
}

void SonicSensor::stop() {
  ledOff();
}

void SonicSensor::updateThreshold() {
  int newThresHoldDistance = map(analogRead(potPin), 0, 4095, minDistance, maxDistance);
  if (abs(thresholdDistance - newThresHoldDistance) > step) {
    Log.infoln("Threshold distance changed. previous: %d, new: %d", thresholdDistance, newThresHoldDistance);
    thresholdDistance = newThresHoldDistance;
  }
}