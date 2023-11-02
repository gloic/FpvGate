#pragma once

#include <vector>
#include "../structs/GateClient.h"

class GatesManager {
    public:
        GatesManager() {}

        GateClient *getGateClientFromIp(String &ip);
        int registerGate(String ip, boolean isMock);
    private:
        std::vector<GateClient> gates;
        
        GateClient &findByIp(String &ip);
        int addGate(const GateClient &gate);
        GateClient createGateClient(String ip, boolean isMock);
};