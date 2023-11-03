#include "GateService.h"

void GateService::setIpStarter(String ip) {
    ipStarter = ip;
}

int GateService::registerGate() {
    return webController.doRegister(ipStarter);
}

void GateService::notifyPassage() {
    webController.doNotifyPassage(ipStarter);
}