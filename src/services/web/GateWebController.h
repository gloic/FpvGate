#pragma once

#include <Arduino.h>
#include <HTTPClient.h>

class GateWebController {
    public:
        void setIpStarter(String ip);
        int registerOnStarter();
        boolean notifyPass(String id);

    private:
        const char* PATH_REGISTER = "/api/gate/register";
        const char* PATH_NOTIFY = "/api/gate/passed";
        
        WiFiClient wifiClient;
        HTTPClient http;
        String ipStarter;

        // HTTPClient* post(char* url, String payload);
        String getUrl(String path);

};