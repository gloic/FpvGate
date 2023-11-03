#pragma once

#include <config/GateConfig.h>
#include <modules/SonicSensor.h>

#include <Secrets.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>
#include <ArduinoLog.h>

#include <services/GateService.h>

class Gate {
    public:
        Gate(): server(80), sonicSensor(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, PIN_SONIC_SENSOR_POT_RANGE, PIN_SONIC_SENSOR_LED) {
            Gate::instance = this;
        };
        void setup();
        void loop();
    protected:
        AsyncWebServer server;
        boolean isListening;

        void setupWifi();
        void setupWebController();
        
        void doRegister();
        void doNotifyPassage();

        void startListen();
        void stopListen();
    private:
        static Gate *instance;
        static void onStartListen(AsyncWebServerRequest *request);
        static void onStopListen(AsyncWebServerRequest *request);

        SonicSensor sonicSensor;
        GateService service;

        void setupService();
        void setupModules();
        
};