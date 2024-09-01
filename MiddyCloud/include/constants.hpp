#pragma once

//creates main/master controller implementation
#include "EZ-Template/drive/drive.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

//creates smare wire port implementations

//creates motor smart wire port implementations

//creates drive motor smart wire port implementations
#define PORT_MOTOR_LF -11
#define PORT_MOTOR_LM -12
#define PORT_MOTOR_LB -14
#define PORT_MOTOR_RF 20
#define PORT_MOTOR_RM 19
#define PORT_MOTOR_RB 17

//creates mechanism motor smart wire port implementations
#define PORT_MOTOR_INTAKE_LEFT 13
#define PORT_MOTOR_INTAKE_RIGHT -18
#define PORT_MOTOR_ARM 5

//creates sensor smart wire port implementations
#define PORT_IMU 8
#define PORT_ROTATION_ARM 1
#define PORT_ODOM_VERT -15
#define PORT_ODOM_HORI -16
#define PORT_OPTICAL_HOOD_RING 2

//creates three wire port device implementations
#define PORT_PISTON_INTAKE_LIFT 'H'
#define PORT_PISTON_CLAMP 'F'
#define PORT_PISTON_HAMMER 'G'
#define PORT_PISTON_HANG 'D'

#define PORT_PISTON_HOOD_LIFT 'A'
#define PORT_PISTON_ARM_PIVOT 'B'
#define PORT_PISTON_ARM_CLAMP 'C'

//creates constant floats implementations
#define OFFSET_ODOM_VERT -0.5
#define OFFSET_ODOM_HORI 2

//creates controller button implementations
#define buttonIntake pros::E_CONTROLLER_DIGITAL_L1
#define buttonIntakeReverse pros::E_CONTROLLER_DIGITAL_L2
#define buttonArm pros::E_CONTROLLER_DIGITAL_R1
#define buttonArmReverse pros::E_CONTROLLER_DIGITAL_R2
#define buttonIntakeLift pros::E_CONTROLLER_DIGITAL_LEFT
#define buttonClamp pros::E_CONTROLLER_DIGITAL_RIGHT
#define buttonHammer pros::E_CONTROLLER_DIGITAL_A
#define buttonHang pros::E_CONTROLLER_DIGITAL_B

//creates controller implementation
extern pros::Controller controlla;

//smart wire device implementations

//creates drive smart wire motor implementations
extern pros::Motor MotorLF;
extern pros::Motor MotorLM;
extern pros::Motor MotorLR;
extern pros::Motor MotorRL;
extern pros::Motor MotorRM;
extern pros::Motor MotorRB;

//creates mechanism smart wire motor implementations
extern pros::Motor MotorIntakeLeft;
extern pros::Motor MotorIntakeRight;
extern pros::Motor MotorArm;
extern pros::MotorGroup MotorGroupIntake;

//creates smart wire sensor implementations
extern pros::IMU intertialIMU;
extern pros::Rotation rotationArm;
extern pros::Rotation rotationOdomVert;
extern pros::Rotation rotationOdomHori;
extern pros::Optical opticalHoodRingSensor;

//three wire device implementations

//creates soleniods for pneumatic piston implementations
extern pros::adi::DigitalOut pistonIntakeLift;
extern pros::adi::DigitalOut pistonClamp;
extern pros::adi::DigitalOut pistonHammer;
extern pros::adi::DigitalOut pistonHang;
extern pros::adi::DigitalOut pistonHoodLift;
extern pros::adi::DigitalOut pistonArmPivot;
extern pros::adi::DigitalOut pistonArmClamp;

//creates chassis config implemenations

//drivetrain motorgroup implementations
extern pros::MotorGroup left_chassis;
extern pros::MotorGroup right_chassis;

//creates lemlib drivetrain implementation
extern lemlib::Drivetrain LLDrivetrain;

//creates odom sensor implementations
extern lemlib::TrackingWheel odom_vert_wheel;
extern lemlib::TrackingWheel odom_hori_wheel;
extern lemlib::OdomSensors LLOdomSensors;

//creates PID controller implementations
extern lemlib::ControllerSettings LLLateral_controller;
extern lemlib::ControllerSettings LLAngular_controller;
void default_constants();

//creates full chassis implementations for both libs
extern lemlib::Chassis LemLibChassis;
extern ez::Drive EzTempChassis;
