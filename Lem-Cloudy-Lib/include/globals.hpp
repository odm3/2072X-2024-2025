
#include "LemLib/api.hpp"

 #pragma once 
// V5 ports


#define PORT_LF -1
#define PORT_LM -2
#define PORT_LB -2

#define PORT_RF 4
#define PORT_RM 5
#define PORT_RB 6

#define PORT_LPTO 7
#define PORT_RPTO 8

#define PORT_INTAKE 7
#define PORT_LIFT 8

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

namespace  globals {

    //chassis

extern pros::Motor LF_motor;
extern pros::Motor LM_motor;
extern pros::Motor LB_motor;
extern pros::Motor RF_motor;
extern pros::Motor RM_motor;
extern pros::Motor RB_motor;
extern pros::Motor LPTO_motor;
extern pros::Motor RPTO_motor;

extern pros::MotorGroup left_chassis;
extern pros::MotorGroup right_chassis;

extern lemlib::Drivetrain drivetrain;

extern pros::Imu IMU;

extern pros::Rotation odom_vert_sensor;
extern pros::Rotation odom_hori_sensor;

extern lemlib::TrackingWheel odom_vert_wheel;
extern lemlib::TrackingWheel odom_hori_wheel;

extern lemlib::OdomSensors odom_sensors;

extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

extern lemlib::ExpoDriveCurve lateral_curve;

extern lemlib::Chassis chassis;


    //mechanisms

extern pros::Motor intake;
extern pros::Motor lift;



    //tw ports

extern pros::adi::DigitalOut intake_lift;
extern pros::adi::DigitalOut mogo_clamp;

    //other shii

}

