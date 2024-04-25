#include "LcdDisplay.h"
#include "Wire.h"
#include <ArduinoLog.h>

void LcdDisplay::setup() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Log.errorln("SSD1306 allocation failed");
    }
    display.setTextColor(WHITE);
    display.setTextSize(1);
    clear();
}

void LcdDisplay::showTop(String title) {
    display.setCursor(0, 2);
    display.print(title);
    display.drawLine(0, 12, 128, 12, 1);
}

void LcdDisplay::showBottom(String line1, String line2, String line3) {
    display.setCursor(0, 15);
    display.println(line1);
    display.println(line2);
    display.println(line3);
}

// void LcdDisplay::display() {
//     display.display();
// }

void LcdDisplay::clear() {
    display.clearDisplay();
}