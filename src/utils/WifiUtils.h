#pragma once

#include "WiFi.h"
#include <Secrets.h>

class WifiUtils {
    public:
        WifiUtils() {}
        void connect(String ssid, String password);
        void createAccessPoint(String ssid, String password);
        String getLocalIp();
        String getGatewayIP();
};