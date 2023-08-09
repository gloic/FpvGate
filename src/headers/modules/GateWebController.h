#ifndef GateWebController_H
#define GateWebController_H

#include <Arduino.h>
#include <HTTPClient.h>

class GateWebController {
    public:
        int registerOnStarter(String ip);
        void notifyPass(String ip, String id);

    private:
        WiFiClient wifiClient;
        HTTPClient http;

        HTTPClient* post(char* url, String payload);

};

#endif