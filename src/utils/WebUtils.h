#pragma once

#include <HTTPClient.h>

class WebUtils {
    public:
        WebUtils() {};
        String post(String ip, String path);
        String post(String ip, String path, String payload);
        String getUrl(String ipStarter, String endpoint);
    private:
        WiFiClient wifiClient;
        HTTPClient http;
};