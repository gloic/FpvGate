#pragma once

#include "Wrapper.h"
#include <gate/Starter.h>
#include <gate/StarterDev.h>

class StarterWrapper : public Wrapper {
    public:
        StarterWrapper() {
            if(DEV_MODE) {
                starter = new StarterDev();
            } else {
                starter = new Starter();
            }
        }

        void setup(AsyncWebServer &webServer) override {
            starter->setup(webServer);
        }

        void loop() override {
            starter->loop();
        }
    private:
        Gate* starter;
};