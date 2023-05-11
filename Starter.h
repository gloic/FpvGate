#ifndef Starter_H
#define Starter_H

#include "Gate.h"

class Starter : public Gate {
public:
  Starter() {instance = this;}
  void setup() override;
  void loop() override;
protected:
  void notifyPass();
private:
  static Starter* instance;

  void setupWifi();
  void setupWebController();
  void setupGPIO();
  void doRegister(String ip);
  int registerGate(String ip);
  void startListening(String ip, String id);
  void stopListening(String ip, String id);
  void enableTrackMode();
  void isMode(Mode mode);

  static void onRegisterGate(AsyncWebServerRequest* request);
  static void onGatePassed(AsyncWebServerRequest* request);
  static void onTrackMode(AsyncWebServerRequest* request);
  static void onRaceMode(AsyncWebServerRequest* request);

  static void onButtonResetPress();
  static void onButtonResetLongPress();  
};

#endif
