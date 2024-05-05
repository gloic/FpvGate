#pragma once

#include <config/GateConfig.h>
#include "Module.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

class LcdDisplay : public Module {
    public:
        LcdDisplay() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, PIN_OLED_RESET) {};
        void setup() override;
        void clear();
        void showTop(String title);
        void showBottom(String* lines, int numLines);
        void show();
    private:
        Adafruit_SSD1306 display;
};