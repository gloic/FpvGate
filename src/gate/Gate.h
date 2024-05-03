#pragma once

#include <config/GateConfig.h>
#include <modules/SonicSensor.h>
#include <modules/Buzzer.h>

#include <Secrets.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoLog.h>
#include <utils/WebUtils.h>
#include <modules/SimpleLed.h>

class Gate {
    public:
        Gate(): sonicSensor(), buzzer(), led(), webUtils()  {
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
        Buzzer buzzer;
        SimpleLed led;
};