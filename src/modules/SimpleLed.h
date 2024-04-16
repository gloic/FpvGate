#pragma once
#include "Arduino.h"
#include "Module.h"

class SimpleLed : public Module {
    public:
        SimpleLed(int pin);
        void setup() override;
        void loop() override;
        void on();
        void off();
    private:
        int pin;
        bool state;
        bool newState;
};