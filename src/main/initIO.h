#ifndef INITIO_H
#define INITIO_H

/* -------------------- OUTPUT -------------------- */

/*

MA7-----
    A   \
------   ------|
    B   | Lift |
------   ------|
    C   /
MA8-----

*/

#define pneumaticA 13
#define pneumaticB 12
#define pneumaticC 11

// Position A5
#define pneumaticKick 10
// Position A6
#define pneumaticStore 9

// Stepper
#define stepperLiftDIR 2
#define stepperLiftPUL 3

// Motor
#define motorA7_F 8
#define motorA7_B 7

#define motorA8_F 6
#define motorA8_B 5


/* -------------------- INPUT -------------------- */

#define switchS1Power 4

// Pneumatic Control
#define switchS2A A5
#define switchS3B A4
#define switchS4C A3

// limit Switch => lift
#define switchS5 A2

#define LimitStore A1

// * Use this One Only | This Sensor will be set Zero Stepper
#define liftLimitDOWN A0


int pinIN[7] = {
                switchS1Power,
                switchS2A,switchS3B,switchS4C,
                switchS5,
                liftLimitDOWN,
                LimitStore,
                };
int pinOUT[4] = {
                motorA7_F,motorA7_B,
                motorA8_F,motorA8_B,
                };

#endif