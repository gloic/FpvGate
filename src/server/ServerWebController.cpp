#include "ServerWebController.h"

#include <server/services/GateManager.h>

void ServerWebController::setup(AsyncWebServer &webServer) {
    webServer.on("/api/gate/register", HTTP_POST, &ServerWebController::onRegister);
    webServer.on("/api/gate/passed", HTTP_POST, &ServerWebController::onPass);
}

void ServerWebController::onRegister(AsyncWebServerRequest *request) {
    String clientIP = request->client()->remoteIP().toString();
    int id = GateManager::getInstance().add(clientIP);
    request->send(200, "text/plain", String(id));
}

void ServerWebController::onPass(AsyncWebServerRequest *request) {
    String response = "coin";
    request->send(200, "text/plain", response);
}