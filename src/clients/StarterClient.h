#pragma once

#include "GateClient.h"

class StarterClient : public GateClient {

    public:
        StarterClient(): GateClient(0, "") {}
        StarterClient(String ip): GateClient(0, ip) {}
};