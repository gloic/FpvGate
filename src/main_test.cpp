#include <Arduino.h>
#include <ArduinoLog.h>

// #include <modules/LcdDisplay.h>
#include <server/managers/LcdManager.h>



// LcdDisplay display = LcdDisplay();


void setupTest() {
    Serial.begin(115200);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    LcdManager lcd = LcdManager::getInstance();    
    lcd.setTitle("youpi");
    String lines[] = {"Ligne 1", "Ligne 2", "Ligne 3"};
    lcd.setContent(lines, 3);
    lcd.show();

    // display.setup();
    // display.showTop("coucou");
    // String lines[] = {"Ligne 1", "Ligne 2", "Ligne 3"};
    // display.showBottom(lines, 3);
    // display.show();

    Log.infoln("Device ready!");
}

void loopTest() {
}