#include "LcdManager.h"

LcdManager* LcdManager::instance = nullptr;

LcdManager& LcdManager::getInstance() {
    if (!instance) {
        instance = new LcdManager();
    }
    return *instance;
}

void LcdManager::setup() {
    display.setup();
}

// void LcdManager::setTitle(String title) {
//     this->title = title;
// }