#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "controls.hpp"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

//  auto that just drives forward a little bit, use if teammate has a good soloawp
void drive2() { EzChassis.pid_drive_set(2, DRIVE_SPEED); }

void soloAwp() {

}

void soloAwpRed() { soloAwp(); }
void soloAwpBlue() { EzChassis.odom_x_flip(); EzChassis.odom_theta_flip(); soloAwp(); }

void neg6(bool doAllianceStake = true) {

}

void neg6red() {
  neg6();
}

void neg6redNoAlly() {
  neg6(false);
}

void neg6blue() { EzChassis.odom_x_flip(); EzChassis.odom_theta_flip(); neg6(); }

void neg6blueNoAlly() { EzChassis.odom_x_flip(); EzChassis.odom_theta_flip(); neg6(false); }

void posAwpRed() {
  EzChassis.drive_angle_set(28.5);

  EzChassis.pid_drive_set(-30, 45);
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(150);
  EzChassis.pid_turn_set(-90, TURN_SPEED);
  EzChassis.pid_wait();
  motor_intake.move_voltage(12000);

  EzChassis.pid_drive_set(28, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(-25, TURN_SPEED);
  EzChassis.pid_wait();

  doinkerLeftState = true;
  EzChassis.pid_drive_set(33, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(35, TURN_SPEED);
  EzChassis.pid_wait_until(25);
  doinkerLeftState = false;
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(-25, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(10, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-46, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait();

  clampState = false;

  EzChassis.pid_drive_set(6, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait();
}

void posAwpBlue() {
  EzChassis.drive_angle_set(-28.5);

  EzChassis.pid_drive_set(-30, 45);
  EzChassis.pid_wait_until(-20);
  EzChassis.pid_speed_max_set(30);
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(150);
  EzChassis.pid_turn_set(90, TURN_SPEED);
  EzChassis.pid_wait();
  motor_intake.move_voltage(12000);

  EzChassis.pid_drive_set(28, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(25, TURN_SPEED);
  EzChassis.pid_wait();

  doinkerRightState = true;
  EzChassis.pid_drive_set(33, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-35, TURN_SPEED);
  EzChassis.pid_wait_until(-25);
  doinkerRightState = false;
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(25, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(10, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-46, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait();

  clampState = false;

  EzChassis.pid_drive_set(6, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(-0, TURN_SPEED);
  EzChassis.pid_wait();
}

void pos3red() {
EzChassis.drive_angle_set(28.5);
EzChassis.pid_drive_set(6, DRIVE_SPEED);
EzChassis.pid_wait();
armPid.target_set(ARM_ALLIANCE);
pros::delay(1000);

EzChassis.pid_drive_set(-30, DRIVE_SPEED);
EzChassis.pid_wait_until(-12);
armPid.target_set(ARM_DOWN);
EzChassis.pid_wait();
clampState = true;
pros::delay(150);
EzChassis.pid_turn_set(142, TURN_SPEED);
EzChassis.pid_wait();
motor_intake.move_voltage(12000);

EzChassis.pid_drive_set(21.5, DRIVE_SPEED);
EzChassis.pid_wait();
doinkerRightState = true;
pros::delay(100);
EzChassis.pid_swing_set(ez::LEFT_SWING, 165, TURN_SPEED);
EzChassis.pid_wait();
doinkerLeftState = true;
pros::delay(100);
EzChassis.pid_swing_set(ez::LEFT_SWING, 135, SWING_SPEED);
EzChassis.pid_wait();
EzChassis.pid_drive_set(-41, 75);
EzChassis.pid_wait();
doinkerRightState = false;
doinkerLeftState = false;
pros::delay(100);
EzChassis.pid_turn_set(115, TURN_SPEED);
EzChassis.pid_wait();

EzChassis.pid_drive_set(12, DRIVE_SPEED);
EzChassis.pid_wait();
EzChassis.pid_turn_set(200, TURN_SPEED);
EzChassis.pid_wait();
EzChassis.pid_drive_set(12, DRIVE_SPEED);
EzChassis.pid_wait();
EzChassis.pid_turn_set(270, TURN_SPEED);  
EzChassis.pid_wait();
EzChassis.pid_drive_set(16, DRIVE_SPEED);
EzChassis.pid_wait();
pros::delay(150);
EzChassis.pid_turn_set(90, TURN_SPEED);
EzChassis.pid_wait();
EzChassis.pid_drive_set(28, DRIVE_SPEED);
armPid.target_set(17000);
EzChassis.pid_wait();
pros::delay(2000);
}

void pos3blue() {
  EzChassis.drive_angle_set(-28.5);
  EzChassis.pid_drive_set(6, DRIVE_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(1000);
  
  EzChassis.pid_drive_set(-30, DRIVE_SPEED);
  EzChassis.pid_wait_until(-12);
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(100);
  EzChassis.pid_turn_set(-142, TURN_SPEED);
  EzChassis.pid_wait();
  motor_intake.move_voltage(12000);
  
  EzChassis.pid_drive_set(21.5, DRIVE_SPEED);
  EzChassis.pid_wait();
  doinkerRightState = true;
  pros::delay(100);
  EzChassis.pid_swing_set(ez::RIGHT_SWING, -165, TURN_SPEED);
  EzChassis.pid_wait();
  doinkerLeftState = true;
  pros::delay(100);
  EzChassis.pid_swing_set(ez::RIGHT_SWING, -135, SWING_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-41, 75);
  EzChassis.pid_wait();
  doinkerRightState = false;
  doinkerLeftState = false;
  pros::delay(100);
  EzChassis.pid_turn_set(-115, TURN_SPEED);
  EzChassis.pid_wait();
  
  EzChassis.pid_drive_set(12, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-200, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(12, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-270, TURN_SPEED);  
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(16, DRIVE_SPEED);
  EzChassis.pid_wait();
  pros::delay(150);
  EzChassis.pid_turn_set(-90, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(28, DRIVE_SPEED);
  armPid.target_set(17500);
  EzChassis.pid_wait();
  pros::delay(2000);
  }

void pos4(bool doAllianceStake) {
  EzChassis.drive_angle_set(28.5);
  EzChassis.pid_drive_set(6, DRIVE_SPEED);
  EzChassis.pid_wait();
  if (doAllianceStake) {
    armPid.target_set(ARM_ALLIANCE);
    pros::delay(1000);
    //pros::delay(2000);
  }
  EzChassis.pid_drive_set(-30, DRIVE_SPEED);
  EzChassis.pid_wait_until(-12);
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(150);
  EzChassis.pid_turn_set(140, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(20.5, DRIVE_SPEED);
  EzChassis.pid_wait();
  doinkerRightState = true;
  EzChassis.pid_swing_set(ez::LEFT_SWING, 170, TURN_SPEED);
  EzChassis.pid_wait();
  doinkerLeftState = true;
  pros::delay(100);
  EzChassis.pid_swing_set(ez::LEFT_SWING, 135, SWING_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-40, DRIVE_SPEED);
  EzChassis.pid_wait();
  doinkerRightState = false;
  doinkerLeftState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(115, TURN_SPEED);
  EzChassis.pid_wait();
  motor_intake.move_voltage(12000);
  EzChassis.pid_drive_set(12, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(200, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(12, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(270, TURN_SPEED);  
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(330, TURN_SPEED);
  EzChassis.pid_wait();
  doinkerLeftState = true;
  EzChassis.pid_drive_set(34, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(380, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(330, TURN_SPEED);
  doinkerLeftState = false;
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(6, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-20,DRIVE_SPEED);
}

void pos4red() { pos4(true); }
void pos4blue() { EzChassis.odom_x_flip(); EzChassis.odom_theta_flip(); pos4(true); }

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  EzChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_drive_set(-12_in, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_drive_set(-12_in, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  EzChassis.pid_turn_set(90_deg, TURN_SPEED, true);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(45_deg, TURN_SPEED, true);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(0_deg, TURN_SPEED, true);
  EzChassis.pid_wait_quick_chain();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  EzChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(-45_deg, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  EzChassis.pid_drive_set(24_in, 30, true);
  EzChassis.pid_wait_until(6_in);
  EzChassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(-45_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzChassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  EzChassis.pid_drive_set(-24_in, 30, true);
  EzChassis.pid_wait_until(-6_in);
  EzChassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  EzChassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  EzChassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  EzChassis.pid_wait();

  EzChassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  EzChassis.pid_wait();

  EzChassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  EzChassis.pid_wait();

  EzChassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  EzChassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  EzChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(-45_deg, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzChassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  EzChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  EzChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    EzChassis.pid_drive_set(-12_in, 127);
    EzChassis.pid_wait();

    // If failsafed...
    if (EzChassis.interfered) {
      EzChassis.drive_sensor_reset();
      EzChassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  EzChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();

  if (EzChassis.interfered) {
    tug(3);
    return;
  }

  EzChassis.pid_turn_set(90_deg, TURN_SPEED);
  EzChassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  EzChassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();

  EzChassis.pid_odom_set(-12_in, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_odom_set(-12_in, DRIVE_SPEED);
  EzChassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  EzChassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  EzChassis.pid_wait();

  // Drive to 0, 0 backwards
  EzChassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  EzChassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  EzChassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  EzChassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  EzChassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  EzChassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  EzChassis.pid_wait();

  EzChassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  EzChassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  EzChassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  EzChassis.pid_wait();

  EzChassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  EzChassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (EzChassis.odom_tracker_left != nullptr) EzChassis.odom_tracker_left->reset();
  if (EzChassis.odom_tracker_right != nullptr) EzChassis.odom_tracker_right->reset();
  if (EzChassis.odom_tracker_back != nullptr) EzChassis.odom_tracker_back->reset();
  if (EzChassis.odom_tracker_front != nullptr) EzChassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    EzChassis.pid_targets_reset();
    EzChassis.drive_imu_reset();
    EzChassis.drive_sensor_reset();
    EzChassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
    EzChassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = EzChassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    EzChassis.pid_turn_set(target, 63, ez::raw);
    EzChassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(EzChassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = EzChassis.odom_tracker_left != nullptr ? EzChassis.odom_tracker_left->get() : 0.0;
    double r_delta = EzChassis.odom_tracker_right != nullptr ? EzChassis.odom_tracker_right->get() : 0.0;
    double b_delta = EzChassis.odom_tracker_back != nullptr ? EzChassis.odom_tracker_back->get() : 0.0;
    double f_delta = EzChassis.odom_tracker_front != nullptr ? EzChassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (EzChassis.odom_tracker_left != nullptr) EzChassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (EzChassis.odom_tracker_right != nullptr) EzChassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (EzChassis.odom_tracker_back != nullptr) EzChassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (EzChassis.odom_tracker_front != nullptr) EzChassis.odom_tracker_front->distance_to_center_set(f_offset);
}

void skills() {
  isRed = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(133);
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  intake_vltg = 12000;  // Start intake motor
  EzChassis.pid_drive_set(-19, DRIVE_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_DOWN);
  clampState = true;
  pros::delay(200);
  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(16, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-23, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(56, DRIVE_SPEED, true);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-18, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-22, DRIVE_SPEED, true);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-90, TURN_SPEED);
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(18.75, 80);
  EzChassis.pid_wait();
  pros::delay(1000);
  EzChassis.drive_set(60, 60);
  intake_vltg = 0;
  armPid.target_set(16000);
  pros::delay(600);
  EzChassis.drive_set(0, 0);

  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait();
  intake_vltg = 12000;
  EzChassis.pid_drive_set(58, DRIVE_SPEED, true);
  EzChassis.pid_wait_until(30);
  EzChassis.pid_speed_max_set(45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-24, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(210, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(18, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-6, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(25, 60);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait();
  clampState = false;
  pros::delay(250);

  EzChassis.pid_drive_set(3, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(272, TURN_SPEED, true);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-80, DRIVE_SPEED, true);
  EzChassis.pid_wait_until(-50);
  EzChassis.pid_speed_max_set(45);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(250);

  EzChassis.pid_turn_set(2, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(28 , TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(50, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(15, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-21, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(90, TURN_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_drive_set(18.75, DRIVE_SPEED);
  EzChassis.pid_wait();
  pros::delay(1000);
  EzChassis.drive_set(60, 60);
  intake_vltg = -1;
  armPid.target_set(16000);
  pros::delay(600);
  EzChassis.drive_set(0, 0);
  
  EzChassis.pid_drive_set(-13, DRIVE_SPEED);
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait();
  intake_vltg = 12000;
  EzChassis.pid_drive_set(54, DRIVE_SPEED, true);
  EzChassis.pid_wait_until(30);
  EzChassis.pid_speed_max_set(45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-22, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(150, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(18, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-26, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-6, DRIVE_SPEED);
  intake_vltg = 0;
  EzChassis.pid_wait_until(-3);
  EzChassis.pid_wait();
  clampState = false;
  pros::delay(150);
  EzChassis.pid_drive_set(26, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait_quick();
  intake_vltg = 12000;
  EzChassis.pid_drive_set(72, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(90, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-44, DRIVE_SPEED);
  EzChassis.pid_wait_until(-20);
  EzChassis.pid_speed_max_set(40);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(250);

  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.drive_set(60, 60);
  pros::delay(750);
  EzChassis.drive_set(0, 0);
  EzChassis.pid_drive_set(-8.25, DRIVE_SPEED, false, false);
  EzChassis.pid_wait();
  intake_vltg = 0;
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);

  EzChassis.pid_drive_set(-8, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(235, TURN_SPEED);
  EzChassis.pid_wait_quick();
  intake_vltg = 12000;
  EzChassis.pid_drive_set(52, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(60, DRIVE_SPEED);
  EzChassis.pid_wait_until(30);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(120, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  EzChassis.pid_wait();
  clampState = false;
  pros::delay(150);

  

  //no allaince stake
  // EzChassis.pid_turn_set(225, TURN_SPEED);
  // EzChassis.pid_wait();
  // intake_vltg = 12000;
  // EzChassis.pid_drive_set(28, DRIVE_SPEED);
  // EzChassis.pid_wait_quick_chain();

  // // start middle ladder ring, comment out if it takes too much time
  // EzChassis.pid_turn_set(135, TURN_SPEED);
  // EzChassis.pid_wait_quick();
  // intake_vltg = 0;
  // EzChassis.pid_drive_set(30, DRIVE_SPEED, true);
  // EzChassis.pid_wait_until(24);
  // startColorUntil(1);
  // EzChassis.pid_wait_quick_chain();
  // EzChassis.pid_drive_set(-30, DRIVE_SPEED, true);
  // EzChassis.pid_wait_quick_chain();
  // stopColorUntilFunction();
  // // end middle ladder ring

  // EzChassis.pid_turn_set(315, TURN_SPEED);
  // EzChassis.pid_wait_quick();
  // EzChassis.pid_drive_set(26, DRIVE_SPEED);
  // intake_vltg = 12000;
  // EzChassis.pid_wait_quick_chain();
  // EzChassis.pid_swing_set(ez::RIGHT_SWING, 270, SWING_SPEED);
  // EzChassis.pid_wait();
  // EzChassis.pid_drive_set(-24, DRIVE_SPEED);
  // EzChassis.pid_wait_quick_chain();
  // EzChassis.pid_turn_set(0, TURN_SPEED);
  // EzChassis.pid_wait_quick();
  // EzChassis.pid_drive_set(12, DRIVE_SPEED);
  // EzChassis.pid_wait_quick_chain();

  // EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  // EzChassis.pid_wait_quick_chain();
  // EzChassis.pid_turn_set(285, TURN_SPEED);
  // EzChassis.pid_wait_quick();
  // EzChassis.pid_drive_set(12, DRIVE_SPEED);
  // EzChassis.pid_wait();
}