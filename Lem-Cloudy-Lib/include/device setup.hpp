#pragma once

#include "LemLib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"

//defining motor powers
#define PORT_LF -1
#define PORT_LM -2
#define PORT_LB -2

#define PORT_RF 4
#define PORT_RM 5
#define PORT_RB 6

#define PORT_LIFT 7
#define PORT_INTAKE 8
/*#define PORT_INTAKE2 9*/

//tracking ports

#define PORT_IMU 9

#define PORT_ODOM_VERT 11
#define PORT_ODOM_HORI 12

//tw ports

#define PORT_INTAKE_LIFT "A"
#define PORT_MOGO_CLAMP "B"

//other constants

#define VERTICAL_OFFSET 0
#define HORIZONTAL_OFFSET 0

#define DRIVE_CURVE 1
//chassis

extern pros::Rotation odom_vert_sensor;
extern pros::Rotation odom_hozi_sensor;


extern lemlib::Chassis chassis;


//mechanisms

extern pros::Motor intake;
extern pros::Motor lift;



//tw ports

extern pros::adi::DigitalOut intake_lift;
extern pros::adi::DigitalOut mogo_clamp;

//other shii


