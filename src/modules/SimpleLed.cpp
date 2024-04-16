#include "SimpleLed.h"

SimpleLed::SimpleLed(int pin) {
    this->pin = pin;
    this->state = false;
    this->newState = false;
}

void SimpleLed::setup() {
    pinMode(pin, OUTPUT);
}

void SimpleLed::loop() {
    if (newState != state) {
        digitalWrite(pin, newState ? HIGH : LOW);
        state = newState;
    }
}

void SimpleLed::on() {
    newState = true;
}

void SimpleLed::off() {
    newState = false;
}