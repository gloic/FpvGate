#pragma once

#include "Wrapper.h"
#include <gate/Starter.h>
#include <gate/StarterDev.h>

class StarterWrapper : public Wrapper {
    public:
        StarterWrapper() {
            starter = new Starter();
        }

        void setup(AsyncWebServer &webServer) override {
            starter->setup(webServer);
        }

        void loop() override {
            starter->loop();
        }
    private:
        Starter* starter;
};