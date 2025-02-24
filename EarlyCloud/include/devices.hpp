#pragma once
// lists all the includes for the devices
#include "LemLib/api.hpp" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"
#include "Ez-Template/api.hpp"
#include "Timer.h"

// declares the timer
extern Timer timer;

// declares the controller
extern pros::Controller controlla;

// declaes the drive motors
extern pros::Motor LF_motor;
extern pros::Motor LM_motor;
extern pros::Motor LB_motor;
extern pros::Motor RF_motor;
extern pros::Motor RM_motor;
extern pros::Motor RB_motor;

// declres the other motors
extern pros::Motor intake;
extern pros::Motor conveyor;
extern pros::Motor arm;

// declares the sensors
extern pros::Imu IMU;
extern pros::Rotation armRotation;
extern pros::Rotation conveyorRotation;

// declare the three wire port devices
extern pros::adi::DigitalOut intake_lift;
extern pros::adi::DigitalOut intake_lift_left;
extern pros::adi::DigitalOut intake_lift_right;
extern pros::adi::DigitalOut clamp;
extern pros::adi::DigitalOut clamp_left;
extern pros::adi::DigitalOut clamp_right;
extern pros::adi::DigitalOut claw;
extern pros::adi::DigitalOut doinker;
extern pros::adi::DigitalOut ring_stopper;
extern pros::Rotation odom_vert_sensor;
extern pros::Rotation odom_hozi_sensor;

//defines the algorithm input variables
#define activeBreak_kp 0.1
#define arm_kp 0.5

// declares the pid constants
void default_constants();
void mogo_constants();
void mogo_rings_constants();

// declares the chassis'
extern lemlib::Chassis LemLibChassis;
extern ez::Drive EzTempChassis;

// defines the odom offsets
#define VERTICAL_OFFSET 0
#define HORIZONTAL_OFFSET 0

// defines drive curves for both chassis, values are vastly different as different equations are used
#define LEMLIB_DRIVE_CURVE 1.25
#define EZTEMP_DRIVE_CURVE 5

// defines smart wire ports

// defines drive motor ports
#define PORT_LF -19
#define PORT_LM 12
#define PORT_LB -6

#define PORT_RF 15
#define PORT_RM -14
#define PORT_RB 13

// defines other motor ports
#define PORT_INTAKE 18
#define PORT_CONVEYOR -20        /*SCRAPPED*/
#define PORT_ARM 4               /*SCRAPPED*/
#define PORT_ARM_LEFT 5          /*SCRAPPED*/
#define PORT_ARM_RIGHT -10       /*SCRAPPED*/

// defines sensor ports
#define PORT_IMU 16
#define PORT_ARM_ROTATION -2     /*SCRAPPED*/
#define PORT_CONVEYOR_ROTATION 3 /*SCRAPPED*/
#define PORT_ODOM_VERT 10
#define PORT_ODOM_HORI 11

// defines three wireports
#define PORT_INTAKE_LIFT 'G'
#define PORT_INTAKE_LIFT_LEFT 'A'    /*SCRAPPED*/
#define PORTS_INTAKE_LIFT_RIGHT 'B'  /*SCRAPPED*/
#define PORT_CLAMP 'H'               /*SCRAPPED*/
#define PORT_CLAMP_LEFT 'H'
#define PORT_CLAMP_RIGHT 'E'
#define PORT_CLAW 'E'                /*SCRAPPED*/
#define PORT_DOINKER 'B'             /*SCRAPPED*/
#define PORT_RING_STOPPER 'A'        /*SCRAPPED*/

// defines buttons
#define intakeButton pros::E_CONTROLLER_DIGITAL_L1
#define intakeReverseButton pros::E_CONTROLLER_DIGITAL_L2
#define intakeLifTButton pros::E_CONTROLLER_DIGITAL_Y
#define ArmUpButton pros::E_CONTROLLER_DIGITAL_R1
#define ArmDownButton pros::E_CONTROLLER_DIGITAL_R2
#define clampButton pros::E_CONTROLLER_DIGITAL_B
#define doinkerButton pros::E_CONTROLLER_DIGITAL_RIGHT           /*SCRAPPED*/
#define ringStopperButton pros::E_CONTROLLER_DIGITAL_DOWN        /*SCRAPPED*/