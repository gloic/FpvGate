#pragma once

#include "StarterWebController.h"
#include <ESPAsyncWebServer.h>

class StarterRestController {
    public:
        StarterRestController() { instance = this; };
        void setup(AsyncWebServer& server);
    private:
        static StarterRestController *instance;
        StarterWebController webController;

        static void onRegisterGate(AsyncWebServerRequest *request);
        static void onGatePassed(AsyncWebServerRequest *request);
};