#pragma once

#include "Wrapper.h"
#include <gate/Gate.h>

class GateWrapper : public Wrapper {
private:
    Gate gate;
public:
    void setup(AsyncWebServer &webServer) override {
        gate.setup(webServer);
    }

    void loop() override {
        gate.loop();
    }
};