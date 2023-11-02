#include "Starter.h"
#include "../config/GateConfig.h"
#include "../structs/GateMode.h"

#include <vector>
#include <Arduino.h>
#include <ArduinoLog.h>
#include "OneButton.h"

Starter *Starter::instance = nullptr;

OneButton buttonReset(PIN_STARTER_RESET, false);

void Starter::setup() {
    Log.infoln("Setup Starter");
    setupWifi();
    setupWebController();
    setupGPIO();
    EspBase::startWebServer();
    Log.infoln("End of setup Starter");
}

void Starter::setupWifi() {
    if (DEV_MODE == 1) {
        EspBase::setupWifi(SECRET_SSID, SECRET_PASS);
    } else {
        EspBase::setupAPWifi(SECRET_SSID, SECRET_PASS);
    }
}

void Starter::setupWebController() {
    Gate::setupWebController();
    Log.infoln("Starter::setupWebController");
    
    server().on("/api/gate/register", HTTP_POST, &Starter::onRegisterGate);
    // server().on("/api/gate/passed", HTTP_POST, &Starter::onGatePassed);
}

void Starter::setupGPIO() {
    Gate::setupGPIO();
    buttonReset.attachClick(&Starter::onButtonResetPress);
    buttonReset.attachDoubleClick([]() {
        instance->isCalibrationMode = !instance->isCalibrationMode;
        if(instance->isCalibrationMode) {
            instance->enableCalibrationMode();
        }
    });
    buttonReset.attachLongPressStart([]() {
        instance->enableTrackMode();
    });
}

// void Starter::onRegisterGate(AsyncWebServerRequest *request) {
//     Log.infoln("onRegisterGate");
//     String clientIP = request->client()->remoteIP().toString();
//     boolean isMock = request->getHeader("isMock") != nullptr;
//     int id = instance->webController.registerGate(clientIP, isMock);

//     request->send(200, "text/plain", String(id));
// }

void Starter::onGatePassed(AsyncWebServerRequest *request) {
    Log.infoln("Gate passed !");
    String clientIP = request->client()->remoteIP().toString();
    Log.infoln("Client ip: %s", clientIP);

    auto *gate = instance->gatesManager.getGateClientFromIp(clientIP);
    instance->handleGatePassed(*gate);
    String responseBehavior = instance->isCalibrationMode ? "continue" : "stop";
    request->send(200, "text/plain", responseBehavior);
}

void Starter::handleGatePassed(GateClient &gate) {
    Log.infoln("Gate passed, id=%d", String(gate.id));

    if (trackHandler.isTrackMode()) {
        Log.infoln("Track mode, add gate to track");
        int trackSize = trackHandler.addGateToTrack(gate);
        if(trackSize >= 1) {
            Log.infoln("track has at least one gate, starter is listening too");
            startListening();
        }
    } else if (trackHandler.isRaceMode()) {
        if(trackHandler.isNextGate(gate.id)) {
            Log.infoln("This gate is expected");
            if (trackHandler.hasNextGate()) {
                trackHandler.incrementNextGateIndex();
                gateStartListening(gate);
            } else {
                Log.infoln("no next gate, Starter is next : start listening");
                startListening();
            }
        } else {
            Log.infoln("Another gate was passed ! pass:%p - expected:%p", gate, trackHandler.getNextGate());
        }
    }
}

void Starter::loop() {
    buttonReset.tick();

    boolean passed = false;
    if (isListening()) {
        passed = checkPass();
    }

    leds.loop();

    if (passed) {
        handleStarterPassage();
    }
}


void Starter::handleStarterPassage() {
    Log.infoln("Starter pass detected");

    if(isCalibrationMode) {
        delay(100);
        enableCalibrationMode();
        return;
    }
    
    stopListening();

    if (trackHandler.isTrackMode()) {
        if (trackHandler.getTrackGateSize() > 0) {
            Log.infoln("Track mode finished, starting race mode");
            // Workaround, a delay is necessary to avoid instant end of race mode
            delay(5000);
            enableRaceMode();
        }
    } else if (instance->trackHandler.isRaceMode()) {
        if(!trackHandler.isRaceStarted()) {
            startLap();
        } else {
            stopLap();
        }
        auto &gate = trackHandler.getNextGate();
        gateStartListening(gate);
    }
}

void Starter::onButtonResetPress() {
    Log.infoln("onButtonResetPress");
   if (instance->trackHandler.isRaceMode()) {
       instance->resetLap();
   }
}

void Starter::enableTrackMode() {
    Log.infoln("enableTrackMode");
    beep();
    trackHandler.setTrackMode();
    trackHandler.clearTrackGates();
    webController.startListeningAll();
}

void Starter::enableRaceMode() {
    Log.infoln("GO");
    beep();
    beep();
    trackHandler.setRaceMode();
    // Only Starter should listen
    startListening();
}

void Starter::gateStartListening(GateClient &gate) {
    Log.infoln("Send start listening to %p", gate);
    
    webController.startListening(gate);
}

void Starter::gateStopListening(GateClient &gate) {
    Log.infoln("Send stop listening to %p", gate);
    webController.stopListening(gate);
}

void Starter::resetLap() {
    trackHandler.resetLap();
    gateStartListening(trackHandler.getNextGate());
}

void Starter::startLap() {
    Log.infoln("Starting lap");
    beep();
    trackHandler.startLap();
}

void Starter::stopLap() {
    Log.infoln("Lap done");
    beep();
    trackHandler.stopLap();
}

void Starter::enableCalibrationMode() {
    startListening();
    webController.startListeningAll();
}