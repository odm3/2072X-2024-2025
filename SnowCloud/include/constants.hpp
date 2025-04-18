#pragma once

// lists includes
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

// defines drive motor port variables
#define PORT_LF -18
#define PORT_LM 7
#define PORT_LB -6
#define PORT_RF 2
#define PORT_RM -4
#define PORT_RB 3

// defines subsystem motor port variables
#define PORT_INTAKE     -1
#define PORT_ARM        5
// #define PORT_ARM_LEFT   -6
// #define PORT_ARM_RIGHT  16

// defines sensor port variables
#define PORT_IMU 20
#define PORT_ROTATION_ODOM_HORI 12
#define PORT_ROTATION_ODOM_VERT 13
#define PORT_ROTATION_ARM       7
#define PORT_ROTATION_INTAKE    14
#define PORT_OPTICAL_COLOR      15
#define PORT_AUTO_CLAMP  14 
// defines piston port variables
#define PORT__CLAMP      'A'
#define PORT_DOINKER     'B'
#define PORT_LIFT        'C'
#define PORT_HANG        'D'

// defines tracking wheel variables
#define OFFSET_HORI 0
#define OFFSET_VERT 0

// defines controller button variables
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

// declares controller
extern pros::Controller controlla;

// declares drive motor variables
extern pros::Motor MOTOR_LF;
extern pros::Motor MOTOR_LM;
extern pros::Motor MOTOR_LB;
extern pros::Motor MOTOR_RF;
extern pros::Motor MOTOR_RM;
extern pros::Motor MOTOR_RB;

// declares subsystem motor variables
extern pros::Motor      MOTOR_INTAKE;
extern pros::Motor      MOTOR_ARM;
extern pros::Motor      MOTOR_ARM_LEFT;
extern pros::Motor      MOTOR_ARM_RIGHT;
extern pros::MotorGroup MOTORGROUP_ARM;

// declares sensor variables
extern pros::IMU      INERTIAL;
extern pros::Rotation ROTATION_ODOM_HORI;
extern pros::Rotation ROTATION_ODOM_VERT;
extern pros::Rotation ROTATION_ARM;
extern pros::Rotation ROTATION_INTAKE;
extern pros::Optical  OPTICAL_COLOR;

// declares piston variables
extern pros::adi::DigitalOut PISTON_CLAMP;
extern pros::adi::DigitalOut PISTON_DOINKER;
extern pros::adi::DigitalOut PISTON_LIFT;
extern pros::adi::DigitalOut PISTON_HANG;
extern pros::Distance        DISTANCE_AUTO_CLAMP;

// declares lemlib variables
extern lemlib::Drivetrain         LL_DRIVETRAIN;
extern lemlib::TrackingWheel      ODOM_HORI;
extern lemlib::TrackingWheel      ODOM_VERT;
extern lemlib::OdomSensors        ODOM_SENSORS;
extern lemlib::ControllerSettings LL_LAT_CONTROLLER;
extern lemlib::ControllerSettings LL_ANG_CONTROLLER;

// declares arm pid
extern ez::PID armPID;

// declares chassis'
extern lemlib::Chassis            LL_CHASSIS;
extern ez::Drive                  EZ_CHASSIS;
// declares index and arrays for lady brown states and color sorting colors
extern int lbDriverIndex;
enum ladybrown_states { ARM_DOWN = 200, ARM_PRIME = 2500,  ARM_SCORE = 15000, ALLIANCE_SCORE = 18000 };
enum ringColors       { RED = 15, BLUE = 100};

// declares default constants
void default_constants();

// declares color sorting variables
// bool doColorSort;
// bool isRedAllinace;