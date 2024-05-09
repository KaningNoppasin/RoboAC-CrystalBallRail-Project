#ifndef Pneumatic_h
#define Pneumatic_h

#include <Arduino.h>

class Pneumatic{
    public:
        Pneumatic(byte pin);
        void onPneumatic();
        void offPneumatic();
        bool isOn();
        bool isOff();
    private:
        byte _pin;
        bool _onStage;
};

#endif