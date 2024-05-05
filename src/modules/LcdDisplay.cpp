#include "LcdDisplay.h"
#include "Wire.h"
#include <ArduinoLog.h>

void LcdDisplay::setup() {
    Log.infoln("LcdDisplay::setup");
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Log.errorln("SSD1306 allocation failed");
    }
    display.setTextColor(WHITE);
    display.setTextSize(1);
    clear();

}

void LcdDisplay::showTop(String title) {
    Log.infoln("showTop : %s", title);
    display.setCursor(0, 2);
    display.print(title);
    display.drawLine(0, 12, 128, 12, 1);
}

void LcdDisplay::showBottom(String* lines, int numLines) {
    if (numLines == 0) {
        return;
    }
    
    Log.infoln("showBottom");
    display.setCursor(0, 15);
    Log.infoln("numLine: %d", numLines);
    for (int i = 0; i < numLines; ++i) {
        Log.infoln("line to show : %s", lines[i]);
        display.println(lines[i]);
    }
}

void LcdDisplay::show() {
    display.display();
}

void LcdDisplay::clear() {
    display.clearDisplay();
}