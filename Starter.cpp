#include "Starter.h"
#include <vector>
#include <OneButton.h>

#define resetPin 12

Starter* Starter::instance = nullptr;
Mode currentMode;

/*
  Led RGB status :
  - RED = IDLE
  - BLUE = TRACK MODE
  - GREEN = RACE MODE

  Button reset :
  - Press = Reset race (in race mode)
  - Long press = Reset track (set race mode)
*/

// Vector containing all registered gates on the network
std::vector<GateClient> gates;
// Vector containing gates for track mode
std::vector<GateClient> trackGates;

unsigned long startTime = 0;
unsigned long elapsedTime = 0;
int nextGateIndex = -1;

OneButton buttonReset(resetPin, true);

void Starter::setup() {
  Serial.println("Setup Starter");
  this->setupWifi();
  this->setupWebController();
  this->setupGPIO();

  EspBase::startWebServer();

  currentMode = Mode::INIT;
  instance->isListening = false;

  Serial.println("End of setup Starter");
}

void Starter::setupWifi() {
  // EspBase::setupAPWifi(SECRET_SSID, SECRET_PASS);
  EspBase::setupWifi(SECRET_SSID, SECRET_PASS);
}

void Starter::setupWebController() {
  Gate::setupWebController();
  Serial.println("Starter::setupWebController");

  this->webServer.on("/api/gate/register", HTTP_POST, &Starter::onRegisterGate);
  this->webServer.on("/api/gate/passed", HTTP_POST, &Starter::onGatePassed);

  this->webServer.on("/api/test/track", HTTP_GET, &Starter::onTrackMode);
  this->webServer.on("/api/test/race", HTTP_GET, &Starter::onRaceMode);
}

void Starter::setupGPIO() {
  Gate::setupGPIO();
  buttonReset.attachClick(&Starter::onButtonResetPress);
  buttonReset.attachLongPressStart([]() {
    instance->enableTrackMode();
  });
}

void Starter::onRegisterGate(AsyncWebServerRequest* request) {
  Serial.println("onRegisterGate");
  String clientIP = request->client()->remoteIP().toString();
  int id = instance->registerGate(clientIP);
  request->send(200, "text/plain", String(id));
}

void Starter::onTrackMode(AsyncWebServerRequest* request) {
  Serial.println("Starting track mode");
  instance->enableTrackMode();
}

void Starter::onRaceMode(AsyncWebServerRequest* request) {
  Serial.println("Starting race mode");
}

void Starter::onGatePassed(AsyncWebServerRequest* request) {
  Serial.println("Gate passed !");
  int id = instance->getParamFromRequest("id", request).toInt();
  Serial.print("id=");
  Serial.println(id);
  if (instance->isMode(Mode::TRACK) && trackGates.size() == 0) {
    for (const auto& gate : gates) {
      if (gate.id == id) {
        trackGates.push_back(gate);
        break;
      }
    }
  } else if (instance->isMode(Mode::RACE) && id == nextGateIndex) {
    GateClient* gateClient = &trackGates[id];
    // TODO will be deleted when "stop listening once passed" will be implemented on Gate's side
    instance->stopListening(gateClient);
    bool gatesLeft = nextGateIndex < trackGates.size() - 1;
    if (gatesLeft) {
      // notify next gate to listen
      instance->startListening(&trackGates[nextGateIndex++]);
    } else {
      // no next gate, Starter is next
      instance->isListening = true;
    }
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

  bool passed = false;
  if (this->isListening) {
    passed = Gate::checkPass();    
  }

  if (!passed) {
    return;
  }

  Serial.println("Started passed !");
  if (this->isMode(Mode::TRACK)) {
    if (trackGates.size() > 0) {
      Serial.println("Track mode finished, starting race mode");
      this->isListening = false;
      
      // Workaround, a delay is necessary to avoid instant end of race mode
      delay(5000);
      this->enableRaceMode();      
    }
  } else if (this->isMode(Mode::RACE)) {
    if (startTime == 0) {
      this->startLap();
    } else {
      this->stopLap();
    }
  }
}

void Starter::onButtonResetPress() {
  Serial.println("onButtonResetPress");
  if (instance->isMode(Mode::RACE)) {
    instance->resetLap();
  }
}

void Starter::enableTrackMode() {
  Serial.println("enableTrackMode");
  currentMode = Mode::TRACK;
  trackGates.clear();

  // LED = BLUE
  this->startListeningAll();
  this->isListening = true;
}

void Starter::enableRaceMode() {
  Serial.println("GO");
  currentMode = Mode::RACE;
  // Only Starter must listen
  this->isListening = true;
}

void Starter::startListeningAll() {
  // Notify all gates to start listening
  for (const auto& gate : gates) {
    this->startListening(&gate);
  }
}

void Starter::startListening(const GateClient* gate) {
  Serial.print("Send start listening to ");
  Serial.println(gate->id);
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/start", gate->ip.c_str());
  http.begin(wifiClient, url);
  http.POST("");
  http.end();
}

void Starter::stopListening(const GateClient* gate) {
  Serial.print("Send stop listening to ");
  Serial.println(gate->id);
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/stop", gate->ip.c_str());
  http.begin(wifiClient, url);
  http.POST("");
  http.end();
}

bool Starter::isMode(Mode mode) {
  return currentMode == mode;
}

void Starter::resetLap() {
  Serial.println("Lap reset");
  startTime = 0;
  elapsedTime = 0;
  nextGateIndex= 0;
}

void Starter::startLap() {
  startTime = millis();
  nextGateIndex++;
}

void Starter::stopLap() {
  elapsedTime = millis() - startTime;
  Serial.print("Lap finished in ");
  Serial.print(elapsedTime / 1000);
  Serial.println("s");
  startTime = 0;
}
