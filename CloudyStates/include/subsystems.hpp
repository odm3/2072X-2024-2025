#pragma once

// including all necessary header files
#include "api.h"
#include "EZ-Template/api.hpp"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/link.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

// declaring drive motor port variables
#define PORT_LF 18
#define PORT_LM -19
#define PORT_LB -20
#define PORT_RF 13
#define PORT_RM -12
#define PORT_RB 11

// declaring subsystem motor port variables
#define PORT_INTAKE    15
#define PORT_ARM       10

// declaring subsystem piston port variables
#define PORT_CLAMP         'A'
#define PORT_LIFT          'B'
#define PORT_DOINKER_LEFT  'C'
#define PORT_DOINKER_RIGHT 'D'

// declaring smartwire sensor port variables
#define PORT_IMU            2
#define PORT_ROTATION_ARM   -9
#define PORT_OPTICAL_CLAMP  17
#define PORT_OPTICAL_SORT   8
#define PORT_ODOM_VERT      13
#define PORT_ODOM_HORI      14
#define PORT_VEXNET         21

// declaring constant variables
#define WHEEL_DIAMETER 3.25
#define DRIVE_RPM      450 
#define TRACK_WIDTH    9.5
#define ODOM_DIAMETER  2.125
#define OFFSET_VERT    0
#define OFFSET_HORI    0
#define EZ_DRIVE_CURVE_1  1
#define EZ_DRIVE_CURVE_2  10
#define DRIVE_SPEED    110
#define TURN_SPEED     90
#define SWING_SPEED    110

// declaring controller button variables
#define BUTTON_INTAKE         pros::E_CONTROLLER_DIGITAL_L1
#define BUTTON_INTAKE_REVERSE pros::E_CONTROLLER_DIGITAL_L2
#define BUTTON_ARM            pros::E_CONTROLLER_DIGITAL_R1
#define BUTTON_ARM_REVERSE    pros::E_CONTROLLER_DIGITAL_R2
#define BUTTON_ARM_PRIME      pros::E_CONTROLLER_DIGITAL_DOWN
#define BUTTON_ARM_SCORE      pros::E_CONTROLLER_DIGITAL_X
#define BUTTON_CLAMP          pros::E_CONTROLLER_DIGITAL_B
#define BUTTON_LIFT           pros::E_CONTROLLER_DIGITAL_Y
#define BUTTON_DOINKER_LEFT   pros::E_CONTROLLER_DIGITAL_LEFT
#define BUTTON_DOINKER_RIGHT  pros::E_CONTROLLER_DIGITAL_A
#define BUTTON_COLOR_SORT     pros::E_CONTROLLER_DIGITAL_RIGHT

// controller constructors
inline pros::Controller controlla(pros::E_CONTROLLER_MASTER);

// drive motor constructors
inline pros::Motor motor_LF     (PORT_LF, pros::v5::MotorGears::blue);
inline pros::Motor motor_LM     (PORT_LM, pros::v5::MotorGears::blue);
inline pros::Motor motor_LB     (PORT_LB, pros::v5::MotorGears::blue);
inline pros::Motor motor_RF     (PORT_RF, pros::v5::MotorGears::blue);
inline pros::Motor motor_RM     (PORT_RM, pros::v5::MotorGears::blue);
inline pros::Motor motor_RB     (PORT_RB, pros::v5::MotorGears::blue);

// subsystem motor constructors
inline pros::Motor motor_intake (PORT_INTAKE, pros::v5::MotorGears::blue);
inline pros::Motor motor_arm    (PORT_ARM, pros::v5::MotorGears::blue);

// subsystem constructors
inline ez::Piston piston_clamp         (PORT_CLAMP, false);
inline ez::Piston piston_lift          (PORT_LIFT, false);
inline ez::Piston piston_doinker_left (PORT_DOINKER_LEFT, false);
inline ez::Piston piston_doinker_right (PORT_DOINKER_RIGHT, false);

