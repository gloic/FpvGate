#pragma once

#include <modules/LcdDisplay.h>
#include <ArduinoLog.h>

class LcdManager {
    public: 
        static LcdManager &getInstance();
        LcdManager() : display() {
            display.setup();
        };
        void setTitle(String title) { 
            Log.infoln("set title : %s", title);
            this->title = title;
        }
        void setContent(String* content, int numLines) {
            this->content = content;
            this->numLines = numLines;
        }
        void show();
        void clear();
    private:
        static LcdManager *instance;
        LcdDisplay display;
        String title;
        String* content;
        int numLines = 0;
};