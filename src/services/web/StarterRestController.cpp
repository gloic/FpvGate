#include "StarterRestController.h"
#include "ArduinoLog.h"

Starter *StarterRestController::instance = nullptr;

void StarterRestController::setup() {
    server.on("/api/gate/register", HTTP_POST, &StarterRestController::onRegisterGate);
    server.on("/api/gate/passed", HTTP_POST, &StarterRestController::onGatePassed);
}

void StarterRestController::onRegisterGate(AsyncWebServerRequest *request) {
    Log.infoln("onRegisterGate");
    String clientIP = request->client()->remoteIP().toString();
    boolean isMock = request->getHeader("isMock") != nullptr;
    int id = instance->webController.registerGate(clientIP, isMock);
    request->send(200, "text/plain", String(id));
}

void StarterRestController::onGatePassed(AsyncWebServerRequest *request) {
    Log.infoln("Gate passed !");
    String clientIP = request->client()->remoteIP().toString();
    Log.infoln("Client ip: %s", clientIP);

    String responseBehavior = instance->webController.handleGatePass(clientIP);

    // auto *gate = instance->gatesManager.getGateClientFromIp(clientIP);
    // instance->handleGatePassed(*gate);
    // String responseBehavior = instance->isCalibrationMode ? "continue" : "stop";
    request->send(200, "text/plain", responseBehavior);
}