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
      analogWrite(_pinRed, _red);
      analogWrite(_pinGreen, _green);
      analogWrite(_pinBlue, _blue);
      break;
   case BLINK:
      // TODO
      break;
   case OFF:
   default:
      digitalWrite(_pinRed, LOW);
      digitalWrite(_pinGreen, LOW);
      digitalWrite(_pinBlue, LOW);
      break;
  }
}

void StateLed::setColor(int red, int green, int blue) {
    _red = red;
    _green = green;
    _blue = blue;
}

void StateLed::setMode(LedMode mode) {
    _ledMode = mode;
}
