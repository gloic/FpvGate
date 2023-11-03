#pragma once
#include <server/GateClients.h>
#include <clients/StarterClient.h>

class StarterService {
    public:
        void registerGate(String ip);
        void notifyPassage();
};