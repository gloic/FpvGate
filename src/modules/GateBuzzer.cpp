#include "GateBuzzer.h"
#include "Arduino.h"
#include "../config/GateConfig.h"

#define NOTE_C4  880

void GateBuzzer::setup() {}

void GateBuzzer::beep() {
  Serial.println("beeping");
  if(!DEV_MUTE_BUZZER) {
    int noteDuration = 1000 / 1;
    tone(buzzerPin, NOTE_C4, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
  
}
