#pragma once

#include "main.h"

extern pros::Controller master;

extern pros::Motor intake;
extern pros::Motor liftLeft;
extern pros::Motor liftRight;


extern pros::MotorGroup left_side_motors;
extern pros::MotorGroup right_side_motors;

extern pros::ADIDigitalOut intakeRaise;
extern pros::ADIDigitalOut backClamp;
extern pros::ADIDigitalOut doinker;
extern pros::ADIDigitalOut ringRush;


extern pros::Rotation liftSensor;

extern bool wingsOut;
extern bool liftUp;

extern Drive chassis;

void checkMotorsAndPrintTemperature();
void calibrateChassis();
void chassisInits();
