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

int speedx = 800;
int stepperLiftPositionA = 0;
int stepperLiftPositionB = -150;
int stepperLiftPositionC = -1190;

// 0 => 210 => 1150
// 0 => -170 => -1190

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
void Sender_serializeJson(String status)
{
    StaticJsonDocument<200> payload;
    payload["status"] = status;

    serializeJson(payload, SERIAL);
}

void Receiver_deserializeJson(){
    if (SERIAL.available())
    {
        StaticJsonDocument<300> response;

        DeserializationError err = deserializeJson(response, SERIAL);

        if (err == DeserializationError::Ok)
        {
            res = response["status"].as<String>();
        }
        else
        {
            // Print error to the "debug" serial port
            // Serial.print("deserializeJson() returned ");
            // Serial.println(err.c_str());

            // Flush all bytes in the "link" serial port buffer
            while (SERIAL.available() > 0)
                SERIAL.read();
        }
    }
}

void setHomeLift(){
    StepperLift.setSpeed(800);
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

    // A => B
    // StepperLift.setSpeed(-speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionB) StepperLift.runSpeed();

   // * >> TX RX Serial with Json
    // Receiver_deserializeJson();
    // while (res != "done")
    // {
    //     Receiver_deserializeJson();
    //     PneumaticA.onPneumatic();
    //     delay(2000);
    //     Receiver_deserializeJson();
    //     PneumaticA.offPneumatic();
    //     delay(2000);
    // }
    // res = "";

    // while (true)
    // {
    //     Serial.println("w");
    //     if (SERIAL.available() > 0){
    //         if (SERIAL.readStringUntil('\n') == "done"){
    //             break;
    //         }
    //     }
    // }

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
    // delay(4000);
    // while (digitalRead(switchS5)){
        // Serial.println("digitalRead(switchS5)");
    // }
   // * >> TX RX Serial with Json
    // Sender_serializeJson("start");
    // SERIAL.println("start");

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
    // Receiver_deserializeJson();
    // while (res != "done")
    // {
    //     Receiver_deserializeJson();
    // }
    // res = "";

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
    // delay(4000);
    // while (digitalRead(switchS5)){
        // Serial.println("digitalRead(switchS5)");
    // }
   // * >> TX RX Serial with Json
    // Sender_serializeJson("start");

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
    // Serial.println("SetUP <<");
    // Serial.println("Hello from Receiver");
    for (int i = 0;i < sizeof(pinIN) / sizeof(pinIN[0]);i++) pinMode(pinIN[i], INPUT);
    for (int i = 0;i < sizeof(pinOUT) / sizeof(pinOUT[0]);i++) pinMode(pinOUT[i], OUTPUT);
    StepperLift.setLimitPositivePosition(500);StepperLift.setLimitNegativePosition(1350);
    // delay(2000);
    // StepperLift.setAcceleration(500);
    // StepperLift.setMaxSpeed(10000);
    setHomeLift();
    delay(500);

    // A => B
    // StepperLift.setSpeedAndLimitPositionOutOfRange(-speedx);
    // while (StepperLift.currentPosition() != stepperLiftPositionB) StepperLift.runSpeed();


    digitalWrite(motorA7_F, LOW);
    digitalWrite(motorA7_B, HIGH);
    digitalWrite(motorA8_F, LOW);
    digitalWrite(motorA8_B, HIGH);

    while (true)
    {
        if (SERIAL.available() > 0){
            String data = SERIAL.readStringUntil('\n');
            if (data == "done"){
                break;
            }
        }
    }

    // Sender_serializeJson("waiting");
    // for (int round = 0; round < 10; round++)
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