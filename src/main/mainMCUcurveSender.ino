// * Receiver
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

// int speedx = 800;
// int stepperLiftPositionA = 0;
// int stepperLiftPositionB = -150;
// int stepperLiftPositionC = -1160;


// TODO Check steeper direction
int speedx = -800;
int stepperLiftPositionA = 0;
int stepperLiftPositionB = 150;
int stepperLiftPositionC = 1160;

String res = "";
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
    StepperLift.setSpeed(speedx);
    while (digitalRead(liftLimitDOWN)){
        StepperLift.runSpeed();
    }
    StepperLift.setSpeed(0);
    StepperLift.setCurrentPosition(0);
}

void main_(){
    // TODO: Step1
    // while (digitalRead(switchS1Power));
    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);

    setHomeLift();

    // A => B
    // StepperLift.setSpeed(-speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionB) StepperLift.runSpeed();

    // * >> TX RX Serial with Json
    // Sender_serializeJson("processing");

    // TODO: Step2
    while (true)
    {
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
    // while (digitalRead(liftLimitDOWN));

    delay(5000);

    // !
    // Pneumatic... ON
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
    setHomeLift();
    // StepperLift.setSpeed(speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionA) StepperLift.runSpeed();

    // TODO: Step5

    // while (digitalRead(LimitStore));
    delay(4000);

    // Sent TX RX
    /*
        payload = {
            status : processing - done
        }
    */
   // * >> TX RX Serial with Json
    // Sender_serializeJson("done");
    // SERIAL.println("done");
    SERIAL.write("done\n");
    delay(500);

    // while (true)
    // {
    //     if (SERIAL.available() > 0){
    //         if (SERIAL.readStringUntil('\n') == "start"){
    //             break;
    //         }
    //     }
    // }
    // String data = Receiver();
    // while (data != "start\n"){
    //     data = Receiver();
    // }
    while (true){
        String data = Receiver();
        if (data == "start\n") break;
    }

    // while (res != "start")
    // {
    //     Receiver_deserializeJson();
    //     delay(500);
    // }
    // res = "";

    // pneumaticStore ON
    PneumaticStore.onPneumatic();
    delay(5000);
    // pneumaticStore OFF
    PneumaticStore.offPneumatic();


    // TODO: Step6
}


void main_input(int input){
    // TODO: Step1
    // while (digitalRead(switchS1Power));
    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);

    // A => B
    // StepperLift.setSpeed(-speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionB) StepperLift.runSpeed();

    // * >> TX RX Serial with Json
    // Sender_serializeJson("processing");

    // TODO: Step2
    while (true)
    {
        if (input == 1){
            // TODO: Step3
            // PneumaticA OFF
            PneumaticA.onPneumatic();
            break;
        }
        else if (input == 2){
            // TODO: Step3
            // PneumaticB OFF
            PneumaticB.onPneumatic();
            break;
        }
        else if (input == 3){
            // TODO: Step3
            // PneumaticC OFF
            PneumaticC.onPneumatic();
            break;
        }
    }

    // TODO: Step4
    // while (digitalRead(switchS5));
    // while (digitalRead(liftLimitDOWN));

    delay(5000);

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
    setHomeLift();
    // StepperLift.setSpeed(speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionA) StepperLift.runSpeed();

    // TODO: Step5

    // while (digitalRead(LimitStore));
    delay(4000);

    // Sent TX RX
    /*
        payload = {
            status : processing - done
        }
    */
   // * >> TX RX Serial with Json
    // Sender_serializeJson("done");

    // while (res != "start")
    // {
    //     Receiver_deserializeJson();
    // }
    // res = "";

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
        Serial.println(position);
        int speedx = position > StepperLift.currentPosition() ? 500 : -500;
        StepperLift.setSpeed(speedx);
        while (StepperLift.currentPosition() != position) StepperLift.runSpeed();
    }
}

void setup(){
    Serial.begin(115200);
    SERIAL.begin(115200);
    // Serial.println("SetUP <<");
    // Serial.println("Hello from Sender");
    for (int i = 0;i < sizeof(pinIN) / sizeof(pinIN[0]);i++) pinMode(pinIN[i], INPUT);
    for (int i = 0;i < sizeof(pinOUT) / sizeof(pinOUT[0]);i++) pinMode(pinOUT[i], OUTPUT);
    StepperLift.setLimitPositivePosition(500);StepperLift.setLimitNegativePosition(1350);

    setHomeLift();
    delay(500);

    // A => B
    // StepperLift.setSpeedAndLimitPositionOutOfRange(-speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionB) StepperLift.runSpeed();


    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);

    // for (int round = 0; round < 1; round++)
    // {
    //     for (int i = 1; i < 4; i++)
    //     {
    //         main_input(i);
    //     }
    // }
}

void loop(){
    // getInputValue();
    main_();
    // serialStep();
}