#pragma once

#include "Arduino.h"

class GateClient {
    public:
        GateClient(int id, String ip): id(id), ip(ip) {}

        int getId() const {return id;};
        String getIp() const {return ip;};
    private:
        int id;
        String ip;
};