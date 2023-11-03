#pragma once

#include <HTTPClient.h>

class WebUtils {
    public:
        String post(String url);
        String getUrl(String ipStarter, String endpoint);
    private:
        WiFiClient wifiClient;
        HTTPClient http;
};