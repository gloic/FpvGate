#include "GateClients.h"
#include <ArduinoLog.h>

GateClients* GateClients::instance = nullptr;

int GateClients::add(String ip) {
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

GateClient& GateClients::findByIp(String& ip) {
    auto it = std::find_if(gates.begin(), gates.end(), [&](const GateClient& gate){return gate.getIp() == ip;});
    if (it != gates.end()) {
        return *it;
    } else {
        throw std::runtime_error("No such IP found.");
    }
}

GateClient GateClients::createGateClient(String ip) {
    int id = gates.size();
    return GateClient{id, ip};
}

int GateClients::addGate(const GateClient &gate) {
    gates.push_back(gate);
    return gate.getId();
}

void GateClients::setStarter(String ip) {
    starter = StarterClient(ip);
}