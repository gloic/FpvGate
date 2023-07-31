#ifndef RestWebController_H
#define RestWebController_H

#include "WebController.h"

class RestWebController : public WebController {
public:
    RestWebController() {};
    void setup();
    void start();
    void notifyPass();
};

#endif