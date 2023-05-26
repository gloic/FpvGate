
#include "Starter.h"
#include <ESPAsyncWebServer.h>

#define starterPin 13

Gate* gate;

void setup() {
  Serial.begin(115200);

  pinMode(starterPin, INPUT);

  //gate = new Starter();
  
  if (digitalRead(starterPin) == HIGH) {
    gate = new Starter();
    Serial.println("Device is the starter");
  } else {
    gate = new Gate();
    Serial.println("Device is a gate");
  }
  
  gate->setup();
  Serial.println("Device ready!");
}

void loop() {
  gate->loop();
  //delay(50);
}
