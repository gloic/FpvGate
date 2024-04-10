#pragma once

#include "GateClient.h"
#include "../../gate/Starter.h"

class StarterClient : public GateClient {
    public:
        StarterClient() : GateClient() {}
        bool isStarter() override { return true; }
        void setPtr(Starter* ptr) { this->starterPtr = ptr; }
        Starter& getPtr() { return *this->starterPtr;}
        // void setIp(String ip) { this->ip = ip;}
    private:
        Starter* starterPtr = nullptr;
};