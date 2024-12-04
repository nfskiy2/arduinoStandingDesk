#include "MotorControl.h"

MotorControl::MotorControl(int motorIn, int motorPWM) {
    _motorIn = motorIn;
    _motorPWM = motorPWM;
}

void MotorControl::moveUp() {
    digitalWrite(_motorIn, HIGH);
    digitalWrite(_motorPWM, LOW);
}

void MotorControl::moveDown() {
    digitalWrite(_motorIn, LOW);
    digitalWrite(_motorPWM, HIGH);
}

void MotorControl::moveStop() {
    digitalWrite(_motorIn, LOW);
    digitalWrite(_motorPWM, LOW);
}