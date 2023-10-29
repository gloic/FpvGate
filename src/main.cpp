#include <Arduino.h>

#include "config/GateConfig.h"
#include "gate/GateBase.h"
#include "wrappers/StarterWrapper.h"
#include "wrappers/GateWrapper.h"

GateBase *gate;

void setup() {
    // if (DEV_MODE == 1) {
        Serial.begin(115200);
    // }

    pinMode(PIN_STARTER, INPUT);
    pinMode(PIN_SONIC_SENSOR_LED, OUTPUT);

    if (digitalRead(PIN_STARTER) == LOW) {
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
    // if (digitalRead(PIN_STARTER) == HIGH) {
    //     digitalWrite(PIN_SONIC_SENSOR_LED, LOW);
    // } else {
    //     digitalWrite(PIN_SONIC_SENSOR_LED, HIGH);
    // }

}
