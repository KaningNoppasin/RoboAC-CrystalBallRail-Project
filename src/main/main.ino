#include <AccelStepper.h>
#include "StepperController.h"
#include "pneumatic.h"
#include "initIO.h"

// StepperController StepperLift(1, stepperLiftDIR, stepperLiftPUL);
StepperController StepperLift(1, stepperLiftPUL, stepperLiftDIR);

Pneumatic PneumaticA(pneumaticA);
Pneumatic PneumaticB(pneumaticB);
Pneumatic PneumaticC(pneumaticC);

Pneumatic PneumaticKick(pneumaticKick);
Pneumatic PneumaticStore(pneumaticStore);

int speedx = 500;
int stepperLiftPositionA = 0;
int stepperLiftPositionB = -290;
int stepperLiftPositionC = -1317;

/*
|--- Lift ---|
|            | Position (C) => -1317
|            |
|            |
|            |
|            | Position (B) => -290
|            |
|            |
|            |
|            |
|--  Limit --| Position (A) => 0

*/


void main_(){
    // TODO: Step1
    // while (digitalRead(switchS1Power));
    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);

    // A => B
    StepperLift.setSpeed(-speedx);
    while (StepperLift.currentPosition() != stepperLiftPositionB) StepperLift.runSpeed();

    // TODO: Step2
    while (true)
    {
        Serial.println("First While");
        if (!digitalRead(switchS2A)){
            // TODO: Step3
            // PneumaticA OFF
            PneumaticA.onPneumatic();
            break;
        }
        else if (!digitalRead(switchS3B)){
            // TODO: Step3
            // PneumaticB OFF
            PneumaticB.onPneumatic();
            break;
        }
        else if (!digitalRead(switchS4C)){
            // TODO: Step3
            // PneumaticC OFF
            PneumaticC.onPneumatic();
            break;
        }
    }

    // TODO: Step4
    // while (digitalRead(switchS5));
    while (digitalRead(switchS5)){
        Serial.println("digitalRead(switchS5)");
    }
    // !
    // Pneumatic... ON
    if (PneumaticA.isOn()) {
        PneumaticA.offPneumatic();
        digitalWrite(motorA7_F, LOW);
        digitalWrite(motorA7_B, LOW);
        digitalWrite(motorA8_F, HIGH);
        digitalWrite(motorA8_B, LOW);
    }
    if (PneumaticB.isOn()) {
        PneumaticB.offPneumatic();
        digitalWrite(motorA7_F, LOW);
        digitalWrite(motorA7_B, HIGH);
        digitalWrite(motorA8_F, LOW);
        digitalWrite(motorA8_B, HIGH);
    }
    if (PneumaticC.isOn()) {
        PneumaticC.offPneumatic();
        digitalWrite(motorA7_F, HIGH);
        digitalWrite(motorA7_B, LOW);
        digitalWrite(motorA8_F, LOW);
        digitalWrite(motorA8_B, HIGH);
    }

    // StepperLift UP
    // B => C
    StepperLift.setSpeed(-speedx);
    while (StepperLift.currentPosition() != stepperLiftPositionC) StepperLift.runSpeed();
    delay(500);

    // PneumaticKick ON
    PneumaticKick.onPneumatic();
    delay(1000);
    PneumaticKick.offPneumatic();

    // StepperLift Down
    // PneumaticKick OFF

    // C => A
    StepperLift.setSpeed(speedx);
    while (StepperLift.currentPosition() != stepperLiftPositionA) StepperLift.runSpeed();

    // TODO: Step5

    while (digitalRead(LimitStore));

    // Sent TX RX
    /*
        payload = {
            status : processing - done
        }
    */

    // pneumaticStore ON
    PneumaticStore.onPneumatic();
    delay(5000);
    // pneumaticStore OFF
    PneumaticStore.offPneumatic();


    // TODO: Step6
}

void getInputValue(){
    for (int i = 0;i < sizeof(pinIN) / sizeof(pinIN[0]);i++){
        Serial.print("Index ");
        Serial.print(i + 1);
        Serial.print(":");
        Serial.print(digitalRead(pinIN[i]));
        Serial.print("\t");
    }
    Serial.println();
}

void serialStep(){
    if (Serial.available() > 0){
        int position = Serial.readStringUntil('\n').toInt();
        // StepperLift.moveTo(-position);
        // while (StepperLift.run());
        // -1317
        int speedx = position > StepperLift.currentPosition() ? 500 : -500;
        StepperLift.setSpeed(speedx);
        while (StepperLift.currentPosition() != position) StepperLift.runSpeed();
    }
}

void setup(){
    Serial.begin(115200);
    Serial.println("SetUP <<");
    for (int i = 0;i < sizeof(pinIN) / sizeof(pinIN[0]);i++) pinMode(pinIN[i], INPUT);
    for (int i = 0;i < sizeof(pinOUT) / sizeof(pinOUT[0]);i++) pinMode(pinOUT[i], OUTPUT);
    StepperLift.setLimitPositivePosition(0);StepperLift.setLimitNegativePosition(1350);
    delay(2000);

    // A => B
    StepperLift.setSpeedAndLimitPositionOutOfRange(-speedx);
    while (StepperLift.currentPosition() != stepperLiftPositionB) StepperLift.runSpeed();

    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);
}

void loop(){
    main_();
}