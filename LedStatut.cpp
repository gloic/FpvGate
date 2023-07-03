#include "LedStatut.h"
#include <jled.h>

auto led_breathe = JLed(2).Breathe(1500).Forever();
auto led_blink = JLed(2).Blink(1000, 500).Forever();
  
LedStatut::LedStatut() {}

void LedStatut::setup() {
  ledMode = 0;
}

void LedStatut::loop() {
  switch(ledMode) {
    case 1:
      led_breathe.Update();
      break;
   case 2:
      led_blink.Update();
      break;
   default:
      break;
  }
}

void LedStatut::setMode(int mode) {
  this->ledMode = mode;
}
