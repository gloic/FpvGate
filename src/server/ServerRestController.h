#pragma once

#include <ESPAsyncWebServer.h>
#include <server/managers/GateManager.h>

class ServerRestController {
    public:
        void setup(AsyncWebServer &webServer);
   private:
        static void onRegister(AsyncWebServerRequest *request);
        static void onPass(AsyncWebServerRequest *request);
};