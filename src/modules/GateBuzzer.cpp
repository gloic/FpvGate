#include "Arduino.h"
#include "GateBuzzer.h"

#define NOTE_C4  880

GateBuzzer::GateBuzzer(int buzzerPin) {
  this->_buzzerPin = buzzerPin;  
}

void GateBuzzer::setup() {
}

void GateBuzzer::beep() {
  Serial.println("beeping");
  int noteDuration = 1000 / 1;
  tone(_buzzerPin, NOTE_C4, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(_buzzerPin);
}
