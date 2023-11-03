#include "ServerWebController.h"
#include <clients/GateClients.h>

void ServerWebController::setup(AsyncWebServer &webServer) {
    webServer.on("/api/gate/register", HTTP_POST, &ServerWebController::onRegister);
    webServer.on("/api/gate/passed", HTTP_POST, &ServerWebController::onPass);
}

void ServerWebController::onRegister(AsyncWebServerRequest *request) {
    String clientIP = request->client()->remoteIP().toString();
    // boolean isMock = request->getHeader("isMock") != nullptr;
    
    //int id = instance->webController.registerGate(clientIP, isMock);
    // TODO - Call GateRegisterService
    GateClients::getInstance().add();
}

void ServerWebController::onPass(AsyncWebServerRequest *request) {
}