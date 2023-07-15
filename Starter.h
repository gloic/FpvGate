#ifndef Starter_H
#define Starter_H

#include "Gate.h"
#include "GateClient.h"
#include "Mode.h"

class Starter : public Gate {
public:
  Starter() {instance = this;}
  void setup() override;
  void loop() override;
protected:
  void notifyPass();
private:
  static Starter* instance;
  long lastLapTime;
  long bestLapTime;

  void setupWifi();
  void setupWebController();
  void setupGPIO();
  void doRegister(String ip);
  int registerGate(String ip);
  void startListening(const GateClient* gate);
  void stopListening(const GateClient* gate);
  void startListeningAll();
  
  void enableTrackMode();
  void enableRaceMode();
  bool isMode(Mode mode);

  void startLap();
  void stopLap();
  void resetLap();

  static void onRegisterGate(AsyncWebServerRequest* request);
  static void onGatePassed(AsyncWebServerRequest* request);
  static void onTrackMode(AsyncWebServerRequest* request);
  static void onRaceMode(AsyncWebServerRequest* request);

  static void onButtonResetPress();
};

#endif
