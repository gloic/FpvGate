#include "EspBase.h"
#include "Secrets.h"
#include <HTTPClient.h>

/** PIN DEFINITONS **/
#define trigPin 33
#define echoPin 25
#define ledPin 32

EspBase espBase;

// Gate variables
String ipStarter;
String id;

bool isListening = false;

WiFiClient wifiClient;
HTTPClient http;

// Configuration
int thresholdDistance = 30;
const int minThreshold = 2 * thresholdDistance / 0.034;

// LEDS I2C (for FastLED)
#define NUM_LEDS 4
#define DATA_PIN 23
#define CLOCK_PIN 22

void setup() {
  espBase.init(SECRET_SSID, SECRET_PASS);
  espBase.setupBase();  
  espBase.setupWifi();  
  setupGPIO();
  setupWebController();  
  
  notifyStarter();  
}

void setupGPIO() {
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void setupWebController() {
  espBase.setupWebController();
  
  espBase.server.on("/test", HTTP_GET, [](AsyncWebServerRequest * request) {
    notifyStarter();
    request->send(200, "text/plain", "Test");
  });
  
  espBase.server.on("/start", HTTP_GET, [](AsyncWebServerRequest * request) {
    isListening = true;
    request->send(200, "text/plain", "OK");
  });
  
  espBase.server.on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    isListening = false;
    request->send(200, "text/plain", "OK");
  });
    
  espBase.startWebServer();
}

void notifyStarter() {
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

void loop() {
  if(isListening) {
	  checkPass();
	  delay(50);
  } 
}

void checkPass() {
  // trigger the sensor by sending a 10us pulse to the trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure the time it takes for the echo pin to go from HIGH to LOW
  long duration = pulseIn(echoPin, HIGH);
  // float distance = duration * 0.034 / 2;
  
  // check if something is within the threshold of the sensor
  if (duration < minThreshold) {
	  // Object passed
	  notifyPass();
  }
}

void notifyPass() {
  String url = "http://" + ipStarter + "/api/gate/" + id + "/pass";
  http.begin(wifiClient, url.c_str());
  int httpCode = http.GET();                                        //Make the request
  if (httpCode > 0) { //Check for the returning code
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }
  http.end();
}