#pragma once

#include "EZ-Template/PID.hpp"
#include "controls.hpp"

// declaring global variables
inline bool isAuto = false;
inline bool runColorSort = true;
inline bool isRed = true;

// declaring intake variables
inline int intake_vltg = 0;

// declaring intake functions
void intakeSet(int vltg);
void intake_control();
void intake_t();

// declaring arm variables
inline int arm_vltg = 0;
inline int armState = 0;
enum armStates{ARM_DOWN = 1000, ARM_PRIME1 = 3400, ARM_PRIME2 = 5000, ARM_SCORE = 14000, ARM_ALLIANCE = 21000};

// declaring arm PID control loop
inline ez::PID armPid(2, 0, 10, 0, "Lady Brown PID");

// declaring arm functions
void armPos(int target);
void arm_wait();
void arm_control();
void arm_control_legacy();
void arm_t();

// declaring piston variables
inline bool clampState = false;
inline bool liftState = false;
inline bool doinkerLeftState = false;
inline bool doinkerRightState = false;

// declaring piston functions
void piston_control();
void piston_t();
void clamp_t();

// checking temperature variables and functions
inline double averageTempFahrenheit = 0;
void checkTempAndPorts();

extern bool ColorLoopActive;

extern bool wrongColorDetected;

extern bool colorLoopStarted;

extern double ambientHue;

extern double ambientProximity;

extern bool colorUntilActivated;
extern int ringsSeen;
extern int colorUntilRings;

extern bool safeScoring;
extern double prevHeading;

void initColorSort();

void doColorSort();

void colorSort_t();

void stopColorUntilFunction();

void startColorUntil(int rings);

void clampMogo(bool active);

// Driver Control Functions
void setMogoMotors();

extern bool autoClampActivated;