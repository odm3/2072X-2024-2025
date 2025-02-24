#pragma once

// declares the intake functions
void intakeVoltage(int voltage);
void intakeVoltage1(int voltage);
void intakeControl();
void intakeLiftUp();
void intakeLiftDown();
void intakeLiftControl();

// declares the clamp functions
void clampActivate();
void clampRetract();
void clampControl();

// declares the doinker functions
void doinkerActivate();
void doinkerRetract();
void doinkerControl();

// declares the ringStopper functions
void ringStopperActivate();
void ringStopperRetract();
void ringStopperControl();

// declares the arm functions
void armVoltage(int Voltage);
void armToZero();
void armToAllianceStake();
void armToWallStake();
void armControl();