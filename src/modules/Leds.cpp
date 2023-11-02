#include "Leds.h"

#include <Arduino.h>

const int WAITING_TIME = 50;

void Leds::setup() {
  pixels.begin();
  pixels.show();
}

void Leds::blink() {
  Log.infoln("Blinking");
  on();
  delay(1000);
  off();
  delay(1000);
}

void Leds::on(uint32_t color) {
  colorWipe(color);
}

void Leds::on() {
  colorWipe(pixels.Color(0, 0, 255));
}

void Leds::off() {
  colorWipe(pixels.Color(0, 0, 0));
}

void Leds::colorWipe(uint32_t color) {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void Leds::setColor(uint32_t color) {
  uint8_t red = (color >> 16) & 0xFF;
  uint8_t green = (color >> 8) & 0xFF;
  uint8_t blue = color & 0xFF;
  pixels.Color(red, green, blue);
}

void Leds::loop() {
  //pixels.show();
}

void Leds::initPattern() {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(100);
  }
}

// void Leds::idlePattern() {
//   // White / Nothing ?
// }

// void Leds::trackPattern() {
//   // Blue
// }

// void Leds::racePattern() {
//   // Green / Red / Nothing
// }

// void Leds::calibrationPattern() {
//   // Yellow
// }