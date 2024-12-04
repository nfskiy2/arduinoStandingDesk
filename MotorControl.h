#pragma once

#include <Arduino.h>

class MotorControl {
private:
    int _motorIn, _motorPWM;

public:
    MotorControl(int motorIn, int motorPWM);

    void moveUp();

    void moveDown();

    void moveStop();

};


