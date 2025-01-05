#pragma once

#include "EZ-Template/PID.hpp"
#include "EZ-Template/drive/drive.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#define PORT_LF -19
#define PORT_LM 9
#define PORT_LB -8
#define PORT_RF 2
#define PORT_RM -4
#define PORT_RB 3

#define PORT_INTAKE     -1
#define PORT_ARM        6
// #define PORT_ARM_LEFT   -6
// #define PORT_ARM_RIGHT  16

#define PORT_IMU 20
#define PORT_ROTATION_ODOM_HORI 12
#define PORT_ROTATION_ODOM_VERT 13
#define PORT_ROTATION_ARM       7
#define PORT_ROTATION_INTAKE    14
#define PORT_OPTICAL_COLOR      15
#define PORT_AUTO_CLAMP  14 
#define PORT__CLAMP      'A'
#define PORT_DOINKER     'B'
#define PORT_LIFT        'C'
#define PORT_HANG        'D'

#define OFFSET_HORI 0
#define OFFSET_VERT 0

#define BUTTON_INTAKE           pros::E_CONTROLLER_DIGITAL_L1
#define BUTTON_INTAKE_REVERSE   pros::E_CONTROLLER_DIGITAL_L2
#define BUTTON_ARM              pros::E_CONTROLLER_DIGITAL_R1
#define BUTTON_ARM_REVERSE      pros::E_CONTROLLER_DIGITAL_R2
#define BUTTON_ARM_PRIME        pros::E_CONTROLLER_DIGITAL_DOWN
#define BUTTON_ARM_SCORE        pros::E_CONTROLLER_DIGITAL_X
#define BUTTON_DOINKER          pros::E_CONTROLLER_DIGITAL_A
#define BUTTON_CLAMP            pros::E_CONTROLLER_DIGITAL_B
#define BUTTON_LIFT             pros::E_CONTROLLER_DIGITAL_Y
#define BUTTON_COLOR_SORT       pros::E_CONTROLLER_DIGITAL_LEFT

extern pros::Controller controlla;

extern pros::Motor MOTOR_LF;
extern pros::Motor MOTOR_LM;
extern pros::Motor MOTOR_LB;
extern pros::Motor MOTOR_RF;
extern pros::Motor MOTOR_RM;
extern pros::Motor MOTOR_RB;

extern pros::Motor      MOTOR_INTAKE;
extern pros::Motor      MOTOR_ARM;
extern pros::Motor      MOTOR_ARM_LEFT;
extern pros::Motor      MOTOR_ARM_RIGHT;
extern pros::MotorGroup MOTORGROUP_ARM;

extern pros::IMU      INERTIAL;
extern pros::Rotation ROTATION_ODOM_HORI;
extern pros::Rotation ROTATION_ODOM_VERT;
extern pros::Rotation ROTATION_ARM;
extern pros::Rotation ROTATION_INTAKE;
extern pros::Optical  OPTICAL_COLOR;

extern pros::adi::DigitalOut PISTON_CLAMP;
extern pros::adi::DigitalOut PISTON_DOINKER;
extern pros::adi::DigitalOut PISTON_LIFT;
extern pros::adi::DigitalOut PISTON_HANG;
extern pros::Distance        DISTANCE_AUTO_CLAMP;

extern lemlib::Drivetrain         LL_DRIVETRAIN;
extern lemlib::TrackingWheel      ODOM_HORI;
extern lemlib::TrackingWheel      ODOM_VERT;
extern lemlib::OdomSensors        ODOM_SENSORS;
extern lemlib::ControllerSettings LL_LAT_CONTROLLER;
extern lemlib::ControllerSettings LL_ANG_CONTROLLER;

extern ez::PID armPID;

extern lemlib::Chassis            LL_CHASSIS;
extern ez::Drive                  EZ_CHASSIS;

extern int lbDriverIndex;
enum ladybrown_states { ARM_DOWN = 200, ARM_PRIME = 2500,  ARM_SCORE = 15000, ALLIANCE_SCORE = 18000 };
enum ringColors       { RED = 15, BLUE = 100};

void default_constants();

// bool doColorSort;
// bool isRedAllinace;