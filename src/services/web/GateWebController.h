#pragma once

#include <Arduino.h>
#include <HTTPClient.h>

class GateWebController {
    public:
        int registerOnStarter(String ip);
        boolean notifyPass(String ip);

    private:
        const char* PATH_REGISTER = "/api/gate/register";
        const char* PATH_NOTIFY = "/api/gate/passed";
        
        WiFiClient wifiClient;
        HTTPClient http;
        String ipStarter;

        String getUrl(String ip, String path);

};