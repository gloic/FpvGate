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
        Gate(): 
        // webServer(80), 
        webUtils(),
        sonicSensor(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, PIN_SONIC_SENSOR_POT_RANGE, PIN_SONIC_SENSOR_LED) {
            Gate::instance = this;
        };
        void setup(AsyncWebServer &webServer);
        void loop();
    protected:
        // AsyncWebServer webServer;
        boolean isListening;

        void setupWifi();
        void setupWebController(AsyncWebServer &webServer);
        
        void doRegister();
        void doNotifyPassage();

        void startListen();
        void stopListen();
        void setupModules();
    private:
        static Gate *instance;
        String getIpStarter();
        static void onStartListen(AsyncWebServerRequest *request);
        static void onStopListen(AsyncWebServerRequest *request);

        WebUtils webUtils;
        SonicSensor sonicSensor;
};