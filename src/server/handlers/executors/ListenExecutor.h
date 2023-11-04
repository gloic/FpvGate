#pragma once

#include <server/model/GateClient.h>
#include <utils/WebUtils.h>
#include <server/model/enums/ActionWhenPass.h>

class ListenExecutor {
    public:
        ListenExecutor() {};
        void startStarter(ActionWhenPass whenPass) {starterListen("start", whenPass);}
        void stopStarter() {starterListen("stop", ActionWhenPass::STOP);};
        void startAll(ActionWhenPass whenPass) {listenAll("start", whenPass);};
        void stopAll() {listenAll("stop", ActionWhenPass::STOP);};
    private:
        WebUtils webUtils;
        void listenAll(String action, ActionWhenPass whenPass);
        void listen(GateClient& gate, String action, ActionWhenPass whenPass);
        void starterListen(String action, ActionWhenPass whenPass);
};