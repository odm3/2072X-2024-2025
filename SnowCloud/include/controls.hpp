#pragma once
#include "controls.hpp"

// declares moveing functions
void moveIntake(double vltg);
void moveArm(double vltg);
void moveArmStates();

// declares auto functions
void activateClamp();
void deactivateClamp();
void activateDoinker();
void deactivateDoinker();
void activateLift();
void deactivateLift();

// declares driver control functions
void controlIntake();
void controlArm();
void controlArmManual();
void controlArmPrime();
void controlArmScore();
void controlClamp();
void controlDoinker();
void controlLift();
void controlHang();
void detectClamp();
void autoClamp_task();

// declares pid arm functions
extern void controlArmTask();
extern int lbArray[2];

// declares auto clamp variable
int toggleClampInt();