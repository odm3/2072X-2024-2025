#pragma once

// bool toggleClamp;
// bool toggleDoinker;
// bool toggleLift;
// bool toggleHang;

#include "controls.hpp"
void moveIntake(double vltg);
void moveArm(double vltg);
void moveArmStates();

void activateClamp();
void deactivateClamp();
void activateDoinker();
void deactivateDoinker();
void activateLift();
void deactivateLift();

void controlIntake();
void controlArm();
void controlArmPrime();
void controlArmScore();
void controlClamp();
void controlDoinker();
void controlLift();
void controlHang();
extern void controlArmTask();
extern int lbArray[2];