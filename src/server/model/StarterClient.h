#pragma once

#include "GateClient.h"

class StarterClient : public GateClient {
    public:
        StarterClient(): GateClient() {}
        bool isStarter() override { return true; }
};