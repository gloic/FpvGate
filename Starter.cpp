#include "Starter.h"
#include <vector>

struct Gate {
  String ip;
  int id;  
};

std::vector<Gate> gates;

#define resetPin 12

void Starter::setupWebController() {
  Gate::setupWebController();

  server().on("/api/gate/register", HTTP_POST, [](AsyncWebServerRequest * request) {
	String clientIP = request->client()->remoteIP().toString();
    int id = registerGate(clientIP);
    request->send(200, "text/plain", String(id));
  });
  
  server().on("/api/gate/{id}/passed", HTTP_POST, [](AsyncWebServerRequest * request) {
	String id = request->pathArg("id");
    request->send(200, "text/plain", "OK");
  });
  
  server().on("/api/gate/track", HTTP_GET, onTrackMode);
  server().on("/api/gate/race", HTTP_GET, onRaceMode);
}

void Starter::setupGPIO() {
  Gate::setupGPIO();
  pinMode(resetPin, INPUT);
}

void Starter::setupWifi() {
	EspBase::setupAPWifi(SECRET_SSID, SECRET_PASS);
}

/**
 * Register a new gate
**/
int Starter::registerGate(String ip) {
  int id = gates.size();
  gates.push_back({ip, id});
  Serial.print("Gate registered : ");
  Serial.print(ip);
  Serial.print(" with id = ");
  Serial.println(id);  
  return id;
}

void Starter::startListening(Gate * gate) {
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/start", gate->ip.c_str());
  http.begin(wifiClient, url.c_str());
  http.POST("");
  http.end();
}

void Starter::stopListening(Gate * gate) {
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/stop", gate->ip.c_str());
  http.begin(wifiClient, url.c_str());
  http.POST("");
  http.end();
}

vod Starter::onTrackMode(AsyncWebServerRequest * request) {
	
}