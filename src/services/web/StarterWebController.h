#pragma once

#include "../../structs/GateClient.h"
#include "entrypoints/starter/StarterEntryPoints.h"

#include <Arduino.h>
#include <HTTPClient.h>

class StarterWebController {
    public:
        void startListening(GateClient *gate) {listen(gate, StarterEntryPoints::START_LISTEN);}
        void stopListening(GateClient *gate)  {listen(gate, StarterEntryPoints::STOP_LISTEN);}
        void startListeningAll();
        int registerGate(String ip, boolean isMock);
        GateClient* getGateClientFromId(int id);
        GateClient* getGateClientFromIp(String ip);
    private:

        WiFiClient wifiClient;
        HTTPClient http;
        std::vector <GateClient> gates;

        void listen(GateClient *gate, String arg);
        String getUrl(GateClient *gate, String path);
};