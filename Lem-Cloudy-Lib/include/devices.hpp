#pragma once

#include "LemLib/api.hpp" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/rotation.hpp"

namespace devices {
extern pros::Controller controlla;

extern pros::Rotation odom_vert_sensor;
extern pros::Rotation odom_hozi_sensor;


extern lemlib::Chassis chassis;

//drive motors
extern pros::Motor LF_motor;
extern pros::Motor LM_motor;
extern pros::Motor LB_motor;
extern pros::Motor RF_motor;
extern pros::Motor RM_motor;
extern pros::Motor RB_motor;

//other motors
extern pros::Motor intake;
extern pros::Motor conveyor;
extern pros::Motor arm;

//tw ports

extern pros::adi::DigitalOut intake_lift;
extern pros::adi::DigitalOut intake_lift_left;
extern pros::adi::DigitalOut intake_lift_right;
extern pros::adi::DigitalOut clamp;
extern pros::adi::DigitalOut clamp_left;
extern pros::adi::DigitalOut clamp_right;
// extern pros::adi::DigitalOut claw;
extern pros::adi::DigitalOut doinker;
extern pros::adi::DigitalOut ring_stopper;

extern pros::Rotation armRotation;
}

//smart wire ports
#define PORT_LF -18
#define PORT_LM 12
#define PORT_LB -13

#define PORT_RF 17
#define PORT_RM -16
#define PORT_RB 15

#define PORT_INTAKE 14
#define PORT_CONVEYOR -19

#define PORT_ARM 11
// #define PORT_ARM_LEFT 5
// #define PORT_ARM_RIGHT -10

//tracking ports

#define PORT_IMU 20

// #define PORT_ODOM_VERT 2
// #define PORT_ODOM_HORI 3

#define PORT_ARM_ROTATION 1

//tw ports
#define PORT_INTAKE_LIFT 'H'
// #define PORT_INTAKE_LIFT_LEFT 'A'
// #define PORTS_INTAKE_LIFT_RIGHT 'B'
#define PORT_CLAMP 'G'
// #define PORT_CLAMP_LEFT 'C'
// #define PORT_CLAMP_RIGHT 'D'
// #define PORT_CLAW 'E'
#define PORT_DOINKER 'F'
#define PORT_RING_STOPPER 'A'

//odom sensor offsets
#define VERTICAL_OFFSET 0
#define HORIZONTAL_OFFSET 0

//drive curve
#define DRIVE_CURVE 3

//buttons
#define intakeButton pros::E_CONTROLLER_DIGITAL_L1
#define intakeReverseButton pros::E_CONTROLLER_DIGITAL_L2
#define intakeLifTButton pros::E_CONTROLLER_DIGITAL_DOWN
#define ArmUpButton pros::E_CONTROLLER_DIGITAL_R1
#define ArmDownButton pros::E_CONTROLLER_DIGITAL_R2
#define clampButton pros::E_CONTROLLER_DIGITAL_B
#define doinkerButton pros::E_CONTROLLER_DIGITAL_Y
#define ringStopperButton pros::E_CONTROLLER_DIGITAL_RIGHT