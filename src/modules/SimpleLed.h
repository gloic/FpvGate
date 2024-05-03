#pragma once
#include "Arduino.h"
#include "Module.h"
#include<config/GateConfig.h>

class SimpleLed : public Module {
    public:
        SimpleLed() : pin(PIN_SONIC_SENSOR_LED), state(false), newState(false) {}
        void setup() override;
        void loop() override;
        void on();
        void off();
    private:
        int pin;
        bool state;
        bool newState;
};