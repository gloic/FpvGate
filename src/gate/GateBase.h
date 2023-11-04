#pragma once

#include <ESPAsyncWebServer.h>

class GateBase {
    public:
        virtual void setup(AsyncWebServer &webServer) = 0;
        virtual void loop() = 0;
        virtual ~GateBase() {}
};