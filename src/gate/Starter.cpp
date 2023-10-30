#include "Starter.h"
#include "../config/GateConfig.h"
#include "../structs/GateMode.h"

#include <vector>
#include <Arduino.h>
#include "OneButton.h"

Starter *Starter::instance = nullptr;

OneButton buttonReset(PIN_STARTER_RESET, false);

void Starter::setup() {
    Serial.println("Setup Starter");
    this->setupWifi();
    this->setupWebController();
    this->setupGPIO();
    EspBase::startWebServer();
    Serial.println("End of setup Starter");
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
    Serial.println("Starter::setupWebController");
    this->server().on("/api/gate/register", HTTP_POST, &Starter::onRegisterGate);
    this->server().on("/api/gate/passed", HTTP_POST, &Starter::onGatePassed);
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

void Starter::onRegisterGate(AsyncWebServerRequest *request) {
    Serial.println("onRegisterGate");
    String clientIP = request->client()->remoteIP().toString();
    auto *gate = instance->webController.getGateClientFromIp(clientIP);
    if(gate != nullptr) {
        Serial.print("Ip already registered : ");
        Serial.print(clientIP);
        request->send(200, "text/plain", String(gate->id));
        return;
    }

    boolean isMock = request->getHeader("isMock") != nullptr;
    int id = instance->webController.registerGate(clientIP, isMock);

    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "");
    response->addHeader("test", "Test");
    request->send(200, "text/plain", String(id));
}

void Starter::onGatePassed(AsyncWebServerRequest *request) {
    Serial.println("Gate passed !");
    //int id = instance->getParamFromRequest("id", request).toInt();
    // auto *gate = instance->webController.getGateClientFromId(id);
    String clientIP = request->client()->remoteIP().toString();
    Serial.print("Client ip =");
    Serial.println(clientIP);

    auto *gate = instance->webController.getGateClientFromIp(clientIP);
    instance->handleGatePassed(gate);
    request->send(200, "text/plain", "stop");
}

void Starter::handleGatePassed(GateClient* gate) {
    Serial.print("Gate passed, id=");
    Serial.println(String(gate->id));

    if (this->trackHandler.isTrackMode()) {
        Serial.println("Track mode, add gate to track");
        int trackSize = this->trackHandler.addGateToTrack(gate);
        if(trackSize >= 1) {
            Serial.println("track has at least one gate, starter is listening too");
            this->startListening();
        }
    } else if (this->trackHandler.isRaceMode()) {
        if(this->trackHandler.isNextGate(gate->id)) {
            Serial.println("This gate is expected");
            if (this->trackHandler.hasNextGate()) {
                this->trackHandler.incrementNextGateIndex();
                this->gateStartListening(gate);
            } else {
                Serial.println("no next gate, Starter is next : start listening");
                this->startListening();
            }
        } else {
            Serial.println("Another gate was passed !");
            Serial.print("passed=");
            Serial.println(gate->id);
            Serial.print("expected=");
            Serial.println(this->trackHandler.getNextGate()->id);
        }
    }
}

void Starter::loop() {
    buttonReset.tick();

    boolean passed = false;
    if (this->isListening()) {
        passed = this->checkPass();
    }

    if (!passed) {
        return;
    }
    this->handleStarterPassage();    
}


void Starter::handleStarterPassage() {
    Serial.println("Started passed");

    if(this->isCalibrationMode) {
        delay(1000);
        this->enableCalibrationMode();
        return;
    }
    
    this->stopListening();

    if (this->trackHandler.isTrackMode()) {
        if (this->trackHandler.getTrackGateSize() > 0) {
            Serial.println("Track mode finished, starting race mode");
            // Workaround, a delay is necessary to avoid instant end of race mode
            delay(5000);
            this->enableRaceMode();
        }
    } else if (instance->trackHandler.isRaceMode()) {
        if(!this->trackHandler.isRaceStarted()) {
            this->startLap();
        } else {
            this->stopLap();
        }
        auto* gate = this->trackHandler.getNextGate();
        this->gateStartListening(gate);
    }
}

void Starter::onButtonResetPress() {
    Serial.println("onButtonResetPress");
   if (instance->trackHandler.isRaceMode()) {
       instance->resetLap();
   }
}

void Starter::enableTrackMode() {
    Serial.println("enableTrackMode");
    this->beep();
    this->trackHandler.setTrackMode();
    this->trackHandler.clearTrackGates();
    this->webController.startListeningAll();
}

void Starter::enableRaceMode() {
    Serial.println("GO");
    this->beep();
    this->beep();
    this->trackHandler.setRaceMode();
    // Only Starter should listen
    this->startListening();
}

void Starter::gateStartListening(GateClient *gate) {
    Serial.print("Send start listening to ");
    Serial.println(gate->id);
    this->webController.startListening(gate);
}

void Starter::gateStopListening(GateClient *gate) {
    Serial.print("Send stop listening to ");
    Serial.println(gate->id);
    this->webController.stopListening(gate);
}

void Starter::resetLap() {
    this->trackHandler.resetLap();
    this->gateStartListening(this->trackHandler.getNextGate());
}

void Starter::startLap() {
    Serial.println("Starting lap");
    this->beep();
    this->trackHandler.startLap();
}

void Starter::stopLap() {
    Serial.println("Lap done");
    this->trackHandler.stopLap();
    this->beep();
}

void Starter::enableCalibrationMode() {
    this->startListening();
    this->webController.startListeningAll();
}