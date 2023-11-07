#include "StarterWebController.h"

#include "../../structs/GateClient.h"
#include "../../config/GateConfig.h"

#include "ArduinoLog.h"

constexpr const char* URL_PREFIX = "http://";
constexpr const char* DEFAULT_PORT = "80";

void StarterWebController::listen(GateClient &gate, String entrypoint) {
    String url = getUrl(gate, entrypoint);
    Log.infoln("Url for listen : %s", url);
    
    http.begin(wifiClient, url);
    http.setTimeout(5000);
    http.POST("");
    http.end();
}

int StarterWebController::registerGate(String ip, boolean isMock) {
    return manager.registerGate(ip, isMock);
}

void StarterWebController::startListeningAll() {
    for (auto &gate: gates) {
        startListening(gate);
    }
}

String StarterWebController::getUrl(GateClient &gate, String entrypoint) {
    String hostame = gate.ip;
    String port = gate.isMock ? DEV_MOCK_PORT_WS : DEFAULT_PORT;
    return URL_PREFIX + hostame + ':' + port + entrypoint;
}

String StarterWebController::handleGatePass(String clientIP) {
    Log.infoln("StarterWebController::handleGatePass");
    Log.infoln("Client ip: %s", clientIP);
    auto *gate = manager.getGateClientFromIp(clientIP);
    // instance->handleGatePassed(*gate);
    // String response = instance->isCalibrationMode ? "continue" : "stop";
    return "";
}