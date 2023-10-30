#include "GateWebController.h"
#include "../../config/GateConfig.h"

constexpr const char* URL_PREFIX = "http://";
constexpr const char* DEFAULT_PORT = "80";

int GateWebController::registerOnStarter(String ip) {
    int result = -1;

    String url = this->getUrl(ip, PATH_REGISTER);
    Serial.print("Url for register: ");
    Serial.println(url);

    http.begin(wifiClient, url);
    int httpCode = http.POST("");
    if (httpCode == HTTP_CODE_OK) {
        result = http.getString().toInt();
    }
    http.end();
    
    return result;
}

boolean GateWebController::notifyPass(String ip) {
    String url = this->getUrl(ip, PATH_NOTIFY);
    Serial.print("Url for notifyPass: ");
    Serial.println(url);

    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int statusCode = http.POST("");

    boolean result = GATE_DEFAULT_CONTINUE_LISTENING;
    if (statusCode == HTTP_CODE_OK) {
        result = http.getString() == "stop";
    }
    http.end();

    return result;
}

String GateWebController::getUrl(String ip, String path) {
    String hostame = DEV_MODE ? DEV_IP_STARTER : ip;
    return URL_PREFIX + hostame + ':' + DEFAULT_PORT + path;
}