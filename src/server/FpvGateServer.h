#pragma once

#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include "ServerWebController.h"
#include "enums/ServerMode.h"

class FpvGateServer {
    public:
        void setup(AsyncWebServer &webServer) {
            webController.setup(webServer);
        };

    private:
        ServerWebController webController;
        ServerMode mode;
//        AsyncWebServer webServer;
//        void setupWebController(AsyncWebServer &webServer);
};