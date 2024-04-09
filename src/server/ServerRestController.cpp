#include "ServerRestController.h"
#include <server/FpvGateServer.h>
#include <ArduinoLog.h>
#include <config/GateEndPoints.h>

void ServerRestController::setup(AsyncWebServer &webServer) {
    Log.infoln("ServerRestController");
    webServer.on(REGISTER, HTTP_POST, &ServerRestController::onRegister);
    webServer.on(PASSED, HTTP_POST, &ServerRestController::onPass);
}

void ServerRestController::onRegister(AsyncWebServerRequest *request) {
    String clientIP = request->client()->remoteIP().toString();
    int id = GateManager::getInstance().add(clientIP);
    request->send(200, "text/plain", String(id));
}

void ServerRestController::onPass(AsyncWebServerRequest *request) {
    int id = request->getHeader("id")->value().toInt();
    Log.infoln("Received passage notification from ip '%s'. Id from request is %d", request->client()->remoteIP().toString(), id);
    FpvGateServer::getInstance().onGatePassage(id);
    request->send(200, "text/plain", "OK");
}