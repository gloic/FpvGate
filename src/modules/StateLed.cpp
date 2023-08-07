#include "../headers/modules/StateLed.h"

#include <Arduino.h>

StateLed::StateLed() {
// StateLed::StateLed(int pinRed, int pinGreen, int pinBlue) {
    _pinRed = 2;
    _pinGreen = 3;
    _pinBlue = 4;
    _ledMode = OFF;
}

void StateLed::setup() {
  pinMode(_pinRed, OUTPUT);
  pinMode(_pinGreen, OUTPUT);
  pinMode(_pinBlue, OUTPUT);
} 

void StateLed::loop() {
  switch(this->_ledMode) {
    case ON:
      analogWrite(_redPin, _red);
      analogWrite(_greenPin, _green);
      analogWrite(_bluePin, _blue);
      break;
   case BLINK:
      // TODO
      break;
   case OFF:
   default:
      digitalWrite(_redPin, LOW);
      digitalWrite(_greenPin, LOW);
      digitalWrite(_bluePin, LOW);
      break;
  }
}

void StateLed::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    _red = red;
    _green = green;
    _blue = blue;
}

void StateLed::setMode(LedMode mode) {
    _ledMode = mode;
}
