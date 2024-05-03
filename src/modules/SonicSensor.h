#pragma once

#include "Arduino.h"
#include <ArduinoLog.h>
#include <NewPing.h>

#include <config/GateConfig.h>
#include "Module.h"

#include "Buzzer.h"

class SonicSensor : public Module {
  public:
    SonicSensor():
      sonar(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, 200),
      potPin(PIN_SONIC_SENSOR_POT_RANGE){}
    void setup() override;
    void stop();
    boolean checkPass();
  private:
    NewPing sonar;

    int potPin;
    int thresholdDistance = 0;

    // long duration;
    // float distance;

    long sendPulse();
    void updateThreshold();
};