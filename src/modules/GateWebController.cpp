#include "../headers/modules/GateWebController.h"

int GateWebController::registerOnStarter() {
    int result = -1;
    char url[100];
    snprintf(url, sizeof(url), "http://%s/api/gate/register", this->_ipStarter);
    
    http.begin(wifiClient, url);
    int httpCode = http.POST("");
    // NOT SURE
    if (httpCode == HTTP_CODE_OK) {
        result = http.getString().toInt();
    }
    http.end();
    return result;
}

void GateWebController::notifyPass(String id) {
    char url[100];
    snprintf(url, sizeof(url), "http://%s/api/gate/passed", this->_ipStarter);
    
    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String payload = "id=" + id;
    http.POST(payload);
    http.end();
}

void GateWebController::setIpStarter(String ip) {
    this->_ipStarter = ip;
}


// HTTPClient* GateWebController::post(char* url, String payload) {
//     http.begin(wifiClient, url);
//     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//     int result = http.POST(payload);
//     http.end();
//     return &http;
// }