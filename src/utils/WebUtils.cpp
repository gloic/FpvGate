#include "WebUtils.h"

String WebUtils::post(String url) {
    String result = "";
    http.begin(wifiClient, url);
    int httpCode = http.POST("");
    if (httpCode == HTTP_CODE_OK) {
        result = http.getString();
    }
    http.end();

    return result;
}

String WebUtils::getUrl(String ipStarter, String endpoint) {
    return "http://" + ipStarter + endpoint;
}