// smartwire sensor constructors
inline pros::Imu      imu            (PORT_IMU);
inline pros::Rotation rotation_arm   (PORT_ROTATION_ARM);
inline pros::Optical optical_clamp  (PORT_OPTICAL_CLAMP);
inline pros::Optical  optical_sort   (PORT_OPTICAL_SORT);
inline pros::Rotation odom_hori      (PORT_ODOM_HORI);
inline pros::Rotation odom_vert      (PORT_ODOM_VERT);
inline pros::Link     vexnet         (PORT_VEXNET, "2072x_link", pros::E_LINK_TX);

// drive motorgroup constructors
inline pros::MotorGroup leftMotors({PORT_LF, PORT_LM, PORT_LB}, pros::MotorGearset::blue); // left motor group
inline pros::MotorGroup rightMotors({PORT_RF, PORT_RM, PORT_RB}, pros::MotorGearset::blue); // right motor group

// tracking wheel constructors
inline lemlib::TrackingWheel odom_hori_LL(&odom_hori, ODOM_DIAMETER, OFFSET_HORI);
inline ez::tracking_wheel odom_hori_EZ(PORT_ODOM_HORI, ODOM_DIAMETER, OFFSET_HORI);
inline lemlib::TrackingWheel odom_vert_LL(&odom_vert, ODOM_DIAMETER, OFFSET_VERT);
inline ez::tracking_wheel odom_vert_EZ(9, ODOM_DIAMETER, OFFSET_VERT);

// lemlib drivetrain constructor
inline lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              TRACK_WIDTH, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              DRIVE_RPM, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lemlib lateral motion controller constructor
inline lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// lemlib angular motion controller constructor
inline lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// lemib odom sensors constructor
inline lemlib::OdomSensors sensors(&odom_vert_LL, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2,
                            &odom_hori_LL, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2,
                            &imu // inertial sensor
);

// lemlib throttle curve constructor
inline lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// lemlib steer curve constructor
inline lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// lemlib chassis constructor
inline lemlib::Chassis LLCHASSIS(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

// Chassis constructor
inline ez::Drive EzChassis(
  //drive motors, the first motor is used for sensing
  {PORT_LF, PORT_LM, PORT_LB},     // Left Chassis Ports
  {PORT_RF, PORT_RM, PORT_RB},  // Right Chassis Ports

  PORT_IMU,      // IMU Port
  WHEEL_DIAMETER,  // Wheel Diameter
  DRIVE_RPM);   // Wheel RPM = cartridge * (motor gear / wheel gear)

// Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
//  - change `back` to `front` if the tracking wheel is in front of the midline
//  - ignore this if you aren't using a horizontal tracker
// EzChassis.odom_tracker_back_set(&horiz_tracker);
// Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
//  - change `left` to `right` if the tracking wheel is to the right of the centerline
//  - ignore this if you aren't using a vertical tracker
// EzChassis.odom_tracker_left_set(&vert_tracker);


inline void default_constants() {
  // P, I, D, and Start I
  EzChassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  EzChassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  EzChassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  EzChassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  EzChassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  EzChassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions
      
  // Exit conditions
  EzChassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EzChassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EzChassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  EzChassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  EzChassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  // motion chaining constants
  EzChassis.pid_turn_chain_constant_set(3_deg);
  EzChassis.pid_swing_chain_constant_set(5_deg);
  EzChassis.pid_drive_chain_constant_set(3_in);
  
  // Slew constants
  EzChassis.slew_turn_constants_set(3_deg, 70);
  EzChassis.slew_drive_constants_set(3_in, 70);
  EzChassis.slew_swing_constants_set(3_in, 80);
  
  // The amount that turns are prioritized over driving in odom motions
  EzChassis.odom_turn_bias_set(0.9);
  
  EzChassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  EzChassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  EzChassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are
  
  EzChassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}