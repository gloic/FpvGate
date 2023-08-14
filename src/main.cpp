#include <Arduino.h>

#include "headers/GateConfig.h"
#include "headers/GateBase.h"
#include "headers/StarterWrapper.h"
#include "headers/GateWrapper.h"
#include "headers/GateBase.h"

GateBase *gate;

void setup() {
    if (DEV_MODE == 1) {
        Serial.begin(115200);
    }

    if (digitalRead(PIN_STARTER) == HIGH) {
        gate = new StarterWrapper();
        Serial.println("Device is the starter");
    } else {
        gate = new GateWrapper();
        Serial.println("Device is a gate");
    }
    gate->setup();
    Serial.println("Device ready!");
}

void loop() {
    gate->loop();
}
