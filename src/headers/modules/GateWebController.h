#ifndef GateWebController_H
#define GateWebController_H

#include <Arduino.h>
#include <HTTPClient.h>

class GateWebController {
    public:
        void setIpStarter(String ip);
        int registerOnStarter();
        void notifyPass(String id);

    private:
        WiFiClient wifiClient;
        HTTPClient http;
        String _ipStarter;

        // HTTPClient* post(char* url, String payload);

};

#endif