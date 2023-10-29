#include "GateWebController.h"
#include "../../config/GateConfig.h"

constexpr const char* URL_PREFIX = "http://";
constexpr const char* DEFAULT_PORT = "80";

int GateWebController::registerOnStarter() {
    int result = -1;

    String url = this->getUrl(PATH_REGISTER);
    Serial.print("Url complete : ");
    Serial.println(url);

    http.begin(wifiClient, url);
    int httpCode = http.POST("");
    if (httpCode == HTTP_CODE_OK) {
        result = http.getString().toInt();
    }
    http.end();
    
    return result;
}

boolean GateWebController::notifyPass(String id) {
    String url = this->getUrl(PATH_NOTIFY);
    Serial.print("Url complete : ");
    Serial.println(url);

    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String payload = "id=" + id;
    int statusCode = http.POST(payload);

    boolean result = GATE_DEFAULT_CONTINUE_LISTENING;
    if (statusCode == HTTP_CODE_OK) {
        result = http.getString() == "stop";
    }
    http.end();

    return result;
}

void GateWebController::setIpStarter(String ip) {
    this->ipStarter = ip;
}

String GateWebController::getUrl(String path) {
    String hostame = DEV_MODE ? DEV_IP_STARTER : this->ipStarter;
    String port = DEV_MODE ? DEV_PORT_WS : DEFAULT_PORT;
    return URL_PREFIX + hostame + ':' + port + path;
}

// HTTPClient* GateWebController::post(char* url, String payload) {
//     http.begin(wifiClient, url);
//     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//     int result = http.POST(payload);
//     http.end();
//     return &http;
// }