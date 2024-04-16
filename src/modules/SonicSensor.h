#pragma once

#include "Arduino.h"
#include <ArduinoLog.h>
#include <NewPing.h>

#include <config/GateConfig.h>
#include "Module.h"
#include "SimpleLed.h"
#include "Buzzer.h"

class SonicSensor : public Module {
  public:
    SonicSensor():
      sonar(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, 200),
      potPin(PIN_SONIC_SENSOR_POT_RANGE),
      led(PIN_SONIC_SENSOR_LED),
      buzzer(PIN_BUZZER) {}
    void setup() override;
    void stop();
    boolean checkPass();
  private:
    NewPing sonar;
    SimpleLed led;
    Buzzer buzzer;

    int potPin;
    int thresholdDistance = 0;

    // long duration;
    // float distance;

    long sendPulse();
    void updateThreshold();
};