#include "StarterRestController.h"
#include "ArduinoLog.h"

StarterRestController *StarterRestController::instance = nullptr;

void StarterRestController::setup(AsyncWebServer &server) {
    Log.infoln("StarterRestController::setup");
    server.on("/api/gate/register", HTTP_POST, &StarterRestController::onRegisterGate);
    server.on("/api/gate/passed", HTTP_POST, &StarterRestController::onGatePassed);
}

void StarterRestController::onRegisterGate(AsyncWebServerRequest *request) {
    Log.infoln("StarterRestController::onRegisterGate");
    String clientIP = request->client()->remoteIP().toString();
    boolean isMock = request->getHeader("isMock") != nullptr;
    
    int id = instance->webController.registerGate(clientIP, isMock);
    request->send(200, "text/plain", String(id));
}

void StarterRestController::onGatePassed(AsyncWebServerRequest *request) {
    Log.infoln("StarterRestController::onGatePassed");
    String clientIP = request->client()->remoteIP().toString();
    String response = instance->webController.handleGatePass(clientIP);
    request->send(200, "text/plain", response);
}