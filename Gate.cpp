#include "Gate.h"
#include "SonicSensor.h"
#include "LedStatut.h"

//#include "Leds.h"
/*
  Led status :
   - ON = Detecting
   - OFF = not detecting
  
  Potentiometer : detection threshold = 10cm <-> 50cm

  // LEDS I2C (for FastLED)
  //#define NUM_LEDS 4
  //#define DATA_PIN 23
  //#define CLOCK_PIN 22
*/

const String ENDPOINT_REGISTER = "/api/gate/register";

auto sonicSensor = SonicSensor(33, 25);
auto ledStatut = LedStatut();

//Leds ledsService = Leds(1, 32);


Gate* Gate::instance = nullptr;
String ipStarter;
String id;

void Gate::setup() {
  this->setupWifi();
  this->setupWebController();
  this->setupGPIO();

  EspBase::startWebServer();
  isListening = false;

  ledStatut.setup();
}

void Gate::setupWifi() {
  EspBase::setupWifi(SECRET_SSID, SECRET_PASS);
  // Notify Starter
  this->doRegister(WiFi.gatewayIP().toString());
}

void Gate::setupWebController() {
  EspBase::setupWebController();
  Serial.println("Gate::setupWebController");
  this->server().on("/api/gate/start", HTTP_POST, &Gate::onStart);
  Serial.println("onStart");
  this->server().on("/api/gate/stop", HTTP_POST, &Gate::onStop);
  Serial.println("onStop");
  this->server().on("/api/gate/led", HTTP_POST, &Gate::onLed);
  Serial.println("onLed");
}

void Gate::setupGPIO() {
  sonicSensor.setup();
  /*
  pinMode(ledPin, OUTPUT);
  */
}

void Gate::doRegister(String ip) {
  Serial.println("Registering gate to Starter");
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/register", ip.c_str());
  http.begin(wifiClient, url);
  int httpCode = http.POST("");
  if (httpCode == HTTP_CODE_OK) {
    String responseBody = http.getString();
    id = responseBody.toInt();
    ipStarter = ip;
    Serial.print("id received = ");
    Serial.println(id);
  }
  http.end();
}

void Gate::onStart(AsyncWebServerRequest* request) {
  instance->isListening = true;
  // TODO : add arg "stop listening once passed"
  request->send(200, "text/plain", "started");
}

void Gate::onStop(AsyncWebServerRequest* request) {
  instance->isListening = false;
  request->send(200, "text/plain", "stopped");
}

void Gate::onLed(AsyncWebServerRequest* request) {
  // TODO
  Serial.println("LED");
  request->send(200, "text/plain", "led");
}

void Gate::loop() {
  if (isListening) {
    if(this->checkPass()) {
     this->notifyPass(); 
    }
  }
  ledStatut.loop();
}

boolean Gate::checkPass() {
  //Serial.println("Checking pass");
  return sonicSensor.checkPass();
}

void Gate::notifyPass() {
  Serial.println("Notify pass to Starter");
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/passed", ipStarter.c_str());
  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  String payload = "id=" + id;
  http.POST(payload);
  http.end();
}
