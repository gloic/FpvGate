#include "LedStrip.h"
#include <config/GateConfig.h>

LedStrip::LedStrip() {
    this->strip = Adafruit_NeoPixel(NUM_LEDS, PIN_STRIP_LEDS, NEO_GRB + NEO_KHZ800);
    this->isOn = false;
}

void LedStrip::setup() {
    this->strip.begin();
}

void LedStrip::loop() {
    if(this->isOn) {
        strip.show();
    }
    strip.fill(strip.Color(255, 0, 0)); // Red
    delay(1000);
    for (int i = 0; i < 256; i++) {
        strip.fill(strip.Color(i, 0, 0)); // Red with varying intensity
        strip.show();
        delay(20);
    }
}

void LedStrip::on() {
    this->isOn = true;
}

void LedStrip::off() {
    this->isOn = false;
}

void LedStrip::setColor() {
    // todo
}