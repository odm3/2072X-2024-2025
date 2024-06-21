#pragma once

#include "LemLib/api.hpp"

extern pros::Controller controlla;

//defining motor ports
#define PORT_LF -1
#define PORT_LM -2
#define PORT_LB -3

#define PORT_RF 4
#define PORT_RM 5
#define PORT_RB 6

#define PORT_INTAKE 8
#define PORT_CONVEYOR 9

#define PORT_ARM_LEFT 11
#define PORT_ARM_RIGHT -12


//tracking ports

#define PORT_IMU 10

#define PORT_ODOM_VERT 13
#define PORT_ODOM_HORI 14

//tw ports

#define PORT_INTAKE_LIFT 'A'
#define PORT_CLAMP 'B'
#define PORT_CLAW 'C'
#define PORT_DOINKER 'D'

//other constants

#define VERTICAL_OFFSET 0
#define HORIZONTAL_OFFSET 0

#define DRIVE_CURVE 1
//chassis

extern pros::Rotation odom_vert_sensor;
extern pros::Rotation odom_hozi_sensor;


extern lemlib::Chassis chassis;

//drive motors
// extern pros::Motor LF_motor;
// extern pros::Motor LM_motor;
// extern pros::Motor LB_motor;
// extern pros::Motor RF_motor;
// extern pros::Motor RM_motor;
// extern pros::Motor RB_motor;

//other motors
extern pros::Motor intake;
extern pros::Motor conveyor;
extern pros::MotorGroup arm;

//tw ports

extern pros::adi::DigitalOut intake_lift;
extern pros::adi::DigitalOut clamp;
extern pros::adi::DigitalOut claw;
extern pros::adi::DigitalOut doinker;
