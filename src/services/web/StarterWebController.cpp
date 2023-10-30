#include "StarterWebController.h"

#include "../../structs/GateClient.h"
#include "../../config/GateConfig.h"

constexpr const char* URL_PREFIX = "http://";
constexpr const char* DEFAULT_PORT = "80";


void StarterWebController::listen(GateClient *gate, String entrypoint) {
    String url = this->getUrl(gate, entrypoint);
    Serial.print("Url for listen : ");
    Serial.println(url);
    
    http.begin(wifiClient, url);
    http.setTimeout(5000);
    http.POST("");
    http.end();
}

int StarterWebController::registerGate(String ip, boolean isMock) {
    int id = gates.size();
    gates.push_back(GateClient{id, ip, isMock});

    Serial.print("Gate registered : ");
    Serial.print(ip);
    Serial.print(" with id = ");
    Serial.println(id);
    Serial.print(" and is mock = ");
    Serial.println(isMock);
    return id;
}

void StarterWebController::startListeningAll() {
    for (auto &gate: gates) {
        this->startListening(&gate);
    }
}

GateClient *StarterWebController::getGateClientFromId(int id) {
    for (auto &gate : gates) {
        if (gate.id == id) {
            return &gate;
        }
    }
    return nullptr;
}

GateClient *StarterWebController::getGateClientFromIp(String ip) {
    for (auto &gate : gates) {
        if (gate.ip == ip) {
            return &gate;
        }
    }
    return nullptr;
}

String StarterWebController::getUrl(GateClient *gate, String entrypoint) {
    String hostame = gate->ip;
    String port = gate->isMock ? DEV_MOCK_PORT_WS : DEFAULT_PORT;
    return URL_PREFIX + hostame + ':' + port + entrypoint;
}