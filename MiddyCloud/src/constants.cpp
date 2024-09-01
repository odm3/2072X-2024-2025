#include "constants.hpp"
#include "main.h"   //IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/motor_group.hpp"

pros::Controller controlla(pros::E_CONTROLLER_MASTER);

//smart wire port devices

//creates drive motors with specified ports and gearsets
pros::Motor MotorLF(PORT_MOTOR_LF, pros::MotorGears::blue);
pros::Motor MotorLM(PORT_MOTOR_LM, pros::MotorGears::blue);;
pros::Motor MotorLB(PORT_MOTOR_LB, pros::MotorGears::blue);;
pros::Motor MotorRF(PORT_MOTOR_RF, pros::MotorGears::blue);;
pros::Motor MotorRM(PORT_MOTOR_RM, pros::MotorGears::blue);;
pros::Motor MotorRB(PORT_MOTOR_RB, pros::MotorGears::blue);;

//creates mechanism motors with specified ports and gearsets
pros::Motor MotorIntakeLeft(PORT_MOTOR_INTAKE_LEFT, pros::MotorGears::blue);
pros::Motor MotorIntakeRight(PORT_MOTOR_INTAKE_RIGHT, pros::MotorGears::blue);
pros::Motor MotorArm(PORT_MOTOR_ARM, pros::MotorGears::green);
pros::MotorGroup MotorGroupIntake({PORT_MOTOR_INTAKE_LEFT, PORT_MOTOR_INTAKE_RIGHT}, pros::v5::MotorGears::blue);

//creates smart wire sensors with their ports
pros::Imu intertialIMU(PORT_IMU);
pros::Rotation rotationArm(PORT_ROTATION_ARM);
pros::Rotation rotationOdomVert(PORT_ODOM_VERT);
pros::Rotation rotationOdomHori(PORT_ODOM_HORI);
pros::Optical opticalHoodRingSensor(PORT_OPTICAL_HOOD_RING);

//creates three wire port devices with ports and init states
pros::adi::DigitalOut pistonIntakeLift(PORT_PISTON_INTAKE_LIFT, false);
pros::adi::DigitalOut pistonClamp(PORT_PISTON_CLAMP, false);
pros::adi::DigitalOut pistonHammer(PORT_PISTON_HAMMER, false);
pros::adi::DigitalOut pistonHang(PORT_PISTON_HANG, false);
pros::adi::DigitalOut pistonHoodLift(PORT_PISTON_HOOD_LIFT, false);
pros::adi::DigitalOut pistonArmPivot(PORT_PISTON_ARM_PIVOT, false);
pros::adi::DigitalOut pistonArmClamp(PORT_PISTON_ARM_CLAMP, false);

//creates EzTempChassis configs

//creates left motor groups with motors and gearsets
pros::MotorGroup left_chassis({ PORT_MOTOR_LF, PORT_MOTOR_LM, PORT_MOTOR_LB }, pros::MotorGearset::blue);
//creates right motor groups with motor ports and gearsets
pros::MotorGroup right_chassis({ PORT_MOTOR_RF, PORT_MOTOR_RM, PORT_MOTOR_RB }, pros::MotorGearset::blue); 

//creates Lemlib Chassis prerequisites

//creates lemlib drivetrain with motorgroups, track width, wheel diameter, wheel rpm, and drift
lemlib::Drivetrain LLDrivetrain (
    &left_chassis,
    &right_chassis,
    13.5,
    lemlib::Omniwheel::NEW_325,
    450,
    2
);

//creates tracking wheels
lemlib::TrackingWheel odom_vert_wheel(&rotationOdomVert, lemlib::Omniwheel::NEW_2, OFFSET_ODOM_VERT);
lemlib::TrackingWheel odom_hori_wheel(&rotationOdomHori, lemlib::Omniwheel::NEW_2, OFFSET_ODOM_HORI);

//creates a lemlib odom sensors class
lemlib::OdomSensors LLOdomSensors(
    &odom_vert_wheel, 
    nullptr,
    &odom_hori_wheel,
    nullptr,
    &intertialIMU
);

//creates lateral drive PID controller 
lemlib::ControllerSettings LLLateral_controller(
    10, // proportional gain (kP)
    0, // integral gain (kI)
    3, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

//creates angular drive PID controller 
lemlib::ControllerSettings LLAngular_controller(
    2, // proportional gain (kP)
    0, // integral gain (kI)
    10, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

//constants used for functions that the EzTempChassis uses
void default_constants() {
  EzTempChassis.pid_heading_constants_set(11, 0, 20);
  EzTempChassis.pid_drive_constants_set(20, 0, 100);
  EzTempChassis.pid_turn_constants_set(3, 0.05, 20, 15);
  EzTempChassis.pid_swing_constants_set(6, 0, 65);

  EzTempChassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EzTempChassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EzTempChassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  EzTempChassis.pid_turn_chain_constant_set(3_deg);
  EzTempChassis.pid_swing_chain_constant_set(5_deg);
  EzTempChassis.pid_drive_chain_constant_set(3_in);

  EzTempChassis.slew_drive_constants_set(7_in, 80);
}

//creates LemLib EzTempChassis
lemlib::Chassis LemLibChassis(
    LLDrivetrain,
    LLLateral_controller,
    LLAngular_controller,
    LLOdomSensors
);

//creates EzTemp EzTempChassis
ez::Drive EzTempChassis(
    {PORT_MOTOR_LF, PORT_MOTOR_LM, PORT_MOTOR_LB},
    {PORT_MOTOR_RF, PORT_MOTOR_RM, PORT_MOTOR_RB},
    PORT_IMU,
    lemlib::Omniwheel::NEW_325,
    600,
    48.0/36.0
);