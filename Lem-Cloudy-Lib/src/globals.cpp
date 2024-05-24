#include "main.h"
#include "LemLib/api.hpp"
#include "globals.hpp"

// using namespace globals;

//individual motor delcarations
pros::Motor LF_motor(PORT_LF, pros::MotorGears::blue);
pros::Motor LM_motor(PORT_LM, pros::MotorGears::blue);;
pros::Motor LB_motor(PORT_LB, pros::MotorGears::blue);;
pros::Motor RF_motor(PORT_RF, pros::MotorGears::blue);;
pros::Motor RM_motor(PORT_RM, pros::MotorGears::blue);;
pros::Motor RB_motor(PORT_RB, pros::MotorGears::blue);;
pros::Motor LPTO_motor(PORT_LPTO, pros::MotorGears::blue);
pros::Motor RPTO_motor(PORT_RPTO, pros::MotorGears::blue);

// left motor group
pros::MotorGroup left_chassis({ PORT_LF, PORT_LM, PORT_LB }, pros::MotorGearset::blue);
// right motor group
pros::MotorGroup right_chassis({ PORT_RF, PORT_RM, PORT_RB }, pros::MotorGearset::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_chassis, // left motor group
                              &right_chassis, // right motor group
                              13, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

//makes imu sensor
pros::Imu IMU(PORT_IMU);

//makes rotation sensors for odom
pros::Rotation odom_vert_sensor(PORT_ODOM_VERT);
pros::Rotation odom_hozi_sensor(PORT_ODOM_HORI);

//makes odom tracking wheel configured 
lemlib::TrackingWheel odom_vert_wheel(&odom_vert_sensor, lemlib::Omniwheel::NEW_2, VERTICAL_OFFSET);
lemlib::TrackingWheel odom_hori_wheel(&odom_hozi_sensor, lemlib::Omniwheel::NEW_2, HORIZONTAL_OFFSET);

lemlib::OdomSensors odom_sensors(&odom_vert_wheel, nullptr, &odom_hori_wheel, nullptr, &IMU);

// makes lateral PID controller
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

// makes angular PID controller
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

lemlib::ExpoDriveCurve lateral_curve(3, 10, DRIVE_CURVE);

//makes chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, odom_sensors, &lateral_curve);
