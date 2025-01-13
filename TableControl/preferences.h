#pragma once

// Пины правого мотора
const int rMotorIn = 5;
const int rMotorPWM = 4;

// Пины левого мотора
const int lMotorIn = 16;
const int lMotorPWM = 2;

// Пины датчика расстояния
const int trigPin = 15;
const int echoPin = 13;

// Пины кнопок
const int upButtonPin = 14;
const int downButtonPin = 12;

const int minHeight = 70;
const int maxHeight = 120;

const int inertiaСompensation = 0;
const int rMotorBalanceFactor = 0.2;
const int lMotorBalanceFactor = 1;
const int motorPower = 255;

