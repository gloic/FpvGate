#pragma once

#include <ESPAsyncWebServer.h>

class ServerWebController {
    public:
        void setup(AsyncWebServer &webServer);
   private:
        static void onRegister(AsyncWebServerRequest *request);
        static void onPass(AsyncWebServerRequest *request);
};