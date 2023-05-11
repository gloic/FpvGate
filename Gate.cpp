#include "Gate.h"

/** PIN DEFINITONS **/
#define trigPin 33
#define echoPin 25
#define ledPin 32

/*
  Led status :
   - ON = Detecting
   - OFF = not detecting
  
  Potentiometer : detection threshold = 10cm <-> 50cm
*/


const String ENDPOINT_REGISTER = "/api/gate/register";

bool isListening;
String ipStarter;
String id;

int thresholdDistance = 30;
int minThreshold = 2 * thresholdDistance / 0.034;

void Gate::setup() {
  this->setupWifi();
  this->setupWebController();
  this->setupGPIO();

  EspBase::startWebServer();
  isListening = false;
}

void Gate::setupWifi() {
  EspBase::setupWifi(SECRET_SSID, SECRET_PASS);
  // Notify Starter
  this->doRegister(WiFi.gatewayIP().toString());
}

void Gate::setupWebController() {
  EspBase::setupWebController();
  Serial.println("Gate::setupWebController");
  this->webServer.on("/api/gate/start", HTTP_POST, &Gate::onStart);
  this->webServer.on("/api/gate/stop", HTTP_POST, &Gate::onStop);
  this->webServer.on("/api/gate/led", HTTP_POST, &Gate::onLed);
}

void Gate::setupGPIO() {
  /*
  Serial.println("setup GPIO");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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
  isListening = true;
  request->send(200, "text/plain", "started");
}

void Gate::onStop(AsyncWebServerRequest* request) {
  isListening = false;
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
}

boolean Gate::checkPass() {
  Serial.println("Checking pass");

  // trigger the sensor by sending a 10us pulse to the trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure the time it takes for the echo pin to go from HIGH to LOW
  long duration = pulseIn(echoPin, HIGH);
  // check if something is within the threshold of the sensor
  // float distance = duration * 0.034 / 2;
  return duration < minThreshold;
}

void Gate::notifyPass() {
  Serial.println("Notify pass to Starter");
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/passed", ipStarter.c_str(), id);
  http.begin(wifiClient, url);
  http.POST("");
  http.end();
}
