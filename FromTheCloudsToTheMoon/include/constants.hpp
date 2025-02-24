#pragma once
// lists out all the header files that are used in the project
#include "EZ-Template/PID.hpp"
#include "EZ-Template/api.hpp"
#include "EZ-Template/piston.hpp"
#include "api.h"
#include "constants.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

//defines drive motor port variables
#define PORT_LF 18
#define PORT_LM -19
#define PORT_LB -20
#define PORT_RF 13
#define PORT_RM -12
#define PORT_RB 11

//defines subsystem motor port variables
#define PORT_INTAKE    15
#define PORT_ARM       9

//defines piston port variables
#define PORT_CLAMP         'A'
#define PORT_LIFT          'C'
#define PORT_DOINKER_LEFT  'D'
#define PORT_DOINKER_RIGHT 'B'
#define PORT_LIMIT_HOOK    'H'

//defines sensor port variables
#define PORT_IMU            2
#define PORT_ROTATION_ARM   10
#define PORT_DISTANCE_CLAMP 16
#define PORT_OPTICAL_SORT   8
#define PORT_ODOM_VERT      0
#define PORT_ODOM_HORI      0

//defines drive constants
#define WHEEL_DIAMETER 2.75
#define DRIVE_RPM      450 
#define ODOM_DIAMETER  2
#define OFFSET_VERT    0
#define OFFSET_HORI    0
#define DRIVE_CURVE_1  3
#define DRIVE_CURVE_2  8
#define DRIVE_SPEED    110
#define TURN_SPEED     90
#define SWING_SPEED    110
#define ACTIVE_BREAK   0

//defines button variables
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
// #define BUTTON_COLOR_SORT_ON  pros::E_CONTROLLER_DIGITAL_UP
// #define BUTTON_COLOR_SORT_OFF pros::E_CONTROLLER_DIGITAL_LEFT

// Controller constructor
inline pros::Controller controlla(pros::E_CONTROLLER_MASTER);

// Motor constructors
inline pros::Motor motor_LF     (PORT_LF, pros::v5::MotorGears::blue);
inline pros::Motor motor_LM     (PORT_LM, pros::v5::MotorGears::blue);
inline pros::Motor motor_LB     (PORT_LB, pros::v5::MotorGears::blue);
inline pros::Motor motor_RF     (PORT_RF, pros::v5::MotorGears::blue);
inline pros::Motor motor_RM     (PORT_RM, pros::v5::MotorGears::blue);
inline pros::Motor motor_RB     (PORT_RB, pros::v5::MotorGears::blue);

inline pros::Motor motor_intake (PORT_INTAKE, pros::v5::MotorGears::blue);
inline pros::Motor motor_arm    (PORT_ARM, pros::v5::MotorGears::blue);

// Piston constructors
inline ez::Piston piston_clamp         (PORT_CLAMP, false);
inline ez::Piston piston_lift          (PORT_LIFT, false);
inline ez::Piston piston_doinker_left (PORT_DOINKER_LEFT, false);
inline ez::Piston piston_doinker_right (PORT_DOINKER_RIGHT, false);

// Sensor constructors
inline pros::Imu      IMU            (PORT_IMU);
inline pros::Rotation rotation_arm   (PORT_ROTATION_ARM);
inline pros::Distance distance_clamp (PORT_CLAMP);
inline pros::Optical  optical_sort   (PORT_OPTICAL_SORT);
inline pros::adi::DigitalIn limitHook(PORT_LIMIT_HOOK);

// Chassis constructor
inline ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {PORT_LF, PORT_LM, PORT_LB},     // Left Chassis Ports (negative port will reverse it!)
    {PORT_RF, PORT_RM, PORT_RB},    // Right Chassis Ports (negative port will reverse it!)

    PORT_IMU,      // IMU Port
    WHEEL_DIAMETER,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    DRIVE_RPM);   // Wheel RPM = cartridge * (motor gear / wheel gear)

// Odom constructors
//inline ez::tracking_wheel vert_tracker (PORT_ODOM_VERT, ODOM_DIAMETER, OFFSET_VERT);  // This tracking wheel is parallel to the drive wheels
//inline ez::tracking_wheel horiz_tracker(PORT_ODOM_HORI, ODOM_DIAMETER, OFFSET_HORI);  // This tracking wheel is perpendicular to the drive wheels

// drive pid constants
inline void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(3.0, 0.0, 50.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.0, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 150_ms, 7_deg, 150_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 150_ms, 7_deg, 150_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 150_ms, 3_in, 150_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 150_ms, 7_deg, 150_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 150_ms, 3_in, 150_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(6_in, 50);
  chassis.slew_swing_constants_set(6_in, 40);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}


#define armKp 3
#define armKd 10
inline ez::PID armPid(armKp, 0, armKd, 0, "Lady Brown PID");
enum   armStates{ ARM_DOWN = 1000, ARM_PRIME = 2600, ARM_SCORE = 15000, ARM_ALLIANCE = 19000};
inline int armStateIndex = 0;
inline int armStateArray [2] = {ARM_DOWN, ARM_PRIME};