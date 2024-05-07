#pragma once

#include "Wrapper.h"
#include "../Starter.h"
#include "../StarterDev.h"

class StarterWrapper : public Wrapper {
    public:
        StarterWrapper() : starter(new Starter()) {}
        void setup(AsyncWebServer &webServer) override {
            starter->setup(webServer);
        }
        void loop() override {
            starter->loop();
        }
    private:
        Starter* starter;
};