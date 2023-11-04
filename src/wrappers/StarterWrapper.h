#pragma once

#include <gate/GateBase.h>
#include <gate/Starter.h>

class StarterWrapper : public GateBase {
private:
    Starter starter;
public:
    void setup(AsyncWebServer &webServer) override {
        starter.setup(webServer);
    }

    void loop() override {
        starter.loop();
    }
};