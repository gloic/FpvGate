#include "Buzzer.h"
#include "Arduino.h"
#include <ArduinoLog.h>

#define NOTE_C4 880

void Buzzer::setup() {
    Log.infoln("Buzzer::setup");
    pinMode(pin, OUTPUT);
}

void Buzzer::beep() {
  Log.infoln("Buzzer::beep");
  int noteDuration = 1000 / 1;
  tone(pin, NOTE_C4, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(pin);
}