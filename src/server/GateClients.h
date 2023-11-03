#pragma once

#include <vector>
#include <clients/GateClient.h>
#include <clients/StarterClient.h>

class GateClients {
    public:
        static GateClients& getInstance() {
            static GateClients instance;
            return instance;
        }
        void setStarter(String ip);
        int add(String ip);
    private:
        static GateClients* instance;
        GateClients();

        StarterClient starter;
        std::vector<GateClient> gates;

        GateClient createGateClient(String ip);
        int addGate(const GateClient &gate);
        GateClient& findByIp(String& ip);

};