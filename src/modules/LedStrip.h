#pragma once

#include "Module.h"
#include <Adafruit_NeoPixel.h>

class LedStrip : public Module {
    public: 
        LedStrip();
        void setup() override;
        void loop() override;

        void on();
        void off();
        void setColor();
    private:
        Adafruit_NeoPixel strip;
        boolean isOn;
};