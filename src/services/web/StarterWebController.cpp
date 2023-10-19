#include "StarterWebController.h"

#include "../../structs/GateClient.h"
#include "../../config/GateConfig.h"

void StarterWebController::listen(GateClient *gate, String arg) {
    char url[100];
    snprintf(url, sizeof(url), "http://%s/api/gate/%s", gate->ip.c_str(), arg);
    Serial.print("Send request : ");
    Serial.println(url);

    if(DEV_MODE == 0) {
        http.begin(wifiClient, url);
        http.setTimeout(5000); // should be 5 sec
        http.POST("");
        http.end();
    }
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