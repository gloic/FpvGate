#include "Gate.h"

/** PIN DEFINITONS **/
#define trigPin 33
#define echoPin 25
#define ledPin 32


const String ENDPOINT_REGISTER = "/api/gate/register";

WiFiClient wifiClient;
HTTPClient http;
String ipStarter;
String id;
bool isListening = false;

int thresholdDistance = 30;
int minThreshold = 2 * thresholdDistance / 0.034;

void Gate::setup() {
  this->setupWifi();
  this->setupWebController();
  this->setupGPIO();
  
  // Notify Starter
  this.register();
}

void Gate::setupWifi() {
	EspBase::setupWifi(SECRET_SSID, SECRET_PASS); 
	ipStarter = WiFi.gatewayIP().toString();
}

void Gate::setupGPIO() {
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);
  
  pinMode(ledPin, OUTPUT);
}

void Gate::register() {
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/register", ipStarter.c_str());
  http.begin(wifiClient, url.c_str());
  int httpCode = http.POST("");
  if (httpCode == HTTP_CODE_OK) {
    String responseBody = http.getString();    
    id = responseBody.toInt();
    Serial.print("id received = ");
    Serial.println(id);
  }
  http.end();
}

void Gate::notifyPass() {
  char url[100];
  snprintf(url, sizeof(url), "http://%s/api/gate/%d/passed", ipStarter.c_str(), id);
  http.begin(wifiClient, url.c_str());
  http.POST("");
  http.end();
}

void Gate::setupWebController() {
  EspBase::setupWebController();
  this->server().on("/api/gate/start", HTTP_POST, onStart);
  this->server().on("/api/gate/stop", HTTP_POST, onStop);
  this->server().on("/api/gate/led", HTTP_POST, onLed);
  EspBase::startWebServer();
}

void Gate::onStart(AsyncWebServerRequest * request) {
	isListening = true;
    request->send(200, "text/plain", "started");
}

void Gate::onStop(AsyncWebServerRequest * request) {
	isListening = false;
    request->send(200, "text/plain", "stopped");
}

void Gate::onLed(AsyncWebServerRequest * request) {
	// TODO
	Serial.println("LED");
    request->send(200, "text/plain", "led");
}

void Gate::checkPass() {
  if(!isListening) return;
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
  if (duration < minThreshold) {
	  // Something passed
	  notifyPass();
  }
}

AsyncWebServer Gate::server() {
  return EspBase::server();
}