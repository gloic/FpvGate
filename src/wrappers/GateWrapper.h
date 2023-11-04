#pragma once

#include <gate/GateBase.h>
#include <gate/Gate.h>

class GateWrapper : public GateBase {
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