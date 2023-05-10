#include "Starter.h"
#include <vector>

Starter* Starter::instance = nullptr;

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

std::vector<GateClient> gates;
//#define resetPin 12

void Starter::setup() {
  Serial.println("Setup Starter");
  this->setupWifi();
  this->setupWebController();
  //this->setupGPIO();
  Serial.println("End of setup setupWebController");
  //isListening = false;
  EspBase::startWebServer();
  Serial.println("End of setup startWebServer");
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
}

/**
 * Register a new gate
**/
int Starter::registerGate(String ip) {
  Serial.println("Registering a gate");
  int id = gates.size();
  gates.push_back(GateClient{ ip, id });
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
}

void Starter::onRaceMode(AsyncWebServerRequest* request) {
  Serial.println("Starting race mode");
}

void Starter::onGatePassed(AsyncWebServerRequest* request) {
  Serial.println("Gate passed !");
  String id = "0"; 
  //request->pathArg(0);
  Serial.print("id=");
  Serial.println(id);
  request->send(200, "text/plain", "OK");
}

void Starter::checkPass() {
  //Gate::checkPass();
}