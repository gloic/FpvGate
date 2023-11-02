#include "GatesManager.h"

#include "ArduinoLog.h"

int GatesManager::registerGate(String ip, boolean isMock) {
    auto *gate = getGateClientFromIp(ip);
    if(&gate != nullptr) {
        Log.warningln("Ip already registered: %s for %p", ip, gate);
        return gate->id;
    } else {
        auto newGate = createGateClient(ip, isMock);
        Log.infoln("Gate registered : %p", newGate);
        return addGate(newGate);
    }
}

GateClient GatesManager::createGateClient(String ip, boolean isMock) {
    int id = gates.size();
    return GateClient{id, ip, isMock};
}

int GatesManager::addGate(const GateClient& gate) {
    gates.push_back(gate);
    return gate.id;
}

GateClient* GatesManager::getGateClientFromIp(String& ip) {
    try {
        return &findByIp(ip);
    } catch (std::runtime_error& e) {
        return nullptr;
    }
}

GateClient& GatesManager::findByIp(String& ip) {
    auto it = std::find_if(gates.begin(), gates.end(), [&](const GateClient& gate){return gate.ip == ip;});
    if (it != gates.end()) {
        return *it;
    } else {
        throw std::runtime_error("No such IP found.");
    }
}