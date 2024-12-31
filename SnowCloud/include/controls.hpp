#pragma once

// bool toggleClamp     = false;
// bool toggleDoinker   = false;
// bool toggleLift      = false;
// bool toggleHang      = false;
// bool toggleArmStates = false;

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
void controlArmManual();
void controlArmPrime();
void controlArmScore();
void controlClamp();
void controlDoinker();
void controlLift();
void controlHang();
void detectClamp();
void autoClamp_task();

extern void controlArmTask();
extern int lbArray[2];

int toggleClampInt();