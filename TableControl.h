#pragma once

#include <Arduino.h>
#include "GyverButton.h"
#include <Ultrasonic.h>
#include "MotorControl.h"
#include <EEPROM.h>

class TableControl {
private:
    int _maxHeight, _minHeight, compensation;
    MotorControl motor;
    Ultrasonic sensor;
    GButton upButton;
    GButton downButton;
    
    int _firstPosition, _secondPosition, _ultrasonicDelay;

public:
    TableControl(int motorIn, int motorPWM, int trigPin, int echoPin, int upButtonPin, int downButtonPin, int minHeight, int maxHeight, int inertiaСompensation);

    void update();
    
    void moveUp(); 
    
    void moveDown();
    
    void moveStop(); 
    
    int checkHeight();

    void moveToPosition(int height);
    
    void updatePosition(int* position);

    int loadPosFromEEPROM(int address);

    void savePosInEEPROM(int position, int address);
    
};