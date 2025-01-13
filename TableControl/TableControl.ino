#include <Arduino.h>
#include "TableControl.h"
#include "preferences.h"

unsigned long tmr = 0;

// Создание объекта стола
TableControl table(rMotorIn, rMotorPWM, lMotorIn, lMotorPWM, trigPin, echoPin, upButtonPin, downButtonPin, minHeight, maxHeight, inertiaСompensation);

void setup() {
    Serial.begin(9600);

    pinMode(rMotorIn, OUTPUT);
    pinMode(rMotorPWM, OUTPUT);
    pinMode(lMotorIn, OUTPUT);
    pinMode(lMotorPWM, OUTPUT);
}

void loop() {
  if (millis() - tmr > 80) {
    table.update();

    tmr = millis();
  }         
}
