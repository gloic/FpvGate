
#include "includes/headers/Starter.h"
#include <ESPAsyncWebServer.h>

#include "includes/GateConfig.h"
#include <Arduino.h>


Starter *gate;

void setup() {
    if (DEV_MODE == 1) {
        Serial.begin(115200);
    }
    gate = new Starter();

    if (digitalRead( PIN_STARTER) == LOW) {
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
