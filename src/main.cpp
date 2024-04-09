#include <Arduino.h>
#include <ArduinoLog.h>
#include <wrappers/GateWrapper.h>
#include <server/FpvGateServer.h>
#include <wrappers/StarterWrapper.h>

Wrapper* gate;
AsyncWebServer webServer(80);

Wrapper* initGate();

void setup() {
    Serial.begin(115200);
    pinMode(PIN_STARTER, INPUT_PULLUP);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    gate = initGate();
    gate->setup(webServer);
    webServer.begin();

    Log.infoln("Device ready!");

}

void loop() {
    gate->loop();
}

Wrapper* initGate() {
    if (digitalRead(PIN_STARTER) == HIGH) { // true by default if not pressed
       Log.infoln("Device is the starter");
       FpvGateServer::getInstance().setup(webServer);
       return new StarterWrapper();
    } else {
        Log.infoln("Device is a gate");
        return new GateWrapper();
    }
}