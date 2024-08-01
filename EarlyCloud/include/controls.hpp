#pragma once

void intakeVoltage(int voltage);
void intakeVoltage1(int voltage);
void intakeControl();
void intakeLiftUp();
void intakeLiftDown();
void intakeLiftControl();

void clampActivate();
void clampRetract();
void clampControl();

void doinkerActivate();
void doinkerRetract();
void doinkerControl();

void ringStopperActivate();
void ringStopperRetract();
void ringStopperControl();


void armVoltage(int Voltage);
void armToZero();
void armToAllianceStake();
void armToWallStake();
void armControl();

#include "api.h"