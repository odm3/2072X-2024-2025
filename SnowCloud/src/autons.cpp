#include "EZ-Template/drive/drive.hpp"
#include "constants.hpp"
#include "controls.hpp"
#include "main.h"
#include "pros/rtos.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  EZ_CHASSIS.pid_drive_set(24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();
  pros::delay(500);

  EZ_CHASSIS.pid_drive_set(-12_in, DRIVE_SPEED);
  EZ_CHASSIS.pid_wait();
  pros::delay(500);

  EZ_CHASSIS.pid_drive_set(-12_in, DRIVE_SPEED);
  EZ_CHASSIS.pid_wait();
  pros::delay(500);
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  EZ_CHASSIS.pid_turn_set(90_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(0_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  EZ_CHASSIS.pid_drive_set(24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(-45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(0_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  EZ_CHASSIS.pid_drive_set(24_in, 30, true);
  EZ_CHASSIS.pid_wait_until(6_in);
  EZ_CHASSIS.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(-45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(0_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  EZ_CHASSIS.pid_drive_set(-24_in, 30, true);
  EZ_CHASSIS.pid_wait_until(-6_in);
  EZ_CHASSIS.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  EZ_CHASSIS.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  EZ_CHASSIS.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  EZ_CHASSIS.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  EZ_CHASSIS.pid_drive_set(24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait_quick_chain();

  EZ_CHASSIS.pid_turn_set(-45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait_quick_chain();

  EZ_CHASSIS.pid_turn_set(0_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  // Your final motion should still be a normal pid_wait
  EZ_CHASSIS.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  EZ_CHASSIS.pid_drive_set(24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(45_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(0_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    EZ_CHASSIS.pid_drive_set(-12_in, 127);
    EZ_CHASSIS.pid_wait();

    // If failsafed...
    if (EZ_CHASSIS.interfered) {
      EZ_CHASSIS.drive_sensor_reset();
      EZ_CHASSIS.pid_drive_set(-2_in, 20);
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
  EZ_CHASSIS.pid_drive_set(24_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  if (EZ_CHASSIS.interfered) {
    tug(3);
    return;
  }

  EZ_CHASSIS.pid_turn_set(90_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .

void redNeg2() {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(275_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(26_in, TURN_SPEED);
  EZ_CHASSIS.pid_wait();
}

void redNeg3() {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(310_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  pros::delay(250);

  EZ_CHASSIS.pid_drive_set(32_in, DRIVE_SPEED, true);
  activateLift();
  EZ_CHASSIS.pid_wait();

  deactivateLift();
  pros::delay(500);
  EZ_CHASSIS.pid_turn_set(195_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(10.5_in,DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

}

void redNeg4() {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(170_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(8_in, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(140_deg, 127);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(8_in, DRIVE_SPEED,true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(270_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(18_in, DRIVE_SPEED);
  EZ_CHASSIS.pid_wait();
}

void redNeg5()  {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(170_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(8_in, DRIVE_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(133_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(9.65_in, 127);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-28_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateLift();
  EZ_CHASSIS.pid_turn_set(310_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();


  EZ_CHASSIS.pid_drive_set(22_in, DRIVE_SPEED, true);
  activateLift();
  EZ_CHASSIS.pid_wait();

  deactivateLift();
  EZ_CHASSIS.pid_drive_set(-5_in, DRIVE_SPEED, true);
  pros::delay(5000);


}

void SoloAwpRedPos() {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(-80_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(240_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(40_in, DRIVE_SPEED, true);
  activateLift();
  EZ_CHASSIS.pid_wait();

  deactivateLift();
  armPID.target_set(ARM_PRIME);
  pros::delay(500);
  EZ_CHASSIS.pid_turn_set(7.5_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(9.25_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();
  pros::delay(500);
  moveIntake(0);

  armPID.target_set(ALLIANCE_SCORE);
  pros::delay(1000);

  EZ_CHASSIS.pid_drive_set(-16_in, TURN_SPEED);
  EZ_CHASSIS.pid_wait();
  deactivateClamp();
  EZ_CHASSIS.pid_drive_set(-4_in, TURN_SPEED);

}

void elims()  {
    EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(-50_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(40_in, DRIVE_SPEED, true);
  activateLift();
  EZ_CHASSIS.pid_wait();

  deactivateLift();
  armPID.target_set(ARM_PRIME);
  pros::delay(500);
  EZ_CHASSIS.pid_turn_set(6_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(6_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();
  pros::delay(500);
  moveIntake(0);

  armPID.target_set(ALLIANCE_SCORE);
  pros::delay(1000);

  EZ_CHASSIS.pid_drive_set(-16_in, TURN_SPEED);
  EZ_CHASSIS.pid_wait();
}

void blueNeg3() {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(70_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(310_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  pros::delay(250);

  EZ_CHASSIS.pid_drive_set(32_in, DRIVE_SPEED, true);
  activateLift();
  EZ_CHASSIS.pid_wait();

  deactivateLift();
  pros::delay(500);
  EZ_CHASSIS.pid_turn_set(195_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(10.5_in,DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

}

void blueNeg4() {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(170_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(8_in, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(140_deg - 180_deg, 127);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(8_in, DRIVE_SPEED,true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(270_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(18_in, DRIVE_SPEED);
  EZ_CHASSIS.pid_wait();
}

void blueNeg5()  {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(170_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(8_in, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(135_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(8_in, DRIVE_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-28_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateLift();
  EZ_CHASSIS.pid_turn_set(300_deg - 180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();
}

void goalRush()  
{
    EZ_CHASSIS.pid_drive_set(-40_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_turn_set(-45_deg, TURN_SPEED, true);
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_drive_set(-8_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    activateClamp();
    EZ_CHASSIS.pid_turn_set(6_deg, TURN_SPEED, true);
    EZ_CHASSIS.pid_wait();
    moveIntake(12000);
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_drive_set(8_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    moveIntake(0);
    EZ_CHASSIS.pid_wait();
    deactivateClamp();
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_drive_set(14_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_turn_set(-52_deg, TURN_SPEED, true);
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_drive_set(-15_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    activateClamp();
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_turn_set(56_deg, TURN_SPEED, true);
    EZ_CHASSIS.pid_wait();
    moveIntake(12000);
    EZ_CHASSIS.pid_wait();
    activateLift();
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_drive_set(20_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    deactivateLift();
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_drive_set(4_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_turn_set(-160_deg, TURN_SPEED, true);
    EZ_CHASSIS.pid_wait();
    EZ_CHASSIS.pid_drive_set(18_in, DRIVE_SPEED);
    EZ_CHASSIS.pid_wait();
    deactivateClamp();
    EZ_CHASSIS.pid_wait();
    
   
}


void skills() {

  armPID.target_set(ARM_PRIME);
  pros::delay(500);
  moveIntake(12000);
  pros::delay(500);
  moveIntake(0);
  armPID.target_set(ALLIANCE_SCORE);
  pros::delay(1000);

  EZ_CHASSIS.pid_drive_set(-16_in, DRIVE_SPEED, false);
  EZ_CHASSIS.pid_wait();

  armPID.target_set(ARM_DOWN);

  EZ_CHASSIS.pid_turn_set(110_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-52_in, 127, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(50_in, 127, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(-110_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(-52_in, 127, true);
  EZ_CHASSIS.pid_wait();

  pros::delay(1000);

}

void SoloAwpRedNeg()  {
  EZ_CHASSIS.pid_drive_set(-30_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  activateClamp();

  EZ_CHASSIS.pid_turn_set(80_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  moveIntake(12000);
  EZ_CHASSIS.pid_drive_set(16_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(-50_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(40_in, DRIVE_SPEED, true);
  activateLift();
  EZ_CHASSIS.pid_wait();

  deactivateLift();
  armPID.target_set(ARM_PRIME);
  pros::delay(500);
  EZ_CHASSIS.pid_turn_set(10_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_drive_set(7_in, DRIVE_SPEED, true);
  EZ_CHASSIS.pid_wait();
  pros::delay(500);
  moveIntake(0);

  armPID.target_set(ALLIANCE_SCORE);
  pros::delay(1000);

  EZ_CHASSIS.pid_drive_set(-16_in, TURN_SPEED);
  EZ_CHASSIS.pid_wait();

  EZ_CHASSIS.pid_turn_set(180_deg, TURN_SPEED);
  EZ_CHASSIS.pid_wait();
  EZ_CHASSIS.pid_drive_set(2_in, TURN_SPEED);
}