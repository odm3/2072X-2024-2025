#pragma once

#include "LemLib/api.hpp" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"

// declares controller
extern pros::Controller controlla;

// declares rotation sensors for odom with specified ports
extern pros::Rotation odom_vert_sensor;
extern pros::Rotation odom_hozi_sensor;

// declares chassis
extern lemlib::Chassis chassis;

//smart wire ports

//declares drive motors
extern pros::Motor LF_motor;
extern pros::Motor LM_motor;
extern pros::Motor LB_motor;
extern pros::Motor RF_motor;
extern pros::Motor RM_motor;
extern pros::Motor RB_motor;

// declares other motors
extern pros::Motor intake;
extern pros::Motor conveyor;
extern pros::Motor arm;

// declares sensor ports
extern pros::Imu IMU;

// declares tw ports

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

// defined smart wire ports
#define PORT_LF -19
#define PORT_LM 12
#define PORT_LB -11

#define PORT_RF 15
#define PORT_RM -14
#define PORT_RB 13

#define PORT_INTAKE 18
#define PORT_CONVEYOR -20

#define PORT_ARM 4
// #define PORT_ARM_LEFT 5
// #define PORT_ARM_RIGHT -10

//tracking ports

#define PORT_IMU 20

// #define PORT_ODOM_VERT 2
// #define PORT_ODOM_HORI 3

#define PORT_ARM_ROTATION 2

// defines tw ports
#define PORT_INTAKE_LIFT 'G'
// #define PORT_INTAKE_LIFT_LEFT 'A'
// #define PORTS_INTAKE_LIFT_RIGHT 'B'
// #define PORT_CLAMP 'H'
#define PORT_CLAMP_LEFT 'H'
#define PORT_CLAMP_RIGHT 'E'
// #define PORT_CLAW 'E'
#define PORT_DOINKER 'B'
#define PORT_RING_STOPPER 'A'

// defines odom sensor offsets
#define VERTICAL_OFFSET 0
#define HORIZONTAL_OFFSET 0

// defines drive curve
#define DRIVE_CURVE 1

// defines buttons
#define intakeButton pros::E_CONTROLLER_DIGITAL_L1
#define intakeReverseButton pros::E_CONTROLLER_DIGITAL_L2
#define intakeLifTButton pros::E_CONTROLLER_DIGITAL_DOWN
#define ArmUpButton pros::E_CONTROLLER_DIGITAL_R1
#define ArmDownButton pros::E_CONTROLLER_DIGITAL_R2
#define clampButton pros::E_CONTROLLER_DIGITAL_B
#define doinkerButton pros::E_CONTROLLER_DIGITAL_Y
#define ringStopperButton pros::E_CONTROLLER_DIGITAL_RIGHT

// defines algo inputs
#define arm_kp 0.5

// checking devices functions
bool isConnected(int port);
void checkIfConnected(int port, std::string deviceName);
void checkAllDevices();

//brain screen w/ robodash