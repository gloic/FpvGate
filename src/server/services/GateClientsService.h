#pragma once

#include <vector>
#include <clients/GateClient.h>
#include <clients/StarterClient.h>

class GateClientsService {
    public:
        static GateClientsService& getInstance();
        void setStarter(String ip);
        int add(String ip);
    protected:
        GateClientsService();
    private:
        static GateClientsService* instance;
        StarterClient starter;
        std::vector<GateClient> gates;

        GateClient createGateClient(String ip);
        int addGate(const GateClient &gate);
        GateClient& findByIp(String& ip);
};