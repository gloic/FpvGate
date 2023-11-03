#pragma once

#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include "ServerWebController.h"

class FpvGateServer {
    public:
        void setup(AsyncWebServer &webServer) {
            webController.setup(webServer);
        };

    private:
        ServerWebController webController;
//        AsyncWebServer webServer;
//        void setupWebController(AsyncWebServer &webServer);
};