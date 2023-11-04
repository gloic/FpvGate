#include "ServerRestController.h"
#include <server/FpvGateServer.h>
#include <server/services/GateManager.h>
#include <ArduinoLog.h>

void ServerRestController::setup(AsyncWebServer &webServer) {
    webServer.on("/api/gate/register", HTTP_POST, &ServerRestController::onRegister);
    webServer.on("/api/gate/passed", HTTP_POST, &ServerRestController::onPass);
}

void ServerRestController::onRegister(AsyncWebServerRequest *request) {
    String clientIP = request->client()->remoteIP().toString();
    int id = GateManager::getInstance().add(clientIP);
    request->send(200, "text/plain", String(id));
}

void ServerRestController::onPass(AsyncWebServerRequest *request) {
    int id = request->getHeader("id")->value().toInt();
    Log.infoln("Receive passage notification from ip '%s'. Id from request is %d", request->client()->remoteIP().toString(), id);
    String response = FpvGateServer::getInstance().gatePassage(id);
    Log.infoln("Sending response: '%s'", response);
    request->send(200, "text/plain", response);
}