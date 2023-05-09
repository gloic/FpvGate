#include "Starter.h"

struct Gate {
  String ip;
  String id;  
};

Gate gates[4];
int numberGate = 0;

void Starter::setupWebController() {
  Gate::setupWebController();

  server().on("/start", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "OK");
  });
}

void Starter::setupGPIO() {
  Gate::setupGPIO();
}

void Starter::onNotify(AsyncWebServerRequest * request) {
  
}

/**
 * Register a new gate
**/
int Starter::registerGate(String ip) {
  //gates[numberGate] = {ip, numberGate};
  Serial.print("Gate registered : ");
  Serial.println(ip);
  return numberGate++;
}