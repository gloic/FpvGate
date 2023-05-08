#include "esp_base.h"
#include "Secrets.h"

#define trigPin 33
#define echoPin 25
#define ledPin 32

EspBase espBase;

void setup() {
  espBase.Init(SECRET_SSID, SECRET_PASS);
  espBase.SetupBase();
  setupWebController();
  espBase.StartWebServer();

  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void setupWebController() {
  espBase.server.on("/test", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("Test");    
    request->send(200, "text/plain", "Test");
  });
}

void loop() {
  // trigger the sensor by sending a 10us pulse to the trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure the time it takes for the echo pin to go from HIGH to LOW
  long duration = pulseIn(echoPin, HIGH);

  // calculate the distance based on the speed of sound and the duration of the echo
  float distance = duration * 0.034 / 2;

/*
  // print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
*/
  // check if something is within 50 cm of the sensor
  if (distance < 50) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // delay for a short amount of time
  delay(50);
}