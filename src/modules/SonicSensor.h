#pragma once

#include "Arduino.h"
#include <NewPing.h>

#include <config/GateConfig.h>
#include "Module.h"

#include "Buzzer.h"
#include "SimpleLed.h"

class SonicSensor : public Module {
  public:
    SonicSensor():
      sonar(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, 200),
      potPin(PIN_SONIC_SENSOR_POT_RANGE),
      _isListening(false),
      thresholdDistance(0), 
      led() {}
    void setup() override;
    void start();
    void stop();
    boolean checkPass();
  private:
    NewPing sonar;
    SimpleLed led;

    int potPin;
    int thresholdDistance;
    boolean _isListening;
    long sendPulse();
    void updateThreshold();
    boolean isListening();
};