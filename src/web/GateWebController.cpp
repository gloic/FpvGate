#include "GateWebController.h"

int GateWebController::doRegister(String ipStarter) {
    String url = getUrl(ipStarter, "/api/gate/register");
    return post(url).toInt();
}

void GateWebController::doNotifyPassage(String ipStarter) {
    String url = getUrl(ipStarter, "/api/gate/passed");
    post(url).toInt();
}

String GateWebController::post(String url) {
    String result = "";
    http.begin(wifiClient, url);
    int httpCode = http.POST("");
    if (httpCode == HTTP_CODE_OK) {
        result = http.getString();
    }
    http.end();

    return result;
}

String GateWebController::getUrl(String ipStarter, String endpoint) {
    return "http://" + ipStarter + endpoint;
}