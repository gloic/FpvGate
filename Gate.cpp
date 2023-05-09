#include "Gate.h"

/** PIN DEFINITONS **/
#define trigPin 33
#define echoPin 25
#define ledPin 32

WiFiClient wifiClient;
HTTPClient http;
String ipStarter;
String id;
bool isListening = false;

int thresholdDistance = 30;

void Gate::setup() {
  EspBase::init(SECRET_SSID, SECRET_PASS);
  EspBase::setupBase();  
  EspBase::setupWifi(); 
  this->setupWebController();
  this->setupGPIO();
}

void Gate::setupGPIO() {
  EspBase::setupGPIO();
  
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void Gate::notifyStarter() {
  ipStarter = WiFi.gatewayIP().toString();
  String url = "http://" + ipStarter + "/api/gate";
  Serial.print("URL to notify : ");
  Serial.println(url);
  http.begin(wifiClient, url.c_str());
  int httpCode = http.POST("");
  if (httpCode == HTTP_CODE_OK) {
    String responseBody = http.getString();    
    id = responseBody.toInt();
    Serial.print("id received=");
    Serial.println(id);
  }
  http.end();
  Serial.println("End of notify");
}

void Gate::notifyPass() {
  String url = "http://" + ipStarter + "/api/gate/" + id + "/pass";
  http.begin(wifiClient, url.c_str());
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }
  http.end();
}

void Gate::setupWebController() {
  EspBase::setupWebController();

  this->server().on("/start", HTTP_GET, [](AsyncWebServerRequest * request) {
    //isListening = true;
    request->send(200, "text/plain", "OK");
  });
  
  this->server().on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    //isListening = false;
    request->send(200, "text/plain", "OK");
  });
    
  EspBase::startWebServer();
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
  int minThreshold = 2 * thresholdDistance / 0.034;
  if (duration < minThreshold) {
	  // Object passed
	  notifyPass();
  }
}

AsyncWebServer Gate::server() {
  return EspBase::server();
}