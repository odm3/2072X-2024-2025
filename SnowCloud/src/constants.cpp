#include "constants.hpp"
#include "EZ-Template/PID.hpp"
#include "controls.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

pros::Controller controlla(pros::E_CONTROLLER_MASTER);

pros::Motor MOTOR_LF(PORT_LF, pros::v5::MotorGears::blue);
pros::Motor MOTOR_LM(PORT_LM, pros::v5::MotorGears::blue);
pros::Motor MOTOR_LB(PORT_LB, pros::v5::MotorGears::blue);
pros::Motor MOTOR_RF(PORT_RF, pros::v5::MotorGears::blue);
pros::Motor MOTOR_RM(PORT_RM, pros::v5::MotorGears::blue);
pros::Motor MOTOR_RB(PORT_RB, pros::v5::MotorGears::blue);
pros::MotorGroup MOTORGROUP_DRIVE_LEFT({PORT_LF, PORT_LM, PORT_LB}, pros::v5::MotorGears::blue); 
pros::MotorGroup MOTORGROUP_DRIVE_RIGHT({PORT_RF, PORT_RM, PORT_RB}, pros::v5::MotorGears::blue);

pros::Motor MOTOR_INTAKE(PORT_INTAKE, pros::v5::MotorGears::blue);
pros::Motor MOTOR_ARM_LEFT(PORT_ARM_LEFT, pros::v5::MotorGears::green);
pros::Motor MOTOR_ARM_RIGHT(PORT_ARM_RIGHT, pros::v5::MotorGears::green);
pros::MotorGroup MOTORGROUP_ARM({PORT_ARM_LEFT, PORT_ARM_RIGHT}, pros::MotorGears::green);

pros::Imu INERTIAL(PORT_IMU);
pros::Rotation ROTATION_ODOM_HORI(PORT_ROTATION_ODOM_HORI);
pros::Rotation ROTATION_ODOM_VERT(PORT_ROTATION_ODOM_VERT);
pros::Rotation ROTATION_ARM(PORT_ROTATION_ARM);
pros::Rotation ROTATION_INTAKE(PORT_ROTATION_INTAKE);

pros::adi::DigitalOut PISTON_CLAMP(PORT__CLAMP, LOW);
pros::adi::DigitalOut PISTON_DOINKER(PORT_DOINKER, LOW);
pros::adi::DigitalOut PISTON_LIFT(PORT_LIFT, LOW);
pros::adi::DigitalOut PISTON_HANG(PORT_HANG, LOW);
pros::Distance DISTANCE_AUTO_CLAMP(PORT_AUTO_CLAMP);

lemlib::TrackingWheel ODOM_HORI(&ROTATION_ODOM_HORI, lemlib::Omniwheel::NEW_2, OFFSET_HORI);
lemlib::TrackingWheel ODOM_VERT(&ROTATION_ODOM_VERT, lemlib::Omniwheel::NEW_2, OFFSET_VERT);

// drivetrain settings
lemlib::Drivetrain LL_DRIVETRAIN(&MOTORGROUP_DRIVE_LEFT, // left motor group
                              &MOTORGROUP_DRIVE_RIGHT, // right motor group
                              13, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

lemlib::OdomSensors ODOM_SENSORS(&ODOM_VERT, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &ODOM_HORI, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &INERTIAL // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings LL_LAT_CONTROLLER(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings LL_ANG_CONTROLLER(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis LL_CHASSIS(LL_DRIVETRAIN, // drivetrain settings
                        LL_LAT_CONTROLLER, // lateral PID settings
                        LL_ANG_CONTROLLER, // angular PID settings
                        ODOM_SENSORS // odometry sensors
);

 ez::PID armPID(3.25, 0.0, 0,0, "Lady Brown");

void default_constants() {
  EZ_CHASSIS.pid_heading_constants_set(11, 0, 20);
  EZ_CHASSIS.pid_drive_constants_set(2.7, 0, 100);
  // EZ_CHASSIS.pid_drive_constants_set(20, 0, 100);
  EZ_CHASSIS.pid_turn_constants_set(3, 0.05, 20, 15);
  EZ_CHASSIS.pid_swing_constants_set(6, 0, 65);

  EZ_CHASSIS.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EZ_CHASSIS.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EZ_CHASSIS.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  EZ_CHASSIS.pid_turn_chain_constant_set(3_deg);
  EZ_CHASSIS.pid_swing_chain_constant_set(5_deg);
  EZ_CHASSIS.pid_drive_chain_constant_set(3_in);

  EZ_CHASSIS.slew_drive_constants_set(7_in, 80);
}

// EzTemp Chassis constructor
ez::Drive EZ_CHASSIS(
    {PORT_LF, PORT_LM, PORT_LB},      // Left Chassis Ports 
    {PORT_RF, PORT_RM, PORT_RB},  // Right Chassis Ports
    PORT_IMU,      // IMU Port
    lemlib::Omniwheel::NEW_275,  // Wheel Diameter 
    450);   // Wheel RPM