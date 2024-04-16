#include "Buzzer.h"
#include "Arduino.h"

#define NOTE_C4 880

void Buzzer::setup() {
    pinMode(pin, OUTPUT);
}

void Buzzer::beep() {
  int noteDuration = 1000 / 1;
  tone(pin, NOTE_C4, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(pin);
}