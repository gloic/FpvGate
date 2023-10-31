#include <Arduino.h>

#include <ArduinoLog.h>
#include "config/GateConfig.h"
#include "gate/GateBase.h"
#include "wrappers/StarterWrapper.h"
#include "wrappers/GateWrapper.h"

GateBase *gate;

void setup() {
    Serial.begin(115200);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    
    if (digitalRead(PIN_STARTER) == LOW) {
       gate = new StarterWrapper();
       Log.infoln("Device is the starter");
    } else {
        gate = new GateWrapper();
        Log.infoln("Device is a gate");
    }
    gate->setup();
    Log.infoln("Device ready!");
}

void loop() {
    gate->loop();
}