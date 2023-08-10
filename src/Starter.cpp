#include "headers/Starter.h"

#include <Arduino.h>
#include "OneButton.h"
#include <vector>
#include "headers/GateConfig.h"
#include "headers/structs/GateMode.h"

Starter *Starter::instance = nullptr;

// Vector containing all registered gates on the network
std::vector <GateClient> gates;

OneButton buttonReset(PIN_RESET, true);

void Starter::setup() {
    Serial.println("Setup Starter");
    this->setupWifi();
    this->setupWebController();
    this->setupGPIO();
    EspBase::startWebServer();

    trackHandler.setMode(GateMode::INIT);
    instance->stopListening();

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
    instance->handleGatePassed(id);
    request->send(200, "text/plain", "OK");
}

void Starter::handleGatePassed(int id) {
    Serial.print("id=");
    Serial.println(id);

    // Serial.print("nextGateIndex=");
    // Serial.println(nextGateIndex);

    // Serial.print("trackGates size=");
    // Serial.println(trackGates.size());

    Serial.print("trackmode=");
    Serial.println(this->trackHandler.getMode());

    // WHY THIS CHECK ON THE SIZE ? is it for dev ?
    if (this->trackHandler.isTrackMode() && this->trackHandler.getTrackGateSize() == 0) {

        if (this->trackHandler.getTrackGateSize() == 0) {
            // First gate passed, starter can listen to close track
            instance->startListening();
        }
        for (auto &gate: gates) {
            if (gate.id == id) {
                this->trackHandler.addGateToTrack(gate);
                break;
            }
        }
        // CPT - CEST PAS JUSTE DU TOUT NEXTGATEINDEX == ID
    } else if (instance->trackHandler.isRaceMode() /*&& id == nextGateIndex*/) {
        GateClient *gateClient = this->trackHandler.getNextGate();

        bool gatesLeft = this->trackHandler.hasNextGate();
        if (gatesLeft) {
            this->trackHandler.incrementNextGateIndex();
            // Serial.print("notify next gate to listen : ");
            // Serial.println(nextGateIndex);
            // notify next gate to listen
            instance->gateStartListening(this->trackHandler.getNextGate());
        } else {
            Serial.println("no next gate, Starter is next : start listening");
            // no next gate, Starter is next
            instance->startListening();
        }
    } else {
        Serial.println("Another gate was passed !");
        Serial.print("passed=");
        Serial.println(id);
        // Serial.print("expected=");
        // Serial.println(nextGateIndex);
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
//    this->stateLed.loop();

    bool passed = false;
    if (Gate::isListening()) {
        passed = Gate::checkPass();
    }

    if (!passed) {
        return;
    }

    Serial.println("Started passed !");
    if (this->trackHandler.isTrackMode()) {
        if (this->trackHandler.getTrackGateSize() > 0) {
            Serial.println("Track mode finished, starting race mode");
            Gate::stopListening();

            // Workaround, a delay is necessary to avoid instant end of race mode
            delay(5000);
            this->enableRaceMode();
        }
    } else if (instance->trackHandler.isRaceMode()) {
        if (this->trackHandler.getStartTime() == 0) {
            // DANGER - NOT SURE
            Gate::stopListening();
            this->startLap();
        } else {
            this->stopLap();
        }
    }
}

void Starter::onButtonResetPress() {
    Serial.println("onButtonResetPress");
//    if (instance->trackHandler.isRaceMode()) {
//        instance->resetLap();
//    }
}

void Starter::enableTrackMode() {
    Serial.println("enableTrackMode");
//    Gate::beep();
//    instance->stateLed.setMode(2);
    instance->trackHandler.setMode(GateMode::TRACK);
    // instance->trackHandler.clearTrackGates();
    this->startListeningAll();
}

void Starter::enableRaceMode() {
    Serial.println("GO");
    Gate::beep();
    Gate::beep();
//    instance->stateLed.setMode(1);
    instance->trackHandler.setMode(GateMode::RACE);
    // Only Starter should listen
    this->startListening();
}

void Starter::startListeningAll() {
    // Notify all gates to start listening
    for (auto &gate: gates) {
        this->gateStartListening(&gate);
    }
}

void Starter::gateStartListening(GateClient *gate) {
    if (DEV_MODE == 1) {
        return;
    } else {
        Serial.print("Send start listening to ");
        Serial.println(gate->id);
        this->webController.startListening(gate);
    }
}

void Starter::gateStopListening(GateClient *gate) {
    if (DEV_MODE == 1) {
        return;
    } else {
        Serial.print("Send stop listening to ");
        Serial.println(gate->id);
        this->webController.stopListening(gate);
    }
}

void Starter::resetLap() {
    this->trackHandler.resetLap();
    instance->gateStartListening(this->trackHandler.getNextGate());
}

void Starter::startLap() {
    this->trackHandler.startLap();
}

void Starter::stopLap() {
    Serial.println("Lap done");
    this->trackHandler.stopLap();
    Gate::beep();
    this->stopListening();
    
}
