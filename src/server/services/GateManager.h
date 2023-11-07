#pragma once

#include <vector>
#include <server/model/GateClient.h>
#include <server/model/StarterClient.h>

class GateManager {
    public:
        static GateManager& getInstance();
        int setStarter(String ip);
        int add(String ip);
        GateClient& findById(int id);
        std::vector<GateClient> findAll() {return gates;}
        StarterClient& getStarter() {return starter;}
    protected:
        GateManager();
    private:
        static GateManager* instance;
        StarterClient starter;
        std::vector<GateClient> gates;
        GateClient createGateClient(String ip);
        int addGate(const GateClient &gate);
        GateClient& findByIp(String& ip);
};