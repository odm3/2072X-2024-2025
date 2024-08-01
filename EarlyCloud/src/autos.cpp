#include "autos.hpp"
#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/util.hpp"
#include "controls.hpp"
#include "devices.hpp"
#include "lemlib/asset.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/device.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

// a universal speed for the EzTempChassis to follow. These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

//nothing happens during auto, last ditch effort if no autos work
//(0 stakes, 0 rings, no lader, 0pts.)
void noAuto() {
}

//auto used if no others work and the alliance can get other awp criteria
//(0 stakes, 0 rings, touches ladder, 0pts.)
void driveToLadder() {
  EzTempChassis.pid_drive_set(-48_in, DRIVE_SPEED);
}

void EzQualsLeft() {
  EzTempChassis.pid_drive_set(-9_in, DRIVE_SPEED, false, true);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_turn_set(30_deg, TURN_SPEED, false);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(-4_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  clampActivate();
  pros::delay(250);
  EzTempChassis.pid_turn_set(95_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  intakeVoltage1(12000);
  EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED, false, true);
  EzTempChassis.pid_wait();
  EzTempChassis.drive_set(0, 0);
  pros::delay(3000);
  intakeVoltage1(-12000);
  EzTempChassis.pid_turn_set(-90_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(20_in, 80, false, true);
  EzTempChassis.pid_wait();
}

void EzQualsRight() {
    EzTempChassis.pid_drive_set(-9_in, DRIVE_SPEED, false, true);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_turn_set(-30_deg, TURN_SPEED, false);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(-4_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  clampActivate();
  pros::delay(250);
  EzTempChassis.pid_turn_set(-95_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  intakeVoltage1(12000);
  EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED, false, true);
  EzTempChassis.pid_wait();
  EzTempChassis.drive_set(0, 0);
  pros::delay(3000);
  intakeVoltage1(-12000);
  EzTempChassis.pid_turn_set(90_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(20_in, 80, false, true);
  EzTempChassis.pid_wait();
}

//default auto for qualification matches on the left side, but using strictly EzTempChassis
// (1 stake, 2 rings, ladder touch, 4pts.)
void EzAWPLeft() {
  EzTempChassis.pid_drive_set(-9_in, DRIVE_SPEED, false);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_turn_set(30_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(-4_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  clampActivate();
  pros::delay(250);                                       //clamps the goal

  EzTempChassis.pid_turn_set(105_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  intakeVoltage1(12000);
  EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.drive_set(0, 0);
  pros::delay(3000);                                     //knocks down 2 stack, scores preload and botttom ring

  // intakeVoltage1(-12000);
  EzTempChassis.pid_turn_set(-65_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(16_in, DRIVE_SPEED);
  intakeLiftUp();
  // intakeVoltage1(12000);
  ringStopperActivate();
  EzTempChassis.pid_wait();
  controlla.rumble(".");
  EzTempChassis.pid_drive_set(5_in, 20);
  EzTempChassis.pid_wait();
  intakeLiftDown();
  pros::delay(500);
  EzTempChassis.pid_drive_set(-6_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  pros::delay(1500);
  EzTempChassis.pid_turn_set(-32_deg, TURN_SPEED);
  // intakeVoltage1(-12000);
  pros::delay(500);
  arm.move_relative(100.0, 127);
  EzTempChassis.pid_wait();                                       //turns, reverses intake for stuck ring, intakes the top ring in the middle

  EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  arm.move_relative(-90, 127); 
  pros::delay(500);                                           
  EzTempChassis.pid_drive_set(-10_in, DRIVE_SPEED);                                             //scores ring on alliance stake
}

//auto which can score all criteria for AWP by itself on the right side using only EzTempChassis (2 stakes, 3 rings, touches ladder, 7 pts.)
void EzAWPRight() {
  EzTempChassis.pid_drive_set(-9_in, DRIVE_SPEED, false);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_turn_set(-30_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(-4_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  clampActivate();
  pros::delay(250);                                       //clamps the goal
  EzTempChassis.pid_turn_set(-105_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  intakeVoltage1(12000);
  EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.drive_set(0, 0);
  pros::delay(3000);                                     //knocks down 2 stack, scores preload and botttom ring
  // intakeVoltage1(-12000);
  EzTempChassis.pid_turn_set(65_deg, TURN_SPEED);
  EzTempChassis.pid_wait();
  EzTempChassis.pid_drive_set(16_in, DRIVE_SPEED);
  intakeLiftUp();
  // intakeVoltage1(12000);
  ringStopperActivate();
  EzTempChassis.pid_wait();
  controlla.rumble(".");
  EzTempChassis.pid_drive_set(5_in, 20);
  EzTempChassis.pid_wait();
  intakeLiftDown();
  pros::delay(500);
  EzTempChassis.pid_drive_set(-6_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  pros::delay(1500);
  EzTempChassis.pid_turn_set(32_deg, TURN_SPEED);
  // intakeVoltage1(-12000);
  pros::delay(500);
  arm.move_relative(100.0, 127);
  EzTempChassis.pid_wait();                                       //turns, reverses intake for stuck ring, intakes the top ring in the middle
  EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
  EzTempChassis.pid_wait();
  armVoltage(-3000);
  arm.move_relative(-90, 127); 
  pros::delay(500);                                            //scores ring on alliance stake
  EzTempChassis.pid_drive_set(-10_in, DRIVE_SPEED);
}

//default auto for qualification matches on the left side 
//(1 goal, 2 rings, ladder touch, 4pts.)
void qualLeft() {
    LemLibChassis.setPose(-55, 35, 270);
    LemLibChassis.moveToPose(-34, 30, 300, 99999, {false, 8} );
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, 45, 99999);
    intakeVoltage1(12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-7.5, 50, 99999);
    doinkerActivate();
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-7.5, 42.5, 99999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-8, 20, 99999);
    intakeVoltage1(-3000);
    armVoltage(3000);
    LemLibChassis.waitUntilDone();
}



//default auto for qualifications on the right side
// (1 stake, 2 rings, ladder touch, 4pts.)
void qualRight() {
    LemLibChassis.setPose(-55, -15, 270);
    LemLibChassis.moveToPose(-34, -20, 300, 9999, {false, 8, 0.6});
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, -47, 99999);
    intakeVoltage1(12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-8, -20, 99999);
    intakeVoltage1(-3000);
    LemLibChassis.waitUntilDone();
}

//auto which acheives autonomous win point by itself on the left side 
//(2 stakes, 2 rings, ladder touch, 6pts.)
void soloAWPLeft() {
    LemLibChassis.setPose(-55, 35, 270);
    LemLibChassis.moveToPose(-34, 30, 300, 99999, {false, 8} );
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, 45, 99999);
    intakeVoltage1(12000);
    LemLibChassis.waitUntilDone();
    pros::delay(500);
    LemLibChassis.moveToPose(-47.5, 3, 180, 99999, {true, 8});
    intakeVoltage1(-6000);
    LemLibChassis.waitUntilDone();
    intakeVoltage1(12000);
    LemLibChassis.moveToPoint(-47.5, 0, 99999);
    LemLibChassis.waitUntilDone();
    intakeVoltage1(12000);
    LemLibChassis.moveToPoint(-58,  18, 99999, {false});
    LemLibChassis.waitUntilDone();
    // armtowallstake
    LemLibChassis.moveToPose(-58, 0, 180, 99999, {true, 8});
    LemLibChassis.waitUntilDone();
    LemLibChassis.turnToPoint(-70, 0, 99999);
    LemLibChassis.waitUntilDone();
    //armdown
    LemLibChassis.moveToPoint(-35, 0, 9999);
}

//auto which acheives autonomous win point by itself on the left side 
//(2 stakes, 2 rings, ladder touch, 6pts.)
void soloAWPRight() {
    LemLibChassis.setPose(-58,-10,270);
    LemLibChassis.moveToPose(-34, -20, 104, 9999, {false, 8});
    clampActivate();
    LemLibChassis.moveToPose(-43, -7, 300, 9999, {true, 8}, false);
    intakeVoltage1(12000);
    pros::delay(500);
    intakeVoltage1(-12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPose(-27, -40, 155, 9999, {true, 8}, false);
    pros::delay(750);
    intakeVoltage1(12000);
    LemLibChassis.waitUntilDone();
    pros::delay(250);
    LemLibChassis.moveToPose(-9, -28, 60, 9999, {true, 8});
    armVoltage(12000);
    pros::delay(2000);
    armVoltage(0); 

}

//auto which scores the most points for elims on the left side
void elimsLeft() {

}

//auto which scores the most points for elims on the right side
void elimsRight() {

}

//auto which rushes for the middle mobile goal whilst on the red side 
//(2 stakes, 2 rings, maybe ladder, 6pts)
void mogoRushRed() {
    LemLibChassis.setPose(-58, -35, 270);
    LemLibChassis.moveToPose(-9, -40, 300, 99999, {false, 8});
    LemLibChassis.waitUntilDone();
    clampActivate();
    intakeVoltage1(12000);
    LemLibChassis.moveToPoint(-12.5, -35, 99999);
    LemLibChassis.waitUntilDone();
    clampRetract();
    EzTempChassis.pid_turn_set(180,TURN_SPEED,false);
    EzTempChassis.pid_wait();
    LemLibChassis.moveToPose(-12.5, 30, 120, 9999, {false, 8});
    LemLibChassis.waitUntilDone();
    clampActivate();
    LemLibChassis.moveToPoint(-23.5, 47, 99999);
    intakeVoltage1(120000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-20, -5, 500);
    armVoltage(3000);
}

//auto which rushes for the mobile goal in the middle whilst on the red side and scores on the alliance stake
// (3 stakes, 3 rings, maybe ladder, 9pts.)
void mogoRushRedAllianceStake() {
  
}

//auto whihc rushes for the middle mobile goal whilst on the blue side
// (2 stakes, 2 rings, maybe ladder, 6pts.)
void mogoRushBlue() {

}

//auto which rushes for the middle mobile goal whilst on the blue side and scores on the alliance stake
// (3 stakes, 3 rings, maybe ladder, 9pts)
void mogoRushBlueAllianceStake() {

}

/*MIDDLE RINGS DOES NOT MEAN THE RINGS INSIDE THE LADDER*/

//auto which rushes for the middle rings whilst on the red side of the field 
//(1 stake, 4 rings, maybe ladder, 6 pts.)
void ringRushRed() {

}

//auto which rushes for the middle rings whilst on the red side of the field and scores the alliance stake
// (2 stakes, 4 rings, maybe ladder, 8pts.)
void ringRushRedAllianceStake() {

}

//auto which rushes for the middle rings whilst on the blue side of the field
// (1 stake, 4 rings, maybe ladder, 6pts.)
void ringRushBlue() {

}

//auto which rushes for the middle rings whilst on the blue side of the field nd scores the alliance stake
// (2 stakes, 4 rings, maybe ladder, 8pts)
void ringRushBlueAllianceStake() {

}

//auto that runs for skills
void Skills() {

}


//TUNING PID AUTOS
void tuneLateralLemLib() {
    LemLibChassis.setPose(0,0,0);
    LemLibChassis.moveToPose(0, 24, 0, 99999, {true});
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
    LemLibChassis.moveToPose(0, 0, 0, 99999, {false});
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
}
void tuneAngularLemLib() {
    LemLibChassis.setPose(0,0,0);
    LemLibChassis.turnToHeading(90, 5000);
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
    LemLibChassis.turnToHeading(0, 5000);
    LemLibChassis.waitUntilDone();
    controlla.rumble(".");
}
// Drive Example
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  EzTempChassis.pid_drive_set(-24_in, DRIVE_SPEED, false, true);
  EzTempChassis.pid_wait();

  EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, false, true);
  EzTempChassis.pid_wait();

}
// Turn Example
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
// Combining Turn + Drive
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
// Wait Until and Changing Max Speed
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
// Swing Example
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
// Motion Chaining
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
// Auto that tests everything
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
// Interference example
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