#include "WebUtils.h"
#include <ArduinoLog.h>

String WebUtils::post(String ip, String path) {
    return post(ip, path, "");
}

String WebUtils::post(String ip, String path, String payload) {
    String url = getUrl(ip, path);

    Log.infoln("Sending POST request to %s", url.c_str());
    
    String result = "";
    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(payload);
    if (httpCode == HTTP_CODE_OK) {
        result = http.getString();
    }
    http.end();

    return result;
}

String WebUtils::getUrl(String ipStarter, String endpoint) {
    return "http://" + ipStarter + endpoint;
}