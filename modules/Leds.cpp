#include "Leds.h"
//#include <FastLED.h>


//CRGB leds[5];
Leds::Leds(int numLeds, int dataPin) {
  this->numLeds = numLeds;
  this->dataPin = dataPin;
}

void Leds::setup() {
  //FastLED.addLeds<APA102>(&leds, this->numLeds);
}

void Leds::blink() {
  Serial.println("blinking");
}
