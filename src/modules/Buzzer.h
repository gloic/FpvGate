#pragma once

#include "Module.h"
#include <config/GateConfig.h>

class Buzzer : public Module {
    public:
        Buzzer() : pin(PIN_BUZZER) {}
        void setup() override;
        void beep();
    private:
        int pin;

};