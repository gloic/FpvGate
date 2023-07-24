#include "headers/Starter.h"

#include <Arduino.h>
#include <vector>
#include "OneButton.h"
#include "headers/GateConfig.h"
#include "headers/structs/GateMode.h"

Starter *Starter::instance = nullptr;
//GateMode currentMode;

// Vector containing all registered gates on the network
std::vector <GateClient> gates;
// Vector containing gates for track mode
std::vector <GateClient> trackGates;

unsigned long startTime = 0;
unsigned long elapsedTime = 0;

int nextGateIndex = -1;

OneButton buttonReset(PIN_RESET, true);

void Starter::setup() {
    Serial.println("Setup Starter");
    this->setupWifi();
    this->setupWebController();
    this->setupGPIO();
    EspBase::startWebServer();

    trackHandler.setMode(GateMode::INIT);
    instance->isListening = false;

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

    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Hello World!");
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
    Serial.print("id=");
    Serial.println(id);

    Serial.print("nextGateIndex=");
    Serial.println(nextGateIndex);

    Serial.print("trackGates size=");
    Serial.println(trackGates.size());

    Serial.print("trackmode=");
    Serial.println(instance->trackHandler.getMode());

    // WHY THIS CHECK ON THE SIZE ? is it for dev ?
    if (instance->trackHandler.isTrackMode() && trackGates.size() == 0) {

        if (trackGates.size() == 0) {
            // First gate passed, starter can listen to close track
            instance->isListening = true;
        }
        for (const auto &gate: gates) {
            if (gate.id == id) {
                trackGates.push_back(gate);
                break;
            }
        }
        // CPT - CEST PAS JUSTE DU TOUT NEXTGATEINDEX == ID
    } else if (instance->trackHandler.isRaceMode() && id == nextGateIndex) {
        GateClient *gateClient = &trackGates[id];

        bool gatesLeft = nextGateIndex < trackGates.size() - 1;
        if (gatesLeft) {
            nextGateIndex++;
            Serial.print("notify next gate to listen : ");
            Serial.println(nextGateIndex);
            // notify next gate to listen
            instance->startListening(&trackGates[nextGateIndex]);
        } else {
            Serial.println("no next gate, Starter is next : start listening");
            // no next gate, Starter is next
            instance->isListening = true;
        }
    } else {
        Serial.println("Another gate was passed !");
        Serial.print("passed=");
        Serial.println(id);
        Serial.print("expected=");
        Serial.println(nextGateIndex);
    }
    request->send(200, "text/plain", "OK");
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
    if (this->isListening) {
        passed = Gate::checkPass();
    }

    if (!passed) {
        return;
    }

    Serial.println("Started passed !");
    if (instance->trackHandler.isTrackMode()) {
        if (trackGates.size() > 0) {
            Serial.println("Track mode finished, starting race mode");
            this->isListening = false;

            // Workaround, a delay is necessary to avoid instant end of race mode
            delay(5000);
            this->enableRaceMode();
        }
    } else if (instance->trackHandler.isRaceMode()) {
        if (startTime == 0) {
            // DANGER - NOT SURE
            this->isListening = false;
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
    trackGates.clear();
    this->startListeningAll();
}

void Starter::enableRaceMode() {
    Serial.println("GO");
    Gate::beep();
    Gate::beep();
//    instance->stateLed.setMode(1);
    instance->trackHandler.setMode(GateMode::RACE);
    // Only Starter should listen
    this->isListening = true;
}

void Starter::startListeningAll() {
    // Notify all gates to start listening
    for (const auto &gate: gates) {
        this->startListening(&gate);
    }
}

void Starter::startListening(const GateClient *gate) {
    if (DEV_MODE == 1) {
        return;
    } else {
        Serial.print("Send start listening to ");
        Serial.println(gate->id);
        char url[100];
        snprintf(url, sizeof(url), "http://%s/api/gate/start", gate->ip.c_str());
        http.begin(wifiClient, url);
        http.setTimeout(5000); // should be 5 sec
        http.POST("");
        http.end();
    }
}

void Starter::stopListening(const GateClient *gate) {
    if (DEV_MODE == 1) {
        return;
    } else {
        Serial.print("Send stop listening to ");
        Serial.println(gate->id);
        char url[100];
        snprintf(url, sizeof(url), "http://%s/api/gate/stop", gate->ip.c_str());
        http.begin(wifiClient, url);
        http.setTimeout(5000); // should be 5 sec
        http.POST("");
        http.end();
    }
}

//bool Starter::isMode(GateMode mode) {
//    return currentMode == mode;
//}

void Starter::resetLap() {
    Serial.println("Lap reset");
    startTime = millis();
    //elapsedTime = 0;
    nextGateIndex = 0;
    // notify next gate to listen
    instance->startListening(&trackGates[nextGateIndex]);
}

void Starter::startLap() {
    Serial.println("Start lap");
    startTime = millis();
    nextGateIndex++;
}

void Starter::stopLap() {
    elapsedTime = (millis() - startTime) / 1000;
    Serial.print("Lap finished in ");
    Serial.print(elapsedTime);
    Serial.println("s");

//     Update last time
    bool newRecord = instance->trackHandler.setLapTime(elapsedTime);
    if(newRecord) {
        Serial.println("New record");
        Gate::beep();
    }
    Gate::beep();
    Serial.println("Lap done");

    this->isListening = false;
    this->resetLap();
}
