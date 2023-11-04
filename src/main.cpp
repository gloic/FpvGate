#include <Arduino.h>
#include <ArduinoLog.h>
#include <wrappers/GateWrapper.h>
#include <server/FpvGateServer.h>
#include <wrappers/StarterWrapper.h>

Wrapper* gate;
AsyncWebServer webServer(80);
boolean isStarter;

Wrapper* initGate();

void setup() {
    Serial.begin(115200);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    isStarter = digitalRead(PIN_STARTER) == LOW;

    gate = initGate();
    gate->setup(webServer);

    webServer.begin();
    Log.infoln("Device ready!");
}

void loop() {
    gate->loop();
}

Wrapper* initGate() {
    if (isStarter) {
       Log.infoln("Device is the starter");
       FpvGateServer::getInstance().setup(webServer);
       return new StarterWrapper();
    } else {
        Log.infoln("Device is a gate");
        return new GateWrapper();
    }
}