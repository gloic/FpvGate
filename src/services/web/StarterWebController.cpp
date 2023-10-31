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
    auto *gate = manager.getGateClientFromIp(ip);
    if(&gate != nullptr) {
        Log.infoln("Ip already registered: %s", ip);
        return gate->id;
    } else {
        GateClient newGate = GateClient{ip, isMock};
        Log.infoln("Gate registered : %p", newGate);
        return manager.addGate(newGate);
    }
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