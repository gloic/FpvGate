#pragma once

#include "Module.h"

class Buzzer : public Module {
    public:
        Buzzer(int pin) : pin(pin) {}
        void setup() override;
        void beep();
    private:
        int pin;

};