#include "EspBase.h"
#include "Gate.h"
#include "Starter.h"

#include <ESPAsyncWebServer.h>
Gate *gate;

#define starterPin 11

// LEDS I2C (for FastLED)
#define NUM_LEDS 4
#define DATA_PIN 23
#define CLOCK_PIN 22

void setup() {
  Serial.begin(115200);
  
  pinMode(starterPin, INPUT);
  bool isStarter = digitalRead(starterPin);
  
  if(isStarter) {
    gate = new Starter();
  } else {
    gate = new Gate();
  }
  
  gate->setup();
}

void loop() {
  gate->checkPass();
  delay(50);
}