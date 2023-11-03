#pragma once

#include <gate/GateBase.h>
#include <gate/Gate.h>

class GateWrapper : public GateBase {
private:
    Gate gate;

public:
    void setup() override {
        gate.setup();
    }

    void loop() override {
        gate.loop();
    }
};