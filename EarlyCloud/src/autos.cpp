#include "autos.hpp"
#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/util.hpp"
#include "controls.hpp"
#include "devices.hpp"
#include "lemlib/asset.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/rtos.hpp"

ASSET(X)

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

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

void funExitConditions() {

}

void noAuto() {
    
}

void qualLeft() {
    LemLibChassis.setPose(-55, 35, 270);
    LemLibChassis.moveToPose(-34, 30, 300, 99999, {false} );
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, 45, 99999);
    intakeVoltage(12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-7.5, 50, 99999);
    doinkerActivate();
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-7.5, 42.5, 99999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-8, 20, 99999);
    intakeVoltage(-3000);
    armVoltage(3000);
    LemLibChassis.waitUntilDone();
}

void qualRight() {
    LemLibChassis.setPose(-55, -15, 270);
    LemLibChassis.moveToPose(-34, -20, 300, 9999, {false});
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, -47, 99999);
    intakeVoltage(12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-8, -20, 99999);
    intakeVoltage(-3000);
    LemLibChassis.waitUntilDone();
}

void soloAWPLeft() {
    LemLibChassis.setPose(-55, 35, 270);
    LemLibChassis.moveToPose(-34, 30, 300, 99999, {false} );
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, 45, 99999);
    intakeVoltage(12000);
    LemLibChassis.waitUntilDone();
    pros::delay(500);
    LemLibChassis.moveToPose(-47.5, 3, 180, 99999);
    intakeVoltage(-6000);
    LemLibChassis.waitUntilDone();
    intakeVoltage(12000);
    LemLibChassis.moveToPoint(-47.5, 0, 99999);
    LemLibChassis.waitUntilDone();
    wallStakeLoad();
    LemLibChassis.moveToPoint(-58,  18, 99999, {false});
    LemLibChassis.waitUntilDone();
    // armtowallstake
    LemLibChassis.moveToPose(-58, 0, 180, 99999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.turnToPoint(-70, 0, 99999);
    LemLibChassis.waitUntilDone();
    //armdown
    LemLibChassis.moveToPoint(-35, 0, 9999);
}

void soloAWPRight() {
    LemLibChassis.setPose(-58,-10,270);
    LemLibChassis.moveToPose(-34, -20, 104, 9999, {false});
    clampActivate();
    LemLibChassis.moveToPose(-43, -7, 300, 9999, {}, false);
    intakeVoltage(12000);
    pros::delay(500);
    intakeVoltage(-12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPose(-27, -40, 155, 9999, {}, false);
    pros::delay(750);
    intakeVoltage(12000);
    LemLibChassis.waitUntilDone();
    pros::delay(250);
    LemLibChassis.moveToPose(-9, -28, 60, 9999);
    armVoltage(12000);
    pros::delay(2000);
    armVoltage(0); 

}

void elimsLeft() {

}

void elimsRight() {

}

void mogoRush() {
    LemLibChassis.setPose(-58, -35, 270);
    LemLibChassis.moveToPose(-9, -40, 300, 99999, {false});
    LemLibChassis.waitUntilDone();
    clampActivate();
    intakeVoltage(12000);
    LemLibChassis.moveToPoint(-12.5, -35, 99999);
    LemLibChassis.waitUntilDone();
    clampRetract();
    EzTempChassis.pid_turn_set(180,TURN_SPEED,false);
    EzTempChassis.pid_wait();
    LemLibChassis.moveToPose(-12.5, 30, 120, 9999, {false});
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, 47, 99999);
    intakeVoltage(120000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-20, -5, 500);
    armVoltage(3000);


}

void Skills() {

}


//TUNING PID AUTOS


void tuneLateralLemLib() {
    LemLibChassis.setPose(0,0,0);
    LemLibChassis.moveToPoint(0, 48, 99999);
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
    LemLibChassis.moveToPoint(0, 0, 9999, {false});
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
}

void tuneAngularLemLib() {
    LemLibChassis.setPose(0,0,0);
    LemLibChassis.turnToHeading(90, 99999999);
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
    LemLibChassis.turnToHeading(0, 99999);
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  EzTempChassis.pid_turn_set(90_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(-45_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  EzTempChassis.pid_drive_set(24_in, 30, true);
  EzTempChassis.pid_wait_until(6_in);
  EzTempChassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(-45_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  EzTempChassis.pid_drive_set(-24_in, 30, true);
  EzTempChassis.pid_wait_until(-6_in);
  EzTempChassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  EzTempChassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  EzTempChassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  EzTempChassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzTempChassis.pid_wait_quick_chain();

  EzTempChassis.pid_turn_set(-45_deg, TURN_SPEED);
  EzTempChassis.pid_wait_quick_chain();

  EzTempChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  EzTempChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(45_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_turn_set(0_deg, TURN_SPEED);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    EzTempChassis.pid_drive_set(-12_in, 127);
    EzTempChassis.pid_wait();

    // If failsafed...
    if (EzTempChassis.interfered) {
      EzTempChassis.drive_sensor_reset();
      EzTempChassis.pid_drive_set(-2_in, 20);
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
  EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  EzTempChassis.pid_wait();

  if (EzTempChassis.interfered) {
    tug(3);
    return;
  }

  EzTempChassis.pid_turn_set(90_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .