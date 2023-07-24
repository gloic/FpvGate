#include "../headers/StateLed.h"

StateLed::StateLed(int pin) {
  _led = new Led(pin);
}

void StateLed::setup() {
  this->_ledMode = 0;
}

void StateLed::loop() {
  switch(this->_ledMode) {
    case 0:
      _led->off();
      break;
    case 1:
      _led->on();
      break;
   case 2:
      _led->blink(200);
      break;
   default:
      break;
  }
}

void StateLed::setMode(int mode) {
  this->_ledMode = mode;
}
