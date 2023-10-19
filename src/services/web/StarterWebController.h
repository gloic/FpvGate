#ifndef StarterWebController_H
#define StarterWebController_H

#include "../../structs/GateClient.h"

#include <Arduino.h>
#include <HTTPClient.h>

class StarterWebController {
    public:
        void startListening(GateClient *gate) {listen(gate, "start");}
        void stopListening(GateClient *gate)  {listen(gate, "stop");}
        void startListeningAll();
        int registerGate(String ip);
        GateClient* getGateClientFromId(int id);
    private:
        WiFiClient wifiClient;
        HTTPClient http;
        std::vector <GateClient> gates;

        void listen(GateClient *gate, String arg);

};

#endif