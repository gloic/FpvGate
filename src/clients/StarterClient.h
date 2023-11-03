#pragma once

#include "GateClient.h"

class StarterClient : public GateClient {

    public:
        StarterClient(String ip): GateClient(0, ip) {}
};