#pragma once

#include "Arduino.h"

class GateClient {
    public:
        GateClient() {};
        GateClient(int id, String ip): id(id), ip(ip) {}
        
        virtual bool isStarter() { return false; }
        const int getId() const {return id;};
        void setIp(String ip) {this->ip = ip;}
        const String& getIp() const {return ip;};
    private:
        int id;
        String ip;
};