#pragma once

class StarterRestController {
    public:
        StarterRestController(AsyncWebServer& server, StarterWebController webController): server(server), webController(webController) {
            StarterRestController::instance = this;
        };
        void setup();

    private:
        static Starter *instance;
        AsyncWebServer& server;
        StarterWebController webController;

        static void onRegisterGate(AsyncWebServerRequest *request);
        static void onGatePassed(AsyncWebServerRequest *request);
};