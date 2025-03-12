#pragma once

#include "EZ-Template/PID.hpp"
#include "controls.hpp"
#include "pros/rtos.hpp"

// declaring global variables
inline bool isAuto = false;
inline bool runColorSort = true;
inline bool isRed;  //

// declaring intake variables
inline int intake_vltg = 0;
inline bool isStuck = false;

// declaring intake functions
void intakeSet(int vltg);
void unstuck();
void intake_control();
void intake_t();

// declaring arm variables
inline int arm_vltg = 0;
inline int armState = 0;
enum armStates{ARM_DOWN = 1000, ARM_PRIME1 = 3250, ARM_PRIME2 = 5000, ARM_SCORE = 14000, ARM_ALLIANCE = 21000};

// declaring arm PID control loop
inline ez::PID armPid(2, 0, 10, 0, "Lady Brown PID");

// declaring arm functions
void armPos(int target);
void arm_wait();
void arm_control();
void arm_t();

// declaring piston variables
inline const double AUTOCLAMP_DISTANCE = 235;
inline bool autoClampActive = false;
inline bool clampState = false;
inline bool liftState = false;
inline bool doinkerLeftState = false;
inline bool doinkerRightState = false;

// declaring piston functions
void setMogoMotors();
void piston_control();
void piston_t();
void clamp_t();

// declaring color sorting variables
inline bool ColorLoopActive = false;
inline bool colorUntilActivated = false;
inline double ambientColorDiff = 0; 
inline double ambientProximity = 60; 
inline bool colorLoopStarted = false;
inline int ringsSeen = 0;
inline int colorUntilRings = 0;
inline bool safeScoring = false;
inline bool rightRingBeingSeen = false;
inline double prevHeading = 0;
inline long prevTime = 0;
inline bool wrongColorDetected;

// declaring color sorting functions
void doColorSort();
void colorSort_t();
void stopColorUntilFunction();
void startColorUntil(int rings);
void handleBlueRing();
void handleRedRing();
void handleRightColor();