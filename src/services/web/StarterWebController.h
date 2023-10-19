#ifndef StarterWebController_H
#define StarterWebController_H

#include "../../structs/GateClient.h"

#include <Arduino.h>
#include <HTTPClient.h>

class StarterWebController {
    public:
        void startListening(GateClient *gate) {listen(gate, "start");}
        void stopListening(GateClient *gate)  {listen(gate, "stop");}

    private:
        WiFiClient wifiClient;
        HTTPClient http;

        void listen(GateClient *gate, String arg);

};

#endif