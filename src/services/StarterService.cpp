#include "StarterService.h"

void StarterService::registerGate(String ip) {
    GateClients::getInstance().setStarter(ip);
}

void StarterService::notifyPassage() {
}