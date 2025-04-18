#include "autons.hpp"
#include <sys/_intsup.h>
#include <cmath>
#include <string>
#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/piston.hpp"
#include "EZ-Template/util.hpp"
#include "constants.hpp"
#include "controls.hpp"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

void nothing() {
  
}

void drive12() {
  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  moveIntake(120000);
  chassis.pid_wait();
  pros::delay(10000);
}

void neg2(bool isRed) {
   isRed ? sign = 1 : sign = -1;
   chassis.pid_drive_set(-28_in, DRIVE_SPEED);
   chassis.pid_wait();
   chassis.pid_turn_set(sign * 90_deg, TURN_SPEED);
   chassis.pid_wait();
   moveIntake(12000);
   chassis.pid_drive_set(20_in, DRIVE_SPEED);
   chassis.pid_wait();
}

void neg2Red() { neg2(true); passRed = true; }
void neg2Blue() { neg2(false); passRed = false; }

void pos2(bool isRed) {
   isRed ? sign =  1: sign = -1;
   chassis.pid_drive_set(-28_in, DRIVE_SPEED);
   chassis.pid_wait();
   chassis.pid_turn_set(sign * -90_deg, TURN_SPEED);
   chassis.pid_wait();
   chassis.pid_drive_set(20_in, DRIVE_SPEED);
   chassis.pid_wait();
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // DONE AND TUNED
void soloAwp(bool isRed) {
  int sign = isRed ? 1 : -1;

  chassis.drive_angle_set(40_deg * sign);

  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);

  if (isRed == false) {
  chassis.pid_swing_set(ez::LEFT_SWING, 120*sign, SWING_SPEED, 60, false);
  } else if (isRed == true) {
  chassis.pid_swing_set(ez::RIGHT_SWING, 120*sign, SWING_SPEED, 60, false);
  }
  chassis.pid_wait();
  armPid.target_set(ARM_DOWN);

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait_until(-5);
  piston_clamp.set(true);
  chassis.pid_wait();

  chassis.pid_turn_set(-140*sign, TURN_SPEED);
  moveIntake(12000);
  chassis.pid_wait();

  chassis.pid_drive_set(17, DRIVE_SPEED);
  chassis.pid_wait();

  if (isRed == false) {
    chassis.pid_swing_set(ez::RIGHT_SWING, 150*sign,SWING_SPEED);
  } else if (isRed == true) {
    chassis.pid_swing_set(ez::LEFT_SWING, 150*sign,SWING_SPEED);
  }
  chassis.pid_wait();

  chassis.pid_drive_set(12, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(33*sign, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(70_in, DRIVE_SPEED);
  chassis.pid_wait_until(18);
  chassis.pid_speed_max_set(45);
  chassis.pid_wait_until(45);
  piston_clamp.set(false);
  chassis.pid_wait_until(62);
  moveIntake(0);
  chassis.pid_wait();

  moveIntake(0);

  chassis.pid_turn_set(100 * sign, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-20, DRIVE_SPEED);
  // chassis.pid_wait_until(-18);
  chassis.pid_drive_set(-12_in, 45);
  chassis.pid_wait();
  piston_clamp.set(true);
  chassis.pid_wait();


  chassis.pid_turn_set(-10.5*sign, TURN_SPEED);
  chassis.pid_wait();

  moveIntake(12000);

  chassis.pid_drive_set(24, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-165*sign, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(36, DRIVE_SPEED);
  armPid.target_set(4000);
  chassis.pid_wait();
}

void soloAwpRed() {
  passRed = true;
  soloAwp(true);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DONE AND TUNED
void soloAwpBlue() {
  passRed = false;
    chassis.drive_angle_set(40_deg * -1);

  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);

  chassis.pid_swing_set(ez::LEFT_SWING, 120*-1, SWING_SPEED, 60, false);


  chassis.pid_wait();
  armPid.target_set(ARM_DOWN);

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait_until(-5);
  piston_clamp.set(true);
  chassis.pid_wait();

  chassis.pid_turn_set(-135*-1, TURN_SPEED);
  moveIntake(12000);
  chassis.pid_wait();

  chassis.pid_drive_set(15, DRIVE_SPEED);
  chassis.pid_wait();


  chassis.pid_swing_set(ez::RIGHT_SWING, 150*-1,SWING_SPEED);

  chassis.pid_wait();

  chassis.pid_drive_set(12, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(33*-1, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(70_in, DRIVE_SPEED);
  chassis.pid_wait_until(30);
  chassis.pid_speed_max_set(45);
  chassis.pid_wait_until(45);
  piston_clamp.set(false);
  chassis.pid_wait_until(65);
  moveIntake(0);
  chassis.pid_wait();

  moveIntake(0);

  chassis.pid_turn_set(101 * -1, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-20, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-16_in, 60);
  chassis.pid_wait_until(14);
  piston_clamp.set(true);
  chassis.pid_wait();

  chassis.pid_turn_set(0*-1, TURN_SPEED);
  chassis.pid_wait();

  moveIntake(12000);

  chassis.pid_drive_set(24, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-170*-1, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(32, DRIVE_SPEED);
  armPid.target_set(4000);
  chassis.pid_wait();
}

void pos5Elims(bool isRed) {

}

void pos5ElimsRed() {
  passRed = true;
  pos5Elims(true);
}

void pos5ElimsBlue() {
  passRed = false;
  pos5Elims(false);
}

void pos2Red() { pos2(true); passRed = true; }
void pos2Blue() {pos2(false); passRed = false; }



// DONE 1 ALLIANCE STAKE 4 GOAL + BAR TOUCH (RING SIDE) //////////////////////////////
void neg5(bool isRed) {
  int sign = isRed ? 1 : -1;

  chassis.drive_angle_set(40_deg * sign);

  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);

  if (isRed == false) {
  chassis.pid_swing_set(ez::LEFT_SWING, 120*sign, SWING_SPEED, 60, false);
  } else if (isRed == true) {
  chassis.pid_swing_set(ez::RIGHT_SWING, 120*sign, SWING_SPEED, 60, false);
  }
  chassis.pid_wait();
  armPid.target_set(ARM_DOWN);

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait_until(-5);
  piston_clamp.set(true);
  chassis.pid_wait();
  piston_doinker_right.set(true);

  chassis.pid_turn_set(-139*sign, TURN_SPEED);
  moveIntake(12000);
  chassis.pid_wait();

  chassis.pid_drive_set(16.5, 127);
  chassis.pid_wait();
  piston_doinker_right.set(false);


  chassis.pid_turn_set(-193*-1, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(10, DRIVE_SPEED);
  chassis.pid_wait();

  if (isRed == false) {
    chassis.pid_swing_set(ez::RIGHT_SWING, 115*sign,SWING_SPEED);
  } else if (isRed == true) {
    chassis.pid_swing_set(ez::LEFT_SWING, 115*sign,SWING_SPEED);
  }
  chassis.pid_wait();

  chassis.pid_drive_set(16, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(30, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(42_in, DRIVE_SPEED);
  chassis.pid_wait_until(18);
  piston_lift.set(true);

  pros::delay(500);
  piston_lift.set(false);
  armPid.target_set(5000);
  pros::delay(200);
  chassis.pid_drive_set(-20, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(23, DRIVE_SPEED);  
}

void neg5Red() {
  passRed = true;
  neg5(true);
}

//DONE AND TUNED////////////////////////////////
void neg5Blue() {
  passRed = false;

  int sign = -1;

  chassis.drive_angle_set(40_deg * sign);

  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);

  chassis.pid_swing_set(ez::LEFT_SWING, 120*sign, SWING_SPEED, 60, false);
  chassis.pid_wait();
  armPid.target_set(ARM_DOWN);

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait_until(-5);
  piston_clamp.set(true);
  chassis.pid_wait();
  piston_doinker_left.set(true);

  chassis.pid_turn_set(-138*sign, TURN_SPEED);
  moveIntake(12000);
  chassis.pid_wait();

  chassis.pid_drive_set(15.8, DRIVE_SPEED);
  chassis.pid_wait();
  piston_doinker_left.set(false);

  chassis.pid_turn_set(-168*-1, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(10, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 115*sign,SWING_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(16, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(-27, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(42.5_in, DRIVE_SPEED);
  chassis.pid_wait_until(18);
  piston_lift.set(true);

  pros::delay(800);
  piston_lift.set(false);
  armPid.target_set(5000);
  pros::delay(200);
  chassis.pid_drive_set(-20, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(23, DRIVE_SPEED);  
}


void ringRush(bool isRed) {
  int sign = isRed ? 1 : -1;

  chassis.drive_angle_set(40_deg * sign);

}

void ringRushRed() {
  passRed = true;
  neg5(true);
}

void ringRushBlue() {
  passRed = false;

  int sign = -1;

  chassis.drive_angle_set(24.8_deg);
  chassis.pid_drive_set(42_in, DRIVE_SPEED);
  chassis.pid_wait_until(6);
  piston_doinker_left.set(true);
  piston_doinker_right.set(true);
  chassis.pid_wait();
  chassis.pid_turn_set(40, TURN_SPEED);
  chassis.pid_wait();
  // chassis.pid_turn_set(28, TURN_SPEED);
  // chassis.pid_wait();

  chassis.pid_drive_set(-28, DRIVE_SPEED);
  chassis.pid_wait();
  piston_doinker_left.set(false);
  piston_doinker_right.set(false);
  chassis.pid_wait();
  chassis.pid_turn_set(165, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-12, 50);
  chassis.pid_wait();
  //piston_clamp.set(true);



  // chassis.pid_wait();
  // piston_doinker_left.set(false);
  // piston_doinker_right.set(false);
  // chassis.pid_wait();
  // chassis.pid_swing_set(ez::RIGHT_SWING, -150*sign,SWING_SPEED);
  // chassis.pid_wait();
  // chassis.pid_swing_set(ez::RIGHT_SWING, -155*sign,SWING_SPEED);


}

void autoSkills() {
  chassis.drive_angle_set(-40_deg);

  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);
  chassis.pid_drive_set(-12, 75);  
  chassis.pid_wait();
  piston_clamp.set(true);
  chassis.pid_wait();
  chassis.pid_turn_set(95, TURN_SPEED);
  armPid.target_set(ARM_DOWN);
  moveIntake(12000);
  chassis.pid_wait();
  chassis.pid_drive_set(24, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(120, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(54, DRIVE_SPEED);
  chassis.pid_wait_until(20);
  armPid.target_set(ARM_PRIME);
  chassis.pid_wait();

  chassis.pid_turn_set(105, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-24, DRIVE_SPEED);
  chassis.pid_wait();

  moveIntake(0);
  armPid.target_set(8000);
  
  chassis.pid_wait();
  chassis.pid_turn_set(180, TURN_SPEED);
  chassis.pid_wait();
  moveIntake(12000);
  chassis.pid_drive_set(17, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_SCORE);

  chassis.pid_wait();
  chassis.pid_drive_set(-11, DRIVE_SPEED);
  chassis.pid_wait();

  armPid.target_set(ARM_DOWN);

  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(56, DRIVE_SPEED);
  chassis.pid_wait_until(30);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_turn_set(-240, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(12, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, -315, SWING_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-4, DRIVE_SPEED);
  chassis.pid_wait();
  piston_clamp.set(false);

  chassis.pid_drive_set(16, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(-180, TURN_SPEED);
  chassis.pid_wait();


}


//////////////////////
void posRed() {
  chassis.drive_angle_set(-40_deg);

  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);

  chassis.pid_swing_set(ez::LEFT_SWING, -120, SWING_SPEED, 60, false);
  chassis.pid_wait();
  armPid.target_set(ARM_DOWN);

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait_until(-5);
  piston_clamp.set(true);
  chassis.pid_wait(); 

  chassis.pid_turn_set(-130.5, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(54, DRIVE_SPEED);
  moveIntake(12000);
  chassis.pid_wait_until(30);
  armPid.target_set(ARM_ALLIANCE);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(-22, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_PRIME);
  chassis.pid_wait();
  chassis.pid_drive_set(19, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(135, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(20, DRIVE_SPEED);
  chassis.pid_wait();

  moveIntake(0);
  armPid.target_set(ARM_SCORE);
  pros::delay(2000);
}

void posBlue() {
  chassis.drive_angle_set(40_deg);

  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);

  chassis.pid_swing_set(ez::RIGHT_SWING, 120, SWING_SPEED, 60, false);
  chassis.pid_wait();
  armPid.target_set(ARM_DOWN);

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait_until(-5);
  piston_clamp.set(true);
  chassis.pid_wait(); 

  chassis.pid_turn_set(135, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(54, DRIVE_SPEED);
  moveIntake(12000);
  chassis.pid_wait_until(30);
  armPid.target_set(ARM_ALLIANCE);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(-19, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_PRIME);
  chassis.pid_wait();
  chassis.pid_drive_set(19, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-135, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(20, DRIVE_SPEED);
  chassis.pid_wait();

  moveIntake(0);
  armPid.target_set(ARM_SCORE);
}

void safePosRed() {
  chassis.drive_angle_set(-40_deg);

  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(800);

  chassis.pid_swing_set(ez::LEFT_SWING, -120, SWING_SPEED, 60, false);
  chassis.pid_wait();
  armPid.target_set(ARM_DOWN);

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait_until(-5);
  piston_clamp.set(true);
  chassis.pid_wait(); 

  chassis.pid_turn_set(-130.5, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(54, DRIVE_SPEED);
  moveIntake(12000);
  chassis.pid_wait_until(30);
  armPid.target_set(ARM_ALLIANCE);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(-22, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();
  armPid.target_set(ARM_PRIME);
  chassis.pid_wait();
  chassis.pid_drive_set(19, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(133, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(23, DRIVE_SPEED);
  chassis.pid_wait();

  moveIntake(0);
  armPid.target_set(ARM_SCORE);
}

void safePosBlue() {
  
}

/*  example progs

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
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
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
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
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

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
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

*/