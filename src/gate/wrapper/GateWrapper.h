#pragma once

#include "Wrapper.h"
#include "../Gate.h"

class GateWrapper : public Wrapper {
    public:
        GateWrapper() : gate(new Gate()) {}
        void setup(AsyncWebServer &webServer) override {
            gate->setup(webServer);
        }
        void loop() override {
            gate->loop();
        }
    private:
        Gate* gate;
};