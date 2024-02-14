#pragma once

#include <server/model/GateClient.h>
#include <utils/WebUtils.h>
#include <server/model/enums/ActionWhenPass.h>

class ListenExecutor {
    public:
        ListenExecutor() {};

        void startStarter(ActionWhenPass whenPass);
        void stopStarter();

        void startGates(ActionWhenPass whenPass);
        void stopGates();
    private:
        WebUtils webUtils;
        void sendToGates(String state, ActionWhenPass whenPass);
        void sendToStarter(String state, ActionWhenPass whenPass);

        void listen(GateClient& gate, String state, ActionWhenPass whenPass);
};