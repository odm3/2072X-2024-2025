#pragma once

#include "pros/rtos.hpp"

// . . .
// 
//  DRIVER CONTROL
//
// . . .
bool getShiftKey();

void tank_drive(double curve = 7.0);
void set_drive_to_coast();
void set_drive_to_hold();

void spinLift(double power);
void spinLiftPID(double rpm);

void liftControl();
void liftAutoControl(double targetLiftValue);
void startLiftTask(double targetLiftValue);

extern const double MAX_LIFT_VALUE;
extern double FIRST_RING_LIFT_VALUE;