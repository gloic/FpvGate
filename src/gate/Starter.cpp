#include "Starter.h"
#include "../config/GateConfig.h"
#include "../structs/GateMode.h"

#include <vector>
#include <Arduino.h>
#include "OneButton.h"

Starter *Starter::instance = nullptr;

// Vector containing all registered gates on the network
std::vector <GateClient> gates;

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
    /*
    this->server().on("/test/reset", HTTP_GET, [](AsyncWebServerRequest* request) {
    instance->resetLap();    
    request->send(200, "text/plain", "OK");
  });
  */

    this->server().on("/api/gate/register", HTTP_POST, &Starter::onRegisterGate);
    this->server().on("/api/gate/passed", HTTP_POST, &Starter::onGatePassed);

    this->server().on("/api/test/track", HTTP_GET, &Starter::onTrackMode);
    this->server().on("/api/test/race", HTTP_GET, &Starter::onRaceMode);

//    this->server().on("/test/laptime", HTTP_POST, [](AsyncWebServerRequest *request) {
//        request->send(200, "text/plain", String(instance->trackHandler.getLastLapTime()));
//    });
//    this->server().on("/test/bestlap", HTTP_POST, [](AsyncWebServerRequest *request) {
//        request->send(200, "text/plain", String(instance->trackHandler.getBestLapTime()));
//    });
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
    int id = instance->registerGate(clientIP);

    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "");
    response->addHeader("test", "Test");
    request->send(200, "text/plain", String(id));
}

void Starter::onTrackMode(AsyncWebServerRequest *request) {
    Serial.println("Starting track mode");
    instance->enableTrackMode();
}

void Starter::onRaceMode(AsyncWebServerRequest *request) {
    Serial.println("Starting race mode");
    instance->enableRaceMode();
}

void Starter::onGatePassed(AsyncWebServerRequest *request) {
    Serial.println("Gate passed !");
    int id = instance->getParamFromRequest("id", request).toInt();
    auto *gate = instance->getGateClientFromId(id);
    instance->handleGatePassed(gate);
    request->send(200, "text/plain", "OK");
}

void Starter::handleGatePassed(GateClient* gate) {
    Serial.print("Gate passed, id=");
    Serial.println(gate->id);

    if (this->trackHandler.isTrackMode()) {
        Serial.println("Track mode, add gate to track");
        int trackSize = this->trackHandler.addGateToTrack(gate);
        if(trackSize == 1) {
            // when first gate is passed, starter can listen to close the track
            this->startListening();
            Serial.println("...and start listening at track has at least one gate");
        }
    } else if (this->trackHandler.isRaceMode()) {
        Serial.print("Next gate index = ");
        Serial.println(this->trackHandler.getNextGateIndex());

        if(gate->id == this->trackHandler.getNextGate()->id) {
            Serial.println("The gate is the expected");
            if (this->trackHandler.hasNextGate()) {
                this->trackHandler.incrementNextGateIndex();
                Serial.print("Next gate index is ");
                Serial.println(this->trackHandler.getNextGateIndex());
                this->gateStartListening(gate);
            } else {
                Serial.println("no next gate, Starter is next : start listening");
                // no next gate, Starter is next
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

int Starter::registerGate(String ip) {
    Serial.println("Registering a gate");
    int id = gates.size();
    gates.push_back(GateClient{id, ip});
    Serial.print("Gate registered : ");
    Serial.print(ip);
    Serial.print(" with id = ");
    Serial.println(id);
    return id;
}

void Starter::loop() {
    buttonReset.tick();

    bool passed = false;
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
    this->startListeningAll();
}

void Starter::enableRaceMode() {
    Serial.println("GO");
    this->beep();
    this->beep();
    this->trackHandler.setRaceMode();
    // Only Starter should listen
    this->startListening();
}

void Starter::startListeningAll() {
    for (auto &gate: gates) {
        this->gateStartListening(&gate);
    }
}

void Starter::gateStartListening(GateClient *gate) {
    if (DEV_MODE == 1) {
        Serial.print("DEV MODE : send start listening to ");
        Serial.println(gate->id);
        return;
    } else {
        Serial.print("Send start listening to ");
        Serial.println(gate->id);
        this->webController.startListening(gate);
    }
}

void Starter::gateStopListening(GateClient *gate) {
    if (DEV_MODE == 1) {
        Serial.print("DEV MODE : send stop listening to ");
        Serial.println(gate->id);
        return;
    } else {
        Serial.print("Send stop listening to ");
        Serial.println(gate->id);
        this->webController.stopListening(gate);
    }
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
    this->startListeningAll();
}

GateClient *Starter::getGateClientFromId(int id) {
    for (auto &gate : gates) {
        if (gate.id == id) {
            return &gate;
        }
    }
    return nullptr;
}