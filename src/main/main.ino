#include <AccelStepper.h>
#include "pneumatic.h"
#include "initIO.h"

/* ---------- Phase 1 ---------- */

AccelStepper StepperLift(1, stepperLiftDIR, stepperLiftPUL);

Pneumatic PneumaticPh1A(pneumaticPh1A);
Pneumatic PneumaticPh1B(pneumaticPh1B);
Pneumatic PneumaticPh1C(pneumaticPh1C);

Pneumatic PneumaticPh1Kick(pneumaticPh1Kick);
Pneumatic PneumaticPh1Store(pneumaticPh1Store);

/* ---------- Phase 2 ---------- */

Pneumatic PneumaticPh2A(pneumaticPh2A);
Pneumatic PneumaticPh2B(pneumaticPh2B);
Pneumatic PneumaticPh2C(pneumaticPh2C);

void main(){
    // TODO: Step1
    while (digitalRead(switchS1PowerPh1));

    // TODO: Step2
    while (true)
    {
        if (!digitalRead(switchS2A)){
            // TODO: Step3
            // PneumaticPh1A OFF
            PneumaticPh1A.offPneumatic();
            break;
        }
        else if (!digitalRead(switchS3B)){
            // TODO: Step3
            // PneumaticPh1B OFF
            PneumaticPh1B.offPneumatic();
            break;
        }
        else if (!digitalRead(switchS4C)){
            // TODO: Step3
            // PneumaticPh1C OFF
            PneumaticPh1C.offPneumatic();
            break;
        }
    }

    // TODO: Step4
    while (digitalRead(switchS5));
    // PneumaticPh1... ON
    if (PneumaticPh1A.isOff()) PneumaticPh1A.onPneumatic();
    if (PneumaticPh1B.isOff()) PneumaticPh1B.onPneumatic();
    if (PneumaticPh1C.isOff()) PneumaticPh1C.onPneumatic();

    // StepperLift UP
    // PneumaticPh1Kick ON
    PneumaticPh1Kick.onPneumatic();
    // StepperLift Down
    // PneumaticPh1Kick OFF
    PneumaticPh1Kick.offPneumatic();

    // TODO: Step5
    while (digitalRead(switchS6PowerPh2));

    while (true)
    {
        if (!digitalRead(switchS7A)){
            // PneumaticPh2A OFF
            PneumaticPh2A.offPneumatic();
            break;
        }
        else if (!digitalRead(switchS8B)){
            // PneumaticPh2B OFF
            PneumaticPh2B.offPneumatic();
            break;
        }
        else if (!digitalRead(switchS9C)){
            // PneumaticPh2C OFF
            PneumaticPh2C.offPneumatic();
            break;
        }
    }

    if (PneumaticPh2A.isOff()) PneumaticPh2A.onPneumatic();
    if (PneumaticPh2B.isOff()) PneumaticPh2B.onPneumatic();
    if (PneumaticPh2C.isOff()) PneumaticPh2C.onPneumatic();

    // pneumaticPh1Store OFF
    PneumaticPh1Store.offPneumatic();

    // pneumaticPh1Store ON
    PneumaticPh1Store.onPneumatic();

    // TODO: Step6
}

void setPneumaticDefaultStage(){
    PneumaticPh1A.onPneumatic();
    PneumaticPh1B.onPneumatic();
    PneumaticPh1C.onPneumatic();

    PneumaticPh1Kick.offPneumatic();
    PneumaticPh1Store.onPneumatic();

    PneumaticPh2A.onPneumatic();
    PneumaticPh2B.onPneumatic();
    PneumaticPh2C.onPneumatic();
}

void getInputValue(){
    for (int i = 0;i < sizeof(pinIN) / sizeof(int);i++){
        Serial.print("Index ");
        Serial.print(i);
        Serial.print(":");
        Serial.print(digitalRead(pinIN[i]));
        Serial.print("\t");
    }
    Serial.println();
}

void setup(){
    Serial.begin(115200);
    for (int i = 0;i < sizeof(pinIN) / sizeof(int);i++) pinMode(pinIN[i], INPUT_PULLUP);
    for (int i = 0;i < sizeof(pinOUT) / sizeof(int);i++) pinMode(pinOUT[i], OUTPUT);
    setPneumaticDefaultStage();
}

void loop(){

}