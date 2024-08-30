#pragma once

#include <config/GateConfig.h>
#include <modules/SonicSensor.h>

#include <Secrets.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoLog.h>
#include <utils/WebUtils.h>
#include <utils/WifiUtils.h>

class Gate {
    public:
        Gate(): sonicSensor(), webUtils(), wifiUtils()  {
            Gate::instance = this;
        }

        void setup(AsyncWebServer &webServer) {
            setupWifi();
            setupWebController(webServer);
            setupModules();
            id = doRegister();
        }

        void loop();
        void startListen();
        void stopListen();
    protected:
        int id;
        
        void setupWifi();
        void setupWebController(AsyncWebServer &webServer);
        
        int doRegister();
        void doNotifyPassage();
        void setupModules();

        SonicSensor sonicSensor;
        WifiUtils wifiUtils;
    private:
        static Gate *instance;
        String getIpStarter();

        static void onStartListen(AsyncWebServerRequest *request);
        static void onStopListen(AsyncWebServerRequest *request);

        WebUtils webUtils;
};