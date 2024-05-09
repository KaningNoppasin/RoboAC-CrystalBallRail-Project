// PlatformIO Project Structure:
// Your project structure should look something like this:

// /Pneumatic
// ├── include
// │   └── Pneumatic.h
// ├── lib
// ├── src
// │   ├── Pneumatic.cpp
// │   └── main.cpp
// ├── platformio.ini
// └── README.md

#include <Arduino.h>

#include "pneumatic.h"

Pneumatic::Pneumatic(byte pin)
{
    this->_pin = pin;
    pinMode(this->_pin, OUTPUT);
    // set default stage
    this->offPneumatic();
}

void Pneumatic::onPneumatic()
{
    digitalWrite(this->_pin, HIGH);
    this->_onStage = true;
}

void Pneumatic::offPneumatic()
{
    digitalWrite(this->_pin, LOW);
    this->_onStage = false;
}

bool Pneumatic::isOff(){
    return !this->_onStage;
}

bool Pneumatic::isOn(){
    return this->_onStage;
}
