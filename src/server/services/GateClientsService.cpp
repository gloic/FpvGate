#include "GateClientsService.h"
#include <ArduinoLog.h>

GateClientsService* GateClientsService::instance = nullptr;


GateClientsService& GateClientsService::getInstance() {
    if (!instance) {
        instance = new GateClientsService();
    }
    return *instance;
}

GateClientsService::GateClientsService() {}

int GateClientsService::add(String ip) {
    GateClient& gate = findByIp(ip);
    if(&gate != nullptr) {
        Log.warningln("Ip already registered: %s for %p", ip, gate);
        return gate.getId();
    } else {
        auto newGate = createGateClient(ip);
        Log.infoln("Gate registered : %p", newGate);
        return addGate(newGate);
    }
}

GateClient& GateClientsService::findByIp(String& ip) {
    auto it = std::find_if(gates.begin(), gates.end(), [&](const GateClient& gate){return gate.getIp() == ip;});
    if (it != gates.end()) {
        return *it;
    } else {
        throw std::runtime_error("No such IP found.");
    }
}

GateClient GateClientsService::createGateClient(String ip) {
    int id = gates.size();
    return GateClient{id, ip};
}

int GateClientsService::addGate(const GateClient &gate) {
    gates.push_back(gate);
    return gate.getId();
}

void GateClientsService::setStarter(String ip) {
    starter = StarterClient(ip);
}