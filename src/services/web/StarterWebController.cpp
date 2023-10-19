#include "StarterWebController.h"

#include "../../structs/GateClient.h"

void StarterWebController::listen(GateClient *gate, String arg) {
    char url[100];
    snprintf(url, sizeof(url), "http://%s/api/gate/%s", gate->ip.c_str(), arg);
    http.begin(wifiClient, url);
    http.setTimeout(5000); // should be 5 sec
    http.POST("");
    http.end();
}