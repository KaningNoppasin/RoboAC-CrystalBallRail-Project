#include <AccelStepper.h>
#include "pneumatic.h"
#include "initIO.h"

AccelStepper StepperLift(1, stepperLiftDIR, stepperLiftPUL);

Pneumatic PneumaticA(pneumaticA);
Pneumatic PneumaticB(pneumaticB);
Pneumatic PneumaticC(pneumaticC);

Pneumatic PneumaticKick(pneumaticKick);
Pneumatic PneumaticStore(pneumaticStore);

int speedx = 500;

void main_(){
    // TODO: Step1
    // while (digitalRead(switchS1Power));
    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);
    StepperLift.setSpeed(-speedx);
    while (StepperLift.currentPosition() != -290) StepperLift.runSpeed();

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
    // StepperLift.moveTo(-1330);
    // while (StepperLift.run());

    StepperLift.setSpeed(-speedx);
    while (StepperLift.currentPosition() != -1317) StepperLift.runSpeed();
    delay(500);

    // PneumaticKick ON
    PneumaticKick.onPneumatic();
    delay(1000);
    PneumaticKick.offPneumatic();

    // StepperLift Down
    // PneumaticKick OFF
    // StepperLift.moveTo(-20);
    // while (StepperLift.run());

    StepperLift.setSpeed(speedx);
    while (StepperLift.currentPosition() != 0) StepperLift.runSpeed();

    // TODO: Step5

    while (digitalRead(LimitStore));

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
    StepperLift.setMaxSpeed(10000);
    StepperLift.setAcceleration(500);

    // Step-lift 0 >> 330 >> 1330
    delay(2000);
    // StepperLift.moveTo(-330);
    // while (StepperLift.run());
    StepperLift.setSpeed(-speedx);
    while (StepperLift.currentPosition() != -290) StepperLift.runSpeed();


    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);
}

void loop(){
    // getInputValue();
    // serialStep();
    main_();
}