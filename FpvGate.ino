
#include "Starter.h"
#include <ESPAsyncWebServer.h>

#define starterPin 12

Starter* gate;

void setup() {
  Serial.begin(115200);
  gate = new Starter();
  
  if (digitalRead(starterPin) == LOW) {
    //gate = new Starter();
    Serial.println("Device is the starter");
  } else {
    //gate = new Gate();
    Serial.println("Device is a gate");
  }
  
  gate->setup();
  Serial.println("Device ready!");
}

void loop() {
  gate->loop();
}
