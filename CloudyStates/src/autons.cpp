#include "main.h"

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

void skills() {

}


///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  EzChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(-12_in, DRIVE_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(-12_in, DRIVE_SPEED);
  EzChassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  EzChassis.pid_turn_set(90_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzChassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  EzChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(-45_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzChassis.pid_wait();

  EzChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EzChassis.pid_wait();
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
    EzChassis.drive_brake_set(MOTOR_BRAKE_HOLD);
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