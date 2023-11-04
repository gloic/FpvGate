#pragma once

#include "Arduino.h"

class GateClient {
    public:
        GateClient(int id, String ip): id(id), ip(ip) {}
        const int getId() const {return id;};
        const String& getIp() const {return ip;};
    private:
        int id;
        String ip;
};