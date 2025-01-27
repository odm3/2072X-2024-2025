#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/util.hpp"
#include "devices.hpp"
#include "autons.hpp"
#include "drivercontrol.hpp"
#include "pros/rtos.hpp"

// function definitions

//       chassis.setPose(x, y, theta); 
//       chassis.turnTo(x, y, timeout);    
//       chassis.follow(path file, timeout, lookahead distance, isAsynchronous, forwards (false makes the robot run the path backwards));
//       chassis.moveToPose(x, y, theta, timeout, {maxSpeed, minSpeed, earlyExitRange});
//       chassis.moveToPoint(x, y, timeout, {maxSpeed, minSpeed, earlyExitRange, forwards});
//
//       chassis.waitUntil(inches); use this to have your bot wait until the path is finished
//       a really big number means just wait until the path has finished

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;
void safe_exit_conditions() {
  chassis.pid_turn_exit_condition_set(150_ms, 3_deg, 300_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(150_ms, 3_deg, 300_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(150_ms, 1_in, 300_ms, 3_in, 500_ms, 500_ms);
}

void soloAwpSafe(bool isRed) { 
  double sign = isRed ? 1 : -1;

  chassis.drive_angle_set(-50 * sign);

  intakeRaise.set_value(true);
  pros::delay(200);
  intake = 127;

  chassis.pid_drive_set(8, 40, true);
  pros::delay(100);
  chassis.pid_wait();

  pros::delay(200);
  intakeRaise.set_value(false);
  pros::delay(200);


  intake = 0;

  chassis.pid_drive_set(-8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  //turn to go to alliance stake
  chassis.pid_turn_set(-90 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(14, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(0 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-3, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;
  pros::delay(750);
  intake = 0;

  // move forward 
  chassis.pid_drive_set(8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to goal
  chassis.pid_turn_set(-140 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(true);
  chassis.pid_drive_set(-36, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(false);
  pros::delay(300);

  chassis.pid_turn_set(90 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;

  chassis.pid_drive_set(28, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(38, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-38, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(-45 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(12, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();


}

void soloAwpSafeBlue() { soloAwpSafe(false); }

void soloAwpSafeRed() { soloAwpSafe(true); }

void positiveSideBlue() { 
  chassis.drive_angle_set(20);

  intake = 127;

  chassis.pid_drive_set(35, 127, false);
  pros::delay(200);
  doinker.set_value(true);
  chassis.pid_wait_until(31);

  pros::delay(100);
  intake = 0;
  doinker.set_value(false);

  chassis.pid_drive_set(-13, 50, false);
  pros::delay(150);
  chassis.pid_wait_until(-7);
  doinker.set_value(true);
  chassis.pid_wait();


  backClamp.set_value(true);

  chassis.pid_turn_set(-100, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  doinker.set_value(false);


  liftSensor.reset_position();
  liftLeft.move(0);
  liftRight.move(0);

  chassis.pid_drive_set(-28, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(-26);
  backClamp.set_value(false);
  chassis.pid_wait();

  intake = 127;

  chassis.pid_turn_set(-180, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(30, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(28);

  chassis.pid_swing_set(ez::LEFT_SWING, -90, SWING_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  doinker.set_value(true);

  chassis.pid_drive_set(26, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(24);
  pros::delay(1000);

  intake = -127;

  chassis.pid_turn_set(10, 127);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(true);
  doinker.set_value(false);

  chassis.pid_drive_set(28, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(26);

  chassis.pid_turn_set(-160, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();
}

void positiveSideRed() { 
  chassis.drive_angle_set(20);

  liftLeft.move_absolute(200, 200);
  liftRight.move_absolute(200, 200);
  intake = 127;
  doinker.set_value(true);

  chassis.pid_drive_set(35, 127, false);
  pros::delay(200);
  chassis.pid_wait_until(31);

  pros::delay(100);
  doinker.set_value(false);


  chassis.pid_drive_set(-13, 50, false);
  pros::delay(200);
  chassis.pid_wait_until(-7);
    intake = 0;

  doinker.set_value(true);
  chassis.pid_wait();


  chassis.pid_turn_set(40, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  doinker.set_value(false);

  chassis.pid_drive_set(31.5, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait();

  liftLeft.move_absolute(470, 200);
  liftRight.move_absolute(470, 200);

  pros::delay(700);

  chassis.pid_drive_set(-19, DRIVE_SPEED, false);
  pros::delay(300);
  liftLeft.move_absolute(-1000, 200);
  liftRight.move_absolute(-1000, 200);
  chassis.pid_wait();

  backClamp.set_value(true);

  chassis.pid_turn_set(90, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  liftSensor.reset_position();
  liftLeft.move(0);
  liftRight.move(0);

  chassis.pid_drive_set(-24, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(-22);
  backClamp.set_value(false);
  chassis.pid_wait();

  intake = 127;

  chassis.pid_swing_set(ez::LEFT_SWING, 180, 70, 45);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  doinker.set_value(true);
  backClamp.set_value(true);

  chassis.pid_drive_set(11, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(270, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(10, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  doinker.set_value(false);

  chassis.pid_turn_set(175, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-34, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

}


void positiveSideQuals(bool isRed) {
  double sign = isRed ? 1 : -1;

  chassis.drive_angle_set(-51 * sign);

  liftLeft.move_absolute(480, 600);
  liftRight.move_absolute(480, 600);

  pros::delay(600);

  liftLeft.move_absolute(10, 200);
  liftRight.move_absolute(10, 200);

  if (!isRed) {
    chassis.pid_swing_set(ez::RIGHT_SWING,-73 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING,-73 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  }

  backClamp.set_value(true);
  chassis.pid_drive_set(-36, 70, true);
  chassis.pid_wait_until(-34);
  backClamp.set_value(false);
  chassis.pid_wait();
  pros::delay(100);

  chassis.pid_turn_set(45 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  pros::delay(300);
  intake = 0;
  chassis.pid_wait_until(16);


  isRed ? ringRush.set_value(true) : doinker.set_value(true);

  pros::delay(250);

  chassis.pid_turn_set(70 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();
  
  if (!isRed) {
    chassis.pid_drive_set(4, DRIVE_SPEED, false);
    chassis.pid_wait();
  } else {
    chassis.pid_drive_set(2, DRIVE_SPEED, false);
    chassis.pid_wait();
  }

  isRed ? doinker.set_value(true) : ringRush.set_value(true);

  pros::delay(250);

  if (!isRed) {
    chassis.pid_swing_set(ez::RIGHT_SWING,45 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING,45 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  }


  chassis.pid_drive_set(-42, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait_until(-40);

  doinker.set_value(false);
  ringRush.set_value(false);

  pros::delay(250);

  chassis.pid_turn_set(-10 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;

  if (!isRed) {
    chassis.pid_swing_set(ez::RIGHT_SWING,200 * sign, SWING_SPEED, 20);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING,200 * sign, SWING_SPEED, 20);
    pros::delay(100);
    chassis.pid_wait();
  }

  chassis.pid_drive_set(30, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait_until(28);

  chassis.pid_drive_set(-24, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait_until(-22);

  chassis.pid_turn_set(90 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(16, 20, false);
  pros::delay(100);
  chassis.pid_wait_until(14);
}

void positiveSideSimple(bool isRed) {
  double sign = isRed ? 1 : -1;

  chassis.pid_turn_set(-0 * sign, TURN_SPEED);
  backClamp.set_value(true);

  chassis.pid_drive_set(-30, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(-28);
  backClamp.set_value(false);
  chassis.pid_wait();

  chassis.pid_turn_set(90 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;

  chassis.pid_drive_set(28, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-28, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(28, 30, true);
  pros::delay(100);
  chassis.pid_wait();
  intake = 0;
}

void positiveSideSimpleRed() { positiveSideSimple(true); } 

void positiveSideSimpleBlue() { positiveSideSimple(false); }


void positiveSideQualsBlue() { positiveSideQuals(false); }

void positiveSideQualsRed() { positiveSideQuals(true); }

void negativeSideQuals(bool isRed) {
  double sign = isRed ? 1 : -1;

  if (isRed == 1) {
    chassis.pid_turn_set(17.5 * sign, TURN_SPEED);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_turn_set(19.5 * sign, TURN_SPEED);
    pros::delay(100);
    chassis.pid_wait();
  }

  chassis.pid_drive_set(5, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  liftLeft.move_absolute(450, 600);
  liftRight.move_absolute(450, 600);

  if (isRed == 1) {
    pros::delay(650);
  } else {
    pros::delay(600);
  }

  liftLeft.move_absolute(10, 600);
  liftRight.move_absolute(10, 600);

  pros::delay(150);

  if (!isRed) {
    chassis.pid_swing_set(ez::LEFT_SWING,77 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::RIGHT_SWING,77 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  }

  
  backClamp.set_value(true);
  chassis.pid_drive_set(-38, 70, true);
  pros::delay(500);
  liftLeft.move_absolute(10, 600);
  liftRight.move_absolute(10, 600);
  chassis.pid_wait_until(-36);
  backClamp.set_value(false);
  chassis.pid_wait();
  pros::delay(250);

  chassis.pid_turn_set(221 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;

  chassis.pid_drive_set(18.5, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-22.5, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

   chassis.pid_turn_set(180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(28, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-26, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(270 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(24, 20, true);
  pros::delay(1000);
  intake = 0;
  chassis.pid_wait();
}

void negativeSideQualsBlue() { negativeSideQuals(false); }

void negativeSideQualsRed() { negativeSideQuals(true); }

void negativeSide(bool isRed) { 
  double sign = isRed ? -1 : 1;
  chassis.drive_angle_set(-25 * sign);
  backClamp.set_value(true);

  chassis.pid_drive_set(-34, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(-32);
  backClamp.set_value(false);
  chassis.pid_wait();
  pros::delay(250);

  chassis.pid_turn_set(-90 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;
  chassis.pid_drive_set(31, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(-180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(15, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-7, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(-220 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(12, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  

    pros::delay(1000);


  chassis.pid_turn_set(-180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-28, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(-105 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(true);

  chassis.pid_drive_set(-70, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

    backClamp.set_value(false);


  intake = 0;
}

void negativeSideBlue() { negativeSide(false); }

void negativeSideRed() { negativeSide(true); }

void skills() {
  safe_exit_conditions();

  // score on alliance stake
  intake = 127;
  pros::delay(500);
  intake = 0;

  // move forward 
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to goal
  chassis.pid_turn_set(68, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move to goal
  backClamp.set_value(true);
  chassis.pid_drive_set(-24, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(false);
  pros::delay(300);

  //turn to first ring
  chassis.pid_turn_set(0, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  intake = 127;
  chassis.pid_drive_set(21, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to second ring
  chassis.pid_turn_set(-52.5, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(40, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  //move back a bit
  chassis.pid_drive_set(-8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to third ring
  chassis.pid_turn_set(-180, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(50, 60, true);
  pros::delay(100);
  chassis.pid_wait();

  pros::delay(500);

  // turn to fourth ring
  chassis.pid_turn_set(-55, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(11, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  //turn to put goal in corner
  chassis.pid_turn_set(15, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // put goal in corner
  backClamp.set_value(true);
  chassis.pid_drive_set(-12, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(6, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(7, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to far ring
  chassis.pid_drive_set(72, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  intake = 0;

  // turn to blue goal
  chassis.pid_turn_set(-135, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to blue goal
  chassis.pid_drive_set(-32, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  //turn to blue goal
  chassis.pid_turn_set(-180, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // grab blue goal
  chassis.pid_drive_set(-12, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(false);
  pros::delay(300);

  // turn to corner
  chassis.pid_turn_set(-260, TURN_SPEED);
  pros::delay(300);
  chassis.pid_wait();

  // put goal in corner
  backClamp.set_value(true);

  chassis.pid_drive_set(10, DRIVE_SPEED, true);
  pros::delay(100);

  pros::delay(300);
  chassis.pid_drive_set(-42, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to middle goal
  chassis.pid_turn_set(-240, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to middle goal
  chassis.pid_drive_set(39, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to grab mid goal
  chassis.pid_turn_set(-120, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // grab mid goal
  chassis.pid_drive_set(-23, 70, true);
  pros::delay(100);
  chassis.pid_wait();
  
  backClamp.set_value(false);
  pros::delay(300);

  // turn second ring
  chassis.pid_turn_set(-225, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;

  // go to second ring
  chassis.pid_drive_set(35, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to third ring
  chassis.pid_turn_set(90, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to third ring
  chassis.pid_drive_set(36, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to fourth ring
  chassis.pid_turn_set(0, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to fourth ring
  chassis.pid_drive_set(28, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // backup a bit
  chassis.pid_drive_set(-8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to fifth ring
  chassis.pid_turn_set(-45, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to fifth ring
  chassis.pid_drive_set(12, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // BACK UP again
  chassis.pid_drive_set(-12, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to corner
  chassis.pid_turn_set(193, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to corner
  backClamp.set_value(true);
  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();
}

void skillsv2() {
  safe_exit_conditions();

  // score on alliance stake
  intake = 127;
  pros::delay(500);
  intake = 0;

  // move forward 
  chassis.pid_drive_set(14, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to goal
  chassis.pid_turn_set(90, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move to goal
  backClamp.set_value(true);
  chassis.pid_drive_set(-24, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(false);
  pros::delay(200);

  //turn to first ring
  chassis.pid_turn_set(0, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  intake = 127;
  chassis.pid_drive_set(21, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to second ring
  chassis.pid_turn_set(-52.5, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(40, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  //move back a bit
  chassis.pid_drive_set(-10, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to third ring
  chassis.pid_turn_set(-180, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(50, 60, true);
  pros::delay(100);
  chassis.pid_wait();

  pros::delay(500);

  // turn to fourth ring
  chassis.pid_turn_set(-47, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(14, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  // back up for alignment
  chassis.pid_drive_set(-9, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  //turn to put goal in corner
  chassis.pid_turn_set(45, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // put goal in corner
  backClamp.set_value(true);
  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  intake = 0;

  chassis.pid_drive_set(15, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(-90, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to far ring
  chassis.pid_drive_set(-67, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-6, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(false);
  pros::delay(200);

  //turn to first ring
  chassis.pid_turn_set(0, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  intake = 127;
  chassis.pid_drive_set(21, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to second ring
  chassis.pid_turn_set(52.5, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(40, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  //move back a bit
  chassis.pid_drive_set(-8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to third ring
  chassis.pid_turn_set(180, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(50, 60, true);
  pros::delay(100);
  chassis.pid_wait();

  pros::delay(500);

  // turn to fourth ring
  chassis.pid_turn_set(55, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // move forward and intake ring
  chassis.pid_drive_set(12, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  // back up for alignment
  chassis.pid_drive_set(-6, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  //turn to put goal in corner
  chassis.pid_turn_set(-45, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // put goal in corner
  backClamp.set_value(true);
  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  intake.move_velocity(200);

  chassis.pid_drive_set(135, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  intake = 0;

  chassis.pid_turn_set(-135, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-18, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(-90, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-22, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  backClamp.set_value(false);
  pros::delay(200);

  intake = 127;

  chassis.pid_turn_set(135, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(36, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to third ring
  chassis.pid_turn_set(90, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to third ring
  chassis.pid_drive_set(34, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to fourth ring
  chassis.pid_turn_set(0, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to fourth ring
  chassis.pid_drive_set(28, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // backup a bit
  chassis.pid_drive_set(-8, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to fifth ring
  chassis.pid_turn_set(-30, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to fifth ring
  chassis.pid_drive_set(12, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // BACK UP again
  chassis.pid_drive_set(-12, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  // turn to corner
  chassis.pid_turn_set(213, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  // go to corner
  backClamp.set_value(true);
  intake = 0;
  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING,315, SWING_SPEED, 10);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING,274, SWING_SPEED, 51);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(96, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(315, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-48, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(10, 40, true);
  pros::delay(100);
  chassis.pid_wait();

}

void soloAwp(bool isRed) { 
  double sign = isRed ? 1 : -1;

  chassis.drive_angle_set(51 * sign);

  liftLeft.move_absolute(480, 600);
  liftRight.move_absolute(480, 600);

  pros::delay(600);

  liftLeft.move_absolute(10, 200);
  liftRight.move_absolute(10, 200);

  if (!isRed) {
    chassis.pid_swing_set(ez::LEFT_SWING,73 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::RIGHT_SWING,73 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  }

  backClamp.set_value(true);
  chassis.pid_drive_set(-38, 70, true);
  chassis.pid_wait_until(-36);
  backClamp.set_value(false);
  chassis.pid_wait();
  pros::delay(100);

  chassis.pid_turn_set(221 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(219 * sign);

  intake = 127;

  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait_until(22);

  chassis.pid_drive_set(-25, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait_until(-23);

  chassis.pid_turn_set(180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(178 * sign);

  chassis.pid_drive_set(30, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait_until(28);

  chassis.pid_turn_set(26 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(79, DRIVE_SPEED, true);
  pros::delay(600);
  chassis.pid_wait_until(32);
  
  chassis.pid_drive_set(48, 50, true);
  pros::delay(100);
  backClamp.set_value(true);
  chassis.pid_wait_until(45);
  intake = 0;
  chassis.pid_wait_until(46);

  chassis.pid_turn_set(96 * sign, TURN_SPEED);
  pros::delay(50);
  chassis.pid_wait_until(94 * sign);

  chassis.pid_drive_set(-35, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(-31);
  backClamp.set_value(false);
  chassis.pid_wait_until(-33);
  
  chassis.pid_turn_set(0 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(2 * sign);
  intake = 127;

  chassis.pid_drive_set(23, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait_until(20);

   chassis.pid_turn_set(-170 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(-168 * sign);

  chassis.pid_drive_set(42, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();
}

void soloAwpBlue() {
  soloAwp(false);
}

void soloAwpRed() {
  soloAwp(true);
}

void negativeSide9123(bool isRed) { 
  double sign = isRed ? 1 : -1;

  chassis.drive_angle_set(17.5 * sign);

  chassis.pid_drive_set(5, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  liftLeft.move_absolute(450, 200);
  liftRight.move_absolute(450, 200);

  pros::delay(600);
  
  liftLeft.move_relative(-450, -200);
  liftRight.move_relative(-450, -200);

  pros::delay(150);

  if (!isRed) {
    chassis.pid_swing_set(ez::LEFT_SWING,77 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::RIGHT_SWING,77 * sign, -SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  }

  backClamp.set_value(true);
  chassis.pid_drive_set(-38, 70, true);
  pros::delay(500);
  chassis.pid_wait_until(-36);
  backClamp.set_value(false);
  chassis.pid_wait();
  pros::delay(100);

  chassis.pid_turn_set(232 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();
   
  intake = 127;

  if (isRed) {
    chassis.pid_swing_set(ez::RIGHT_SWING,180 * sign, SWING_SPEED, 44);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING,180 * sign, SWING_SPEED, 40);
    pros::delay(100);
    chassis.pid_wait();
  }

  chassis.pid_drive_set(12, 70, true);
  pros::delay(100);
  chassis.pid_wait();

  if (isRed) {
    chassis.pid_swing_set(ez::RIGHT_SWING,270 * sign, SWING_SPEED, 44);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING,270 * sign, SWING_SPEED, 45);
    pros::delay(100);
    chassis.pid_wait();
  }

  chassis.pid_turn_set(180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(180 * sign);

  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-4, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(90 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(90 * sign);

  chassis.pid_drive_set(22, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(135 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(135 * sign);

  chassis.pid_drive_set(49, 60, true);
  pros::delay(100);
  chassis.pid_wait();

  pros::delay(500);


  chassis.pid_drive_set(-5, 30, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(-13, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_turn_set(185 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(185 * sign);


  chassis.pid_drive_set(-180, DRIVE_SPEED, true);
  pros::delay(500);
  backClamp.set_value(true);
  chassis.pid_wait();



}

void negativeSide9123Blue() {
  negativeSide9123(false);
}

void negativeSide9123Red() {
  negativeSide9123(true);
}

void samsPositiveSide(bool isRed) {
  double sign = isRed ? -1 : 1;
  chassis.drive_angle_set(205 * sign);
  backClamp.set_value(true);

  chassis.pid_drive_set(-34, 70, true);
  pros::delay(100);
  chassis.pid_wait_until(-32);
  backClamp.set_value(false);
  chassis.pid_wait();
  pros::delay(250);

  intake = 127;

  chassis.pid_turn_set(45 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  pros::delay(300);
  intake = 0;
  chassis.pid_wait_until(16);

  isRed ? ringRush.set_value(true) : doinker.set_value(true);

  pros::delay(250);

  chassis.pid_turn_set(19 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  if (!isRed) {
    chassis.pid_drive_set(4, DRIVE_SPEED, false);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_drive_set(2, DRIVE_SPEED, false);
    pros::delay(100);
    chassis.pid_wait();
  }

  isRed ? doinker.set_value(true) : ringRush.set_value(true);

  pros::delay(250);

  if (!isRed) {
    chassis.pid_swing_set(ez::RIGHT_SWING, 45 * sign, SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING,45 * sign, SWING_SPEED, 0);
    pros::delay(100);
    chassis.pid_wait();
  }

  chassis.pid_drive_set(-42, DRIVE_SPEED, true);
  pros::delay(100);
  chassis.pid_wait_until(-40);

  doinker.set_value(false);
  ringRush.set_value(false);

  pros::delay(250);

  chassis.pid_turn_set(100 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  intake = 127;

  if (!isRed) {
    chassis.pid_swing_set(ez::RIGHT_SWING, -115 * sign, SWING_SPEED, 20);
    pros::delay(100);
    chassis.pid_wait();
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING,-115 * sign, SWING_SPEED, 20);
    pros::delay(100);
    chassis.pid_wait();
  }

  chassis.pid_drive_set(32, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait_until(30);

  chassis.pid_drive_set(-5, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait_until(-2);

  chassis.pid_turn_set(-156.5 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(34, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait_until(7);
  isRed ? doinker.set_value(true) : ringRush.set_value(true);
  chassis.pid_wait_until(32);

  intake = 0;

  chassis.pid_turn_set(-236.5 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait();

  chassis.pid_drive_set(15, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait_until(10);

  doinker.set_value(false);
  ringRush.set_value(false);

  chassis.pid_turn_set(-180 * sign, TURN_SPEED);
  pros::delay(100);
  chassis.pid_wait_until(-180 * sign);

  chassis.pid_drive_set(-30, DRIVE_SPEED, false);
  pros::delay(100);
  chassis.pid_wait_until(-20);



}

void samsPositiveSideRed() {
  samsPositiveSide(true);
}

void samsPositiveSideBlue() {
  samsPositiveSide(false);
}
void doNothingAuto() {
  // do nothing
}