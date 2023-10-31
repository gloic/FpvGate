#pragma once

#include <vector>
#include "../structs/GateClient.h"

class GatesManager {
    public:
        GatesManager() {}
        GateClient *getGateClientFromIp(String &ip);
        int addGate(const GateClient &gate);

    private:
        std::vector<GateClient> gates;
        
        GateClient &findByIp(String &ip);
        GateClient createGateClient(String ip, boolean isMock);
};