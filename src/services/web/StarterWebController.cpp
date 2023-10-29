#include "StarterWebController.h"

#include "../../structs/GateClient.h"
#include "../../config/GateConfig.h"

constexpr const char* URL_PREFIX = "http://";
constexpr const char* DEFAULT_PORT = "80";


void StarterWebController::listen(GateClient *gate, String entrypoint) {
    char url[100];
    this->getUrl(gate, entrypoint);
    Serial.print("Url complete : ");
    Serial.println(url);
    
    http.begin(wifiClient, url);
    http.setTimeout(5000);
    http.POST("");
    http.end();
}

int StarterWebController::registerGate(String ip) {
    int id = gates.size();
    gates.push_back(GateClient{id, ip});

    Serial.print("Gate registered : ");
    Serial.print(ip);
    Serial.print(" with id = ");
    Serial.println(id);
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
    String port = DEV_MODE ? DEV_PORT_WS : DEFAULT_PORT;
    return URL_PREFIX + hostame + ':' + port + entrypoint;
}