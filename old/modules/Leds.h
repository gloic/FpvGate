#pragma once

#include <ArduinoLog.h>
#include <Adafruit_NeoPixel.h>

#include "../config/GateConfig.h"

class Leds {
  public:
    Leds(): pixels(NUM_LEDS, PIN_STRIP_LEDS, NEO_GRB + NEO_KHZ800) {
      Log.infoln("Init Leds strip : %d leds on pin %d", NUM_LEDS, PIN_STRIP_LEDS);
    }
    void setup();
    void loop();

    
    void initPattern();

    void blink();

    void on(uint32_t color);
    void on();
    void off();
    void setColor(uint32_t color);
private:
    Adafruit_NeoPixel pixels;

    void colorWipe(uint32_t color);
};