
#include "Starter.h"
#include <ESPAsyncWebServer.h>

#define starterPin 13

Starter *gate;

// LEDS I2C (for FastLED)
//#define NUM_LEDS 4
//#define DATA_PIN 23
//#define CLOCK_PIN 22

void setup() {
  Serial.begin(115200);

  pinMode(starterPin, INPUT);

  gate = new Starter();
  /*
  if (digitalRead(starterPin) == HIGH) {
    gate = new Starter();
    Serial.println("Device is the starter");
  } else {
    gate = new Gate();
    Serial.println("Device is a gate");
  }
  */
  gate->setup();

  Serial.println("Device ready!");
}

void loop() {
  gate->loop();
  //delay(50);
}
