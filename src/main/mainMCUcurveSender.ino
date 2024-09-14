#include <AccelStepper.h>
#include <ArduinoJson.h>
#include "StepperController.h"
#include "pneumatic.h"
#include "initIO.h"

StepperController StepperLift(1, stepperLiftPUL, stepperLiftDIR);

Pneumatic PneumaticA(pneumaticA);
Pneumatic PneumaticB(pneumaticB);
Pneumatic PneumaticC(pneumaticC);

Pneumatic PneumaticKick(pneumaticKick);
Pneumatic PneumaticStore(pneumaticStore);

#define SERIAL Serial

int speedx = 800;
int stepperLiftPositionA = 0;
int stepperLiftPositionB = 150;
int stepperLiftPositionC = 1200;
int debounceDelay = 500;


String Receiver()
{
    const int bufferSize = 64;
    static char buffer[bufferSize];
    static int index = 0;

    while (SERIAL.available() > 0)
    {
        char incomingByte = SERIAL.read();

        if (index < bufferSize - 1)
        {
            buffer[index++] = incomingByte;
        }

        if (incomingByte == '\n')
        {
            buffer[index] = '\0';
            String data = String(buffer);
            index = 0;
            return data;
        }
    }
    return "";
}



void setHomeLift(){
    StepperLift.setSpeed(-speedx);
    while (digitalRead(liftLimitDOWN)){
        StepperLift.runSpeed();
    }
    StepperLift.setSpeed(0);
    StepperLift.setCurrentPosition(0);
}

void resetStage(){
    PneumaticStore.onPneumatic();
    delay(10000);
    PneumaticStore.offPneumatic();
    // Reset Stepper
    setHomeLift();
    delay(500);
    // Reset Motor
    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);
}

void liftGoUP(){
    StepperLift.setSpeed(speedx);
    while (digitalRead(liftLimitUP)){
        StepperLift.runSpeed();
    }
    StepperLift.setSpeed(0);
}

void main_(){
    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);

    setHomeLift();

    while (true)
    {
        if (!digitalRead(switchS2A)){
            // Debounce
            delay(debounceDelay);
            if (digitalRead(switchS2A)) continue;
            PneumaticA.onPneumatic();
            break;
        }
        else if (!digitalRead(switchS3B)){
            // Debounce
            delay(debounceDelay);
            if (digitalRead(switchS3B)) continue;
            PneumaticB.onPneumatic();
            break;
        }
        else if (!digitalRead(switchS4C)){
            // Debounce
            delay(debounceDelay);
            if (digitalRead(switchS4C)) continue;
            PneumaticC.onPneumatic();
            break;
        }
    }

    delay(5000);

    if (PneumaticA.isOn()) {
        PneumaticA.offPneumatic();
        digitalWrite(motorA7_F, LOW);
        digitalWrite(motorA7_B, LOW);
        digitalWrite(motorA8_F, HIGH);
        digitalWrite(motorA8_B, LOW);
    }
    else if (PneumaticB.isOn()) {
        PneumaticB.offPneumatic();
        digitalWrite(motorA7_F, LOW);
        digitalWrite(motorA7_B, HIGH);
        digitalWrite(motorA8_F, LOW);
        digitalWrite(motorA8_B, HIGH);
    }
    else if (PneumaticC.isOn()) {
        PneumaticC.offPneumatic();
        digitalWrite(motorA7_F, HIGH);
        digitalWrite(motorA7_B, LOW);
        digitalWrite(motorA8_F, LOW);
        digitalWrite(motorA8_B, HIGH);
    }

    // StepperLift.setSpeed(speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionC) StepperLift.runSpeed();
    liftGoUP();
    delay(500);

    PneumaticKick.onPneumatic();
    delay(1000);
    PneumaticKick.offPneumatic();

    setHomeLift();
    delay(4000);

    SERIAL.write("done\n");
    delay(500);

    while (true){
        String data = Receiver();
        if (data == "start\n") break;
    }

    PneumaticStore.onPneumatic();
    delay(5000);
    PneumaticStore.offPneumatic();
}

void setup(){
    Serial.begin(115200);
    SERIAL.begin(115200);

    for (int i = 0; i < sizeof(pinIN) / sizeof(pinIN[0]); i++) pinMode(pinIN[i], INPUT_PULLUP);
    for (int i = 0; i < sizeof(pinOUT) / sizeof(pinOUT[0]); i++) pinMode(pinOUT[i], OUTPUT);
    StepperLift.setLimitPositivePosition(500);
    StepperLift.setLimitNegativePosition(1350);

    resetStage();
    // digitalWrite(motorA7_F, LOW);
    // digitalWrite(motorA7_B, HIGH);
    // digitalWrite(motorA8_F, LOW);
    // digitalWrite(motorA8_B, HIGH);

    // setHomeLift();
    // delay(500);
}

void loop(){
    main_();
}
