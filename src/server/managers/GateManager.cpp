#include "GateManager.h"
#include <ArduinoLog.h>

GateManager* GateManager::instance = nullptr;

GateManager& GateManager::getInstance() {
    if (!instance) {
        instance = new GateManager();
    }
    return *instance;
}

int GateManager::add(String ip) {
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

GateClient GateManager::createGateClient(String ip) {
    int id = gates.size();
    return GateClient{id, ip};
}

int GateManager::addGate(const GateClient &gate) {
    gates.push_back(gate);
    return gate.getId();
}

int GateManager::setStarter(Starter& starterPtr, String ip) {
    Log.infoln("setStarter");
    starterClient = StarterClient();
    Log.infoln("ip=%s", ip);
    starterClient.setIp(ip);
    starterClient.setPtr(&starterPtr); // i don't know what i'm doing
    return starterClient.getId();
}

GateClient& GateManager::findByIp(String& ip) {
    auto it = std::find_if(gates.begin(), gates.end(), [&](const GateClient& gate){return gate.getIp() == ip;});
    if (it != gates.end()) {
        return *it;
    } else {
        Log.errorln("Can't find by gate by ip, '%s' not found", ip);
        throw std::runtime_error("No such IP found.");
    }
}

GateClient& GateManager::findById(int id) {
    auto it = std::find_if(gates.begin(), gates.end(), [&](const GateClient& gate){return gate.getId() == id;});
    if (it != gates.end()) {
        return *it;
    } else {
        Log.errorln("Can't find by gate by id, '%d' not found", id);
        throw std::runtime_error("No such ID found.");
    }
}

void GateManager::starterStartListen() {
    Log.infoln("starterStartListen");
    this->starterClient.getPtr().startListen();
}