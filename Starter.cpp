#include "Starter.h"
#include <vector>
#include <OneButton.h>

#define resetPin 12

Starter* Starter::instance = nullptr;

enum Mode { INIT, TRACK, RACE };
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

struct GateClient {
  String ip;
  int id;
};

// Vector containing all registered gates on the network
std::vector<GateClient> gates;
// Vector containing gates for track mode
std::vector<GateClient> trackGates;

OneButton buttonReset(resetPin, true);

void Starter::setup() {
  Serial.println("Setup Starter");
  this->setupWifi();
  this->setupWebController();
  this->setupGPIO();
  
  EspBase::startWebServer();
  
  currentMode = Mode::INIT;
  //isListening = false;
  
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
  this->webServer.on("/api/gate/track", HTTP_GET, &Starter::onTrackMode);
  this->webServer.on("/api/gate/race", HTTP_GET, &Starter::onRaceMode);
}

void Starter::setupGPIO() {
  Gate::setupGPIO();
  //pinMode(resetPin, INPUT);
  buttonReset.attachClick(&Starter::onButtonResetPress);
  buttonReset.attachLongPressStart(&Starter::onButtonResetLongPress);
}

/**
 * Register a new gate
**/
int Starter::registerGate(String ip) {
  Serial.println("Registering a gate");
  int id = gates.size();
  gates.push_back(GateClient{ip, id});
  Serial.print("Gate registered : ");
  Serial.print(ip);
  Serial.print(" with id = ");
  Serial.println(id);
  return id;
}

void Starter::onRegisterGate(AsyncWebServerRequest* request) {
  Serial.println("onRegisterGate");
  String clientIP = request->client()->remoteIP().toString();
  int id = instance->registerGate(clientIP);
  request->send(200, "text/plain", String(id));
}

void Starter::startListening(String ip, String id) {
  Serial.print("Send start listening to ");
  Serial.println(id);
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/start", ip.c_str());
  http.begin(wifiClient, url);
  http.POST("");
  http.end();
}

void Starter::stopListening(String ip, String id) {
  Serial.print("Send stop listening to ");
  Serial.println(id);
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/stop", ip.c_str());
  http.begin(wifiClient, url);
  http.POST("");
  http.end();
}

void Starter::onTrackMode(AsyncWebServerRequest* request) {
  Serial.println("Starting track mode");
  this->enableTrackMode();
}

void Starter::onRaceMode(AsyncWebServerRequest* request) {
  Serial.println("Starting race mode");
}

void Starter::onGatePassed(AsyncWebServerRequest* request) {
  Serial.println("Gate passed !");
  String id = EspBase::getParamFromRequest("id", req);
  Serial.print("id=");
  Serial.println(id);
  if(this->isMode(Mode::TRACK) && trackGates.size() == 0) {
	  Serial.println("");
    // build a GateClient from request's information (ip and id)
    //   or retrieve the corresponding gate from the vector "gates" from its id
	for (const auto& gate : gates) {
		if (gate.id == id) {
			trackGates.push_back(gate);
			break;
		}
	}
	
  }
  request->send(200, "text/plain", "OK");
}

void Starter::loop() {
  buttonReset.tick();
  if(this->isMode(Mode::TRACK)) {    
    boolean passed = Gate::checkPass();
    // TODO : define if the track mode is starting or ending
  }  
}

void Starter::onButtonResetPress() {
  Serial.println("onButtonResetPress");
  // if (currentMode == Mode::RACE) {
  //   reinit current lap
  // }
}

void Starter::onButtonResetLongPress() {
  Serial.println("onButtonResetLongPress");
  this->enableTrackMode();
}

void Starter::enableTrackMode() {
  currentMode = Mode::TRACK;
  // LED = BLUE
  
  // Notify all gate to start listening
  for (const auto& gate : gates) {
    this->startListening(gate.ip, gate.id);
  }  
}

bool Starter::isMode(Mode mode) {
	return currentMode = mode;
}