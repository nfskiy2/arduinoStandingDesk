#include <Arduino.h>
#include "TableControl.h"

// Параметры стола
const int motorIn = 5;
const int motorPWM = 4;
const int trigPin = 15;
const int echoPin = 13;
const int upButtonPin = 0;
const int downButtonPin = 2;

const int minHeight = 10;
const int maxHeight = 60;
const int inertiaСompensation = 2;

unsigned long tmr = 0;

// Создание объекта стола
TableControl table(motorIn, motorPWM, trigPin, echoPin, upButtonPin, downButtonPin, minHeight, maxHeight, inertiaСompensation);

void setup() {
    Serial.begin(9600);

    pinMode(motorIn, OUTPUT);
    pinMode(motorPWM, OUTPUT);
}

void loop() {
  if (millis() - tmr > 80) {
    table.update();

    tmr = millis();
  }         
}