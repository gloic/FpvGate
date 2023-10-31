#include "Leds.h"

#include <Arduino.h>

const int WAITING_TIME = 50;

void Leds::setup() {
  this->pixels.begin();
  this->pixels.show();
}

void Leds::blink() {
  Log.infoln("Blinking");
  this->on();
  delay(1000);
  this->off();
  delay(1000);
}

void Leds::on() {
  colorWipe(this->pixels.Color(0, 0, 255));
}

void Leds::off() {
  colorWipe(this->pixels.Color(0, 0, 0));
}

void Leds::colorWipe(uint32_t color) {
  for (int i = 0; i < this->pixels.numPixels(); i++) {
    this->pixels.setPixelColor(i, color);
  }
}

void Leds::setColor(uint32_t color) {
  uint8_t red = (color >> 16) & 0xFF;
  uint8_t green = (color >> 8) & 0xFF;
  uint8_t blue = color & 0xFF;
  this->pixels.Color(red, green, blue);
}

void Leds::loop() {
  this->pixels.show();
}
