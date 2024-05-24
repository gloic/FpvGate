#pragma once

#include "Gate.h"


class Starter : public Gate {
    public:
        Starter(): Gate() {}
        void setup(AsyncWebServer &webServer) {
            setupWifi();
            setupWebController(webServer);
            Gate::setupModules();
            id = doRegister();
        }
        void loop() { Gate::loop(); }
        void startListen() { Gate::startListen(); }
    protected:
        void setupWifi();
        void setupWebController(AsyncWebServer &webServer);
        int doRegister();
        void doNotifyPassage();
    private:
        // FpvGateServer& server;
};