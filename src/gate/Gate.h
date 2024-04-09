#pragma once

#include <config/GateConfig.h>
#include <modules/SonicSensor.h>

#include <Secrets.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoLog.h>
#include <utils/WebUtils.h>

class Gate {
    public:
        Gate(): sonicSensor(sonicSensor) {
            Gate::instance = this;
        }

        void setup(AsyncWebServer &webServer) {
            setupWifi();
            setupWebController(webServer);
            id = doRegister();
        }

        void loop();
        void startListen();
        void stopListen();
    protected:
        boolean isListening = false;
        int id;
        
        void setupWifi();
        void setupWebController(AsyncWebServer &webServer);
        
        int doRegister();
        void doNotifyPassage();
        void setupModules();

        boolean checkPass();
    private:
        static Gate *instance;
        String getIpStarter();

        static void onStartListen(AsyncWebServerRequest *request);
        static void onStopListen(AsyncWebServerRequest *request);

        WebUtils webUtils;
        SonicSensor sonicSensor;
};