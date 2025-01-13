#pragma once

#include <Arduino.h>

class MotorControl {
private:
    int _rMotorIn, _rMotorPWM, _lMotorIn, _lMotorPWM;

public:
    MotorControl(int rMotorIn, int rMotorPWM, int lMotorIn, int lMotorPWM);

    void moveUp();

    void moveDown();

    void moveStop();

};


