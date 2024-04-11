#pragma once

#include "Arduino.h"
#include <NewPing.h>
#include <ArduinoLog.h>
#include <config/GateConfig.h>
#include "Module.h"

class SonicSensor : public Module {
  public:
    SonicSensor():
      sonar(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, 200),
      potPin(PIN_SONIC_SENSOR_POT_RANGE),
      ledPin(PIN_SONIC_SENSOR_LED) {}
    void setup() override;
    void stop();
    boolean checkPass();
protected:
private:
    NewPing sonar;

    int potPin;
    int ledPin;
    int thresholdDistance = 0;

    // long duration;
    // float distance;

    long sendPulse();
    void updateThreshold();

    void ledOn() {digitalWrite(ledPin, HIGH);}
    void ledOff() {digitalWrite(ledPin, LOW);}
};