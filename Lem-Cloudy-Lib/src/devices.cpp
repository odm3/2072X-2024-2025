#pragma once

#include "main.h" // IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"

namespace devices {
    //creates controller
pros::Controller controlla (pros::E_CONTROLLER_MASTER);

//creates drive motors with specified ports and gearsets
pros::Motor LF_motor(PORT_LF, pros::MotorGears::blue);
pros::Motor LM_motor(PORT_LM, pros::MotorGears::blue);;
pros::Motor LB_motor(PORT_LB, pros::MotorGears::blue);;
pros::Motor RF_motor(PORT_RF, pros::MotorGears::blue);;
pros::Motor RM_motor(PORT_RM, pros::MotorGears::blue);;
pros::Motor RB_motor(PORT_RB, pros::MotorGears::blue);;

//creates left motor groups with inducidual motors listed above
pros::MotorGroup left_chassis({ PORT_LF, PORT_LM, PORT_LB }, pros::MotorGearset::blue);
//creates right motor groups with inducidual motors listed above
pros::MotorGroup right_chassis({ PORT_RF, PORT_RM, PORT_RB }, pros::MotorGearset::blue);

//creates drivetrain with certain variables listed below
lemlib::Drivetrain drivetrain(&left_chassis, // left motor group
                              &right_chassis, // right motor group
                              13.5, // 13 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

//creates imu sensor with specified port
pros::Imu IMU(PORT_IMU);

// //creates rotation sensors for odom with specified ports
// pros::Rotation odom_vert_sensor(PORT_ODOM_VERT);
// pros::Rotation odom_hozi_sensor(PORT_ODOM_HORI);

// //creates odom tracking wheel configuration with specified rotation sensors, wheel sizes, and offsets
// lemlib::TrackingWheel odom_vert_wheel(&odom_vert_sensor, lemlib::Omniwheel::NEW_2, VERTICAL_OFFSET);
// lemlib::TrackingWheel odom_hori_wheel(&odom_hozi_sensor, lemlib::Omniwheel::NEW_2, HORIZONTAL_OFFSET);


//creates entire odom sensor variable with all classes above
lemlib::OdomSensors odom_sensors(
    nullptr, 
    nullptr, 
    nullptr, 
    nullptr,
    &IMU // inertial sensor
);

//creates lateral PID controller variable
lemlib::ControllerSettings lateral_controller(
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

//creates angular PID controller variable
lemlib::ControllerSettings angular_controller(
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

//creates an exponential drive curve function variable with specified deadzone, minimum output, and curve.
lemlib::ExpoDriveCurve lateral_curve(
    5,
    10,
    DRIVE_CURVE
);

//creates chassis variable with all listed above
lemlib::Chassis chassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    odom_sensors,
    &lateral_curve);

//mechanism motors
pros::Motor intake(PORT_INTAKE, pros::MotorGears::rpm_200);
pros::Motor conveyor(PORT_CONVEYOR, pros::MotorGears::rpm_200);
// pros::MotorGroup arm({PORT_ARM_LEFT, PORT_ARM_RIGHT}, pros::MotorGears::rpm_200);
pros::Motor arm(PORT_ARM, pros::MotorGearset::rpm_100);

//pistons
pros::adi::DigitalOut intake_lift_left(PORT_INTAKE_LIFT_LEFT, LOW);
pros::adi::DigitalOut intake_lift_right(PORTS_INTAKE_LIFT_RIGHT, LOW);
pros::adi::DigitalOut clamp_left(PORT_CLAMP_LEFT, LOW);
pros::adi::DigitalOut clamp_right(PORT_CLAMP_RIGHT, LOW);
// pros::adi::DigitalOut claw(PORT_CLAW, LOW);
pros::adi::DigitalOut doinker(PORT_DOINKER, LOW);
pros::adi::DigitalOut ring_stopper(PORT_RING_STOPPER,LOW);
}
