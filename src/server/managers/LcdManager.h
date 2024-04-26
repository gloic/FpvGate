#pragma once

#include <modules/LcdDisplay.h>

class LcdManager {
    public: 
        static LcdManager &getInstance();
        LcdManager() : display() {
            display.setup();
        };
        void setup();
        void setTitle(String title) { this->title = title; }
        void setContent(String* content) { this->content = content;}
    private:
        static LcdManager *instance;
        LcdDisplay display;
        String title;
        String* content;
};