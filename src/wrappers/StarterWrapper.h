#pragma once

#include <gate/GateBase.h>
#include <gate/Starter.h>

class StarterWrapper : public GateBase {
private:
    Starter starter;

public:
    void setup() override {
        starter.setup();
    }

    void loop() override {
        starter.loop();
    }
};