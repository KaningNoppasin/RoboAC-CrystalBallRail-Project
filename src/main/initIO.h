#ifndef INITIO_H
#define INITIO_H

/* -------------------- OUTPUT -------------------- */

/* ---------- Phase 1 ---------- */

/*
* PneumaticPh1

-------
    A   \
------   ------|
    B   | Lift |
------   ------|
    C   /
-------

*/

#define pneumaticPh1A 1
#define pneumaticPh1B 1
#define pneumaticPh1C 1

// Position A5
#define pneumaticPh1Kick 1
// Position A6
#define pneumaticPh1Store 1

// Stepper
#define stepperLiftDIR 1
#define stepperLiftPUL 1

// Motor
#define motorA7 1
#define motorA8 1

/* ---------- Phase 2 ---------- */

// #define pneumaticPh2A 1
// #define pneumaticPh2B 1
// #define pneumaticPh2C 1

/* -------------------- INPUT -------------------- */

/* ---------- Phase 1 ---------- */

#define switchS1PowerPh1 1

// Pneumatic Control
#define switchS2A 1
#define switchS3B 1
#define switchS4C 1

// limit Switch => lift
#define switchS5 1

#define liftLimitUP 1
#define liftLimitDOWN 1

/* ---------- Phase 2 ---------- */

#define switchS6PowerPh2 1

// Pneumatic Control
#define switchS7A 1
#define switchS8B 1
#define switchS9C 1

int pinIN[9] = {
                switchS1PowerPh1,
                switchS2A,switchS3B,switchS4C,
                switchS5,
                switchS6PowerPh2,
                switchS7A,switchS8B,switchS9C,
                };
int pinOUT[2] = {
                motorA7,motorA8
                };

#endif