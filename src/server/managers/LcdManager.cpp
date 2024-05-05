#include "LcdManager.h"

LcdManager* LcdManager::instance = nullptr;

LcdManager& LcdManager::getInstance() {
    if (!instance) {
        instance = new LcdManager();
    }
    return *instance;
}

void LcdManager::show() {
    Log.infoln("LcdManager::show");
    
    display.showTop(title);
    display.showBottom(content, numLines);
    display.show();
}

void LcdManager::clear() {
    display.clear();
}