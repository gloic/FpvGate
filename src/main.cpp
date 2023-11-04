#include <Arduino.h>

#include <ArduinoLog.h>
#include <wrappers/StarterWrapper.h>
#include <wrappers/GateWrapper.h>

#include <server/FpvGateServer.h>

GateBase *gate;
AsyncWebServer webServer(80);

void setup() {
    Serial.begin(115200);

    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    if (digitalRead(PIN_STARTER) == LOW) {
       Log.infoln("Device is the starter");
       gate = new StarterWrapper();
    } else {
        Log.infoln("Device is a gate");
        gate = new GateWrapper();
    }
    gate->setup(webServer);
    FpvGateServer::getInstance().setup(webServer);

    Log.infoln("Device ready!");
}

void loop() {
    gate->loop();
    FpvGateServer::getInstance().loop();
}