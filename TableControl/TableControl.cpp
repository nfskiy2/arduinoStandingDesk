#include "TableControl.h"

TableControl::TableControl(int motorIn, int motorPWM, int trigPin, int echoPin, int upButtonPin, int downButtonPin, int minHeight, int maxHeight, int inertiaСompensation) : motor(motorIn, motorPWM), sensor(trigPin, echoPin), upButton(upButtonPin), downButton(downButtonPin) { 
  compensation = inertiaСompensation; //компенcируем инерцию стола

  _ultrasonicDelay = 300;//с какой частотой будет опрашиваться датчик расстояния 
  upButton.setDebounce(80);// установка времени антидребезга
  downButton.setDebounce(80);

  _minHeight = minHeight;
  _maxHeight = maxHeight;

  _firstPosition = loadPosFromEEPROM(0); 
  _secondPosition = loadPosFromEEPROM(4); 
}

void TableControl::update() {
    upButton.tick();
    downButton.tick();
    

    if (upButton.isHold()) {
        Serial.println("upButton is Hold");
        moveUp();
    } //при зажатии кнопки непрерывно двигаемся вверх

    if (downButton.isHold()) {
        Serial.println("downButton is Hold");
        moveDown();
    } //при зажатии кнопки непрерывно двигаемся вниз

    if (upButton.isRelease() || downButton.isRelease()) {
        Serial.println("release");
        moveStop();
    } //останавливаем двигатели, когда отпускаем кнопку

    if (upButton.isSingle()) {
        Serial.println("upButton is clicked");
        moveToPosition(_firstPosition);
    } //перемещаемся в первую позицию

    if (downButton.isSingle()) {
        Serial.println("downButton is clicked");
        moveToPosition(_secondPosition);
    } //перемещаемся во вторую позицию

    if (upButton.isDouble()) {
        Serial.println("upButton is double clicked");
        updatePosition(&_firstPosition);
    } //записываем первую позицию в память

    if (downButton.isDouble()) {
        Serial.println("upButton is double clicked");
        updatePosition(&_secondPosition);
    } //записываем вторую позицию в память
}

void TableControl::moveUp() {
    if (checkHeight() < _maxHeight) {
        Serial.println("up");
        motor.moveUp();
    } 
    else {
        Serial.println("too high");
        motor.moveStop();
    }
}

void TableControl::moveDown() {
    if (checkHeight() > _minHeight) {
        Serial.println("down");
        motor.moveDown();
    } else {
        Serial.println("too low");
        motor.moveStop();
    }
}

void TableControl::moveStop() {
    motor.moveStop();
}

int TableControl::checkHeight() {
    return sensor.read();
}

void TableControl::moveToPosition(int targetHeight) {
  if (targetHeight > _maxHeight || targetHeight < _minHeight) return;

  int currentHeight = checkHeight();

  Serial.print("target height: ");
  Serial.println(targetHeight);
  Serial.print("current height: ");
  Serial.println(currentHeight);

  if (currentHeight > targetHeight) {
      unsigned long lastTime = millis();

      while (currentHeight > targetHeight + compensation) {
        if (millis() - lastTime > _ultrasonicDelay) {
          Serial.println("down");

          motor.moveDown();

          lastTime = millis();
          currentHeight = checkHeight();
        }                 
      }
      
      Serial.print("stop on: ");
      Serial.println(currentHeight);
      motor.moveStop();
      return;
  } 
  

  if (currentHeight < targetHeight) {
      unsigned long lastTime = millis();

      while (currentHeight < targetHeight - compensation) {
        if (millis() - lastTime > _ultrasonicDelay) {
          Serial.println("up");

          motor.moveUp();

          lastTime = millis();
          currentHeight = checkHeight();
        }                 
      }
      
      Serial.print("stop on: ");
      Serial.println(currentHeight);

      motor.moveStop();
      return;
  } 
  
}

void TableControl::updatePosition(int* position) {
  int currentHeight = checkHeight();

  Serial.print("current height: ");
  Serial.println(currentHeight);
  
  if (currentHeight > _maxHeight || currentHeight < _minHeight) return;

  *position = currentHeight;

  if (position == &_firstPosition) {
    savePosInEEPROM(*position, 0);  // Сохраняем первую позицию по адресу 0
  } else if (position == &_secondPosition) {
    savePosInEEPROM(*position, 4);  // Сохраняем вторую позицию по адресу 4
  }

  Serial.println("position saved");
}

// Функция для записи в EEPROM
void TableControl::savePosInEEPROM(int position, int address) {
  EEPROM.put(address, position);  // Сохраняем позицию в указанный адрес
}

int TableControl::loadPosFromEEPROM(int address) {
  int position;
  EEPROM.get(address, position);  // Считываем позицию из указанного адреса
  return position;
}
