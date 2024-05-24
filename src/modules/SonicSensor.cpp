#include "SonicSensor.h"
#include <ArduinoLog.h>

const float minDistance = 10.0;
const float maxDistance = 300.0;
const int step = 5;

void SonicSensor::setup() {
  Log.infoln("SonicSensor setup");
  pinMode(potPin, INPUT);
  led.setup();
  buzzer.setup();
  updateThreshold();  
}

boolean SonicSensor::checkPass() {
  led.loop();

  if (!this->isListening()) return false;

  updateThreshold();
  boolean result = false;
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  long distance = sonar.ping_cm(thresholdDistance);
  if (distance > 0) {
    Log.infoln("Passage detected at %d cm", distance);
    result = true;
    buzzer.beep();
  }
  return result;
}

void SonicSensor::updateThreshold() {
  int newThresHoldDistance = map(analogRead(potPin), 0, 4095, minDistance, maxDistance);
  if (abs(thresholdDistance - newThresHoldDistance) > step) {
    Log.infoln("Threshold distance changed. previous: %d, new: %d", thresholdDistance, newThresHoldDistance);
    thresholdDistance = newThresHoldDistance;
  }
}

boolean SonicSensor::isListening() {
  return _isListening;
}

void SonicSensor::start() {
  Log.infoln("SonicSensor::start");
  led.on();
  _isListening = true;
}

void SonicSensor::stop() {
  Log.infoln("SonicSensor::stop");
  led.off();
  _isListening = false;
}