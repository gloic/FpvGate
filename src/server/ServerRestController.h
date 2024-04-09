#pragma once

#include <ESPAsyncWebServer.h>

class ServerRestController {
    public:
        void setup(AsyncWebServer &webServer);
   private:
        static void onRegister(AsyncWebServerRequest *request);
        static void onPass(AsyncWebServerRequest *request);
};