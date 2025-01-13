#include "MotorControl.h"
#include "preferences.h"

MotorControl::MotorControl(int rMotorIn, int rMotorPWM, int lMotorIn, int lMotorPWM) {
    _rMotorIn = rMotorIn;
    _rMotorPWM = rMotorPWM;
    _lMotorIn = lMotorIn;
    _lMotorPWM = lMotorPWM;
}

void MotorControl::moveUp() {
    digitalWrite(_rMotorIn, HIGH);
    analogWrite(_rMotorPWM, (-motorPower) * rMotorBalanceFactor);
    digitalWrite(_lMotorIn, HIGH);
    analogWrite(_lMotorPWM, (-motorPower) * lMotorBalanceFactor);
}

void MotorControl::moveDown() {
    digitalWrite(_rMotorIn, LOW);
    analogWrite(_rMotorPWM, motorPower * rMotorBalanceFactor);
    digitalWrite(_lMotorIn, LOW);
    analogWrite(_lMotorPWM, motorPower * lMotorBalanceFactor);
}

void MotorControl::moveStop() {
    digitalWrite(_rMotorIn, LOW);
    digitalWrite(_rMotorPWM, LOW);
    digitalWrite(_lMotorIn, LOW);
    digitalWrite(_lMotorPWM, LOW);
}
