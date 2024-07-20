#include <Arduino.h>

#define LED_BUILTIN 8

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
  Serial.println("Hello ESP32-C3!!");
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  Serial.println("ESP32-C3 Loop!!");
}