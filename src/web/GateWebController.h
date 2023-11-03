#pragma once

#include <HTTPClient.h>

class GateWebController {
    public:
        int doRegister(String ipStarter);
        void doNotifyPassage(String ipStarter);
    private:
        WiFiClient wifiClient;
        HTTPClient http;

        String post(String url);
        String getUrl(String ipStarter, String endpoint);
};