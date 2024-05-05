#include "SimpleLed.h"
#include <ArduinoLog.h>

void SimpleLed::setup() {
    Log.infoln("SimpleLed::setup");
    pinMode(pin, OUTPUT);
}

void SimpleLed::loop() {
    if (newState != state) {
        Log.infoln("Changing led state");
        digitalWrite(pin, newState ? HIGH : LOW);
        state = newState;
    }
}

void SimpleLed::on() {
    if (newState) {
        return;
    }

    Log.infoln("SimpleLed::on");
    newState = true;
}

void SimpleLed::off() {
    if (!newState) {
        return;
    }
    
    Log.infoln("SimpleLed::off");
    newState = false;
}