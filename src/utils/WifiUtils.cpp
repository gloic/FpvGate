#include "WifiUtils.h"

#include <ArduinoLog.h>

void WifiUtils::connect(String ssid, String password) {
    WiFi.begin(SECRET_SSID, SECRET_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Log.infoln("Wifi connected");
    Log.infoln("IP= %s", this->getLocalIp());
    Log.infoln("Gateway=%s", this->getGatewayIP());
}

void WifiUtils::createAccessPoint(String ssid, String password) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(SECRET_SSID, SECRET_PASS);
    Log.infoln("Wifi AP created. IP=%s", WiFi.softAPIP().toString());
}

String WifiUtils::getLocalIp() {
    return WiFi.localIP().toString();
}

String WifiUtils::getGatewayIP() {
    return WiFi.gatewayIP().toString();
}