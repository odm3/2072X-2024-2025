#include "autons.hpp"
#include <cmath>
#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/util.hpp"
#include "controls.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

//  auto that just drives forward a little bit, use if teammate has a good soloawp
void drive6() { EzChassis.pid_drive_set(6, DRIVE_SPEED); }

void cornerTest(){
  isRed = true;
  autoClampActive = false;
  ColorLoopActive = false;

  intake_vltg = -12000;
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(25, 110);
  pros::delay(400);
  intake_vltg = 12000;
  pros::delay(400);
  EzChassis.pid_drive_set(-36, DRIVE_SPEED);
}

void qualNegRed() {
  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(130.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(340, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = true;
  intakeSet(12000);
  EzChassis.pid_drive_set(32, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(310, TURN_SPEED);
  EzChassis.pid_drive_set(-23, DRIVE_SPEED);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait_quick();
  hookSet(12000);
  EzChassis.pid_turn_set(290, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(150);
  EzChassis.pid_turn_set(270, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 80);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(21, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(223.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(22, 65);
  armPos(19500);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-20, 90);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(10, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, 127);
  EzChassis.pid_wait_quick_chain();
  
  EzChassis.pid_turn_set(105, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(28, 127);
  EzChassis.pid_wait_quick_chain();
  armPos(ARM_DOWN);
  doinkerLeftState = true;
  pros::delay(250);
  EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(80, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_swing_set(ez::RIGHT_SWING, 0, 127, 45);
  armPos(16000);
  EzChassis.pid_wait_quick_chain();
}

void qualNegBlue() {
  isRed = false;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-130.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(-340, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = true;
  intakeSet(12000);
  EzChassis.pid_drive_set(32, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-310, TURN_SPEED);
  EzChassis.pid_drive_set(-22, DRIVE_SPEED);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait_quick_chain();
  hookSet(12000);
  EzChassis.pid_turn_set(-292, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(-268, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 70);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(22, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-222, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(22, 65);
  armPos(19000);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-20, 90);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(10, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, 127);
  EzChassis.pid_wait_quick_chain();
  
  EzChassis.pid_turn_set(-100, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(26, 127);
  EzChassis.pid_wait_quick_chain();
  armPos(ARM_DOWN);
  doinkerRightState = true;
  pros::delay(250);
  EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(-80, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPos(15500);
  EzChassis.pid_drive_set(6, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-20, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, 127);
  EzChassis.pid_wait_quick();
}

void elimNegRed() {
  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(130.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(340, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = true;
  intakeSet(12000);
  EzChassis.pid_drive_set(32, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(310, TURN_SPEED);
  EzChassis.pid_drive_set(-23, DRIVE_SPEED);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait_quick();
  hookSet(12000);
  EzChassis.pid_turn_set(290, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(150);
  EzChassis.pid_turn_set(270, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 80);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(21, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(223.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(20, 65);
  armPos(19500);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-20, 90);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(10, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, 127);
  EzChassis.pid_wait_quick_chain();
  
  EzChassis.pid_turn_set(105, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(28, 127);
  EzChassis.pid_wait_quick_chain();
  armPos(ARM_DOWN);
  doinkerLeftState = true;
  pros::delay(250);
  EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(80, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_swing_set(ez::LEFT_SWING, 100, 127, 45);
  EzChassis.pid_wait_quick_chain();
}

void ringRushRed() {
  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(340);
  EzChassis.pid_drive_set(45, 127);
  doinkerLeftState = true;
  //intake_vltg = 12000;
  intakeSet(12000);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(310, TURN_SPEED);
  //EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-28, 127);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait();
  hookSet(12000);
  EzChassis.pid_turn_set(290, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(150);
  EzChassis.pid_turn_set(270, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 80);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(21, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(223.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(20, 65);
  armPos(19500);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, 90);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(10, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, 127);
  EzChassis.pid_wait_quick_chain();
  
  EzChassis.pid_turn_set(105, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(28, 127);
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_wait_quick_chain();
  doinkerLeftState = true;
  pros::delay(250);
  EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(80, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(6,  127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(145, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(12, 127);
  hookSet(0);
  armPos(ARM_ALLIANCE);
  pros::delay(250);
  hookSet(12000);
  pros::delay(850);
  EzChassis.pid_wait();
}

void elimNegBlue() {

  isRed = false;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-130.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(-340, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = true;
  intakeSet(12000);
  EzChassis.pid_drive_set(32, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-310, TURN_SPEED);
  EzChassis.pid_drive_set(-23, DRIVE_SPEED);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait();
  hookSet(12000);
  EzChassis.pid_turn_set(-290, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(150);
  EzChassis.pid_turn_set(-270, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 80);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(20, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-223.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 35);
  armPos(19500);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-20, 127);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(10, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, 127);
  EzChassis.pid_wait_quick_chain();
  
  EzChassis.pid_turn_set(-105, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(28, 127);
  EzChassis.pid_wait_quick_chain();
  armPos(ARM_DOWN);
  doinkerLeftState = true;
  pros::delay(250);
  EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(-80, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(6,  127);
  EzChassis.pid_wait_quick_chain();

}

void ringRushBlue() {
  isRed = false;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-340);
  EzChassis.pid_drive_set(45, 127);
  doinkerRightState = true;
  //intake_vltg = 12000;
  intakeSet(12000);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-310, TURN_SPEED);
  //EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-28, 127);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait();
  hookSet(12000);
  EzChassis.pid_turn_set(-290, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  pros::delay(150);
  EzChassis.pid_turn_set(-272, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 70);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(20, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-223.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(22, 65);
  //armPos(19500);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-20, 127);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(10, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, 127);
  EzChassis.pid_wait_quick_chain();
  
  EzChassis.pid_turn_set(-100, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(28, 127);
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_wait_quick_chain();
  doinkerRightState = true;
  pros::delay(250);
  EzChassis.pid_drive_set(-12, DRIVE_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(-80, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(6,  127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-152, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, 127);
  armPid.target_set(ARM_ALLIANCE);
  hookSet(0);
  pros::delay(100);
  hookSet(12000);
  pros::delay(850);
  EzChassis.pid_wait();
}


void qualPosRed() {

  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(229.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(700);
  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait_quick();

  EzChassis.pid_turn_set(309.5, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  doinkerRightState = true;
  pros::delay(100);


  EzChassis.pid_swing_set(ez::LEFT_SWING, 333, SWING_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(1, 127);
  EzChassis.pid_wait_quick_chain();
  doinkerLeftState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::LEFT_SWING, 317, SWING_SPEED, 50);
  //EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(280, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(112.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  intakeAndHookSet(12000);
  doinkerRightState = false;
  pros::delay(350);
  EzChassis.pid_turn_set(135, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(38, 65);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-17, 45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(9, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-5, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(0, 45);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 90);
  EzChassis.pid_wait_quick();
  EzChassis.pid_turn_set(-70, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(21, 127);
  armPos(16000);
  EzChassis.pid_wait_quick_chain();
}

void qualPosBlue() {

  isRed = false;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-229.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(700);
  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait_quick();

  EzChassis.pid_turn_set(-309.5, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  doinkerLeftState = true;
  pros::delay(100);


  EzChassis.pid_swing_set(ez::RIGHT_SWING, -333, SWING_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(1, 127);
  EzChassis.pid_wait_quick_chain();
  doinkerRightState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::RIGHT_SWING, -317, SWING_SPEED, 50);
  //EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-280, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-112.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  intakeAndHookSet(12000);
  doinkerLeftState = false;
  pros::delay(350);
  EzChassis.pid_turn_set(-132, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(38, 65);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-18, 45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(10, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-5, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(0, 45);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 90);
  EzChassis.pid_wait_quick();
  EzChassis.pid_turn_set(70, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(21, 127);
  armPos(15000);
  EzChassis.pid_wait_quick_chain();
}

void elimPosRed() {
  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(180);
  EzChassis.pid_drive_set(-29.5, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  pros::delay(100);

  EzChassis.pid_turn_set(309.5, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  hookSet(12000);
  EzChassis.pid_wait_quick_chain();
  hookSet(0);
  doinkerRightState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::LEFT_SWING, 333, SWING_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(1, 127);
  EzChassis.pid_wait_quick_chain();
  doinkerLeftState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::LEFT_SWING, 317, SWING_SPEED, 50);
  //EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(280, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(112.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  intakeAndHookSet(12000);
  doinkerRightState = false;
  pros::delay(350);
  EzChassis.pid_turn_set(129, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(40, 65);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-19, 45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(9, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-5, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(0, 45);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(30, 90);
  intakeAndHookSet(12000);
  EzChassis.pid_wait();
  pros::delay(1250);
  autoClampActive = false;
  clampState = false;
  EzChassis.pid_turn_set(175, TURN_SPEED);
  EzChassis.pid_wait_quick();
  autoClampActive = true;
  EzChassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
  EzChassis.pid_drive_set(-6, 70);
  EzChassis.pid_wait_quick_chain();
}

void elimPosBlue() {
  isRed = false;
  autoClampActive = true;
  ColorLoopActive = false;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-180);
  EzChassis.pid_drive_set(-29.5, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  pros::delay(100);

  EzChassis.pid_turn_set(-309.5, TURN_SPEED, true);
  EzChassis.pid_wait_until(-220);
  hookSet(12000);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  EzChassis.pid_wait_until(1);
  hookSet(0);
  EzChassis.pid_wait_quick_chain();
  hookSet(0);
  doinkerLeftState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::RIGHT_SWING, -333, SWING_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(1, 127);
  EzChassis.pid_wait_quick_chain();
  doinkerRightState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::RIGHT_SWING, -317, SWING_SPEED, 50);
  //EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-280, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-112.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  intakeAndHookSet(12000);
  doinkerLeftState = false;
  pros::delay(350);
  EzChassis.pid_turn_set(-129, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(38, 65);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-19, 45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(9, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-3, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-0, 45);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(30, 90);
  intakeAndHookSet(12000);
  ColorLoopActive = true;
  EzChassis.pid_wait();
  pros::delay(1250);
  autoClampActive = false;
  clampState = false;
  EzChassis.pid_turn_set(-185, TURN_SPEED);
  EzChassis.pid_wait_quick();
  autoClampActive = true;
  EzChassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
  EzChassis.pid_drive_set(-6, 70);
  EzChassis.pid_wait_quick_chain();
  clampState = true;

}

void elimPosRedWall() {
  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(180);
  EzChassis.pid_drive_set(-29.5, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  pros::delay(100);

  EzChassis.pid_turn_set(309.5, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  hookSet(12000);
  EzChassis.pid_wait_quick_chain();
  hookSet(0);
  doinkerRightState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::LEFT_SWING, 333, SWING_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(1, 127);
  EzChassis.pid_wait_quick_chain();
  doinkerLeftState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::LEFT_SWING, 317, SWING_SPEED, 50);
  //EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(280, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(112.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  intakeAndHookSet(12000);
  doinkerRightState = false;
  pros::delay(350);
  EzChassis.pid_turn_set(129, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(40, 65);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-19, 45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(9, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-5, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(0, 30);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(30, 90);
  intakeAndHookSet(12000);
  armPos(ARM_PRIME1);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(53, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(13, 127);
  EzChassis.pid_wait_quick_chain();
  hookSet(100);
  armPos(14000);
  pros::delay(250);
  hookSet(12000);
  pros::delay(1000);

}

void elimPosBlueWall() {
  isRed = false;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-180);
  EzChassis.pid_drive_set(-29.5, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  pros::delay(100);

  EzChassis.pid_turn_set(-309.5, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  hookSet(12000);
  EzChassis.pid_wait_quick_chain();
  hookSet(0);
  doinkerLeftState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::RIGHT_SWING, -333, SWING_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(1, 127);
  EzChassis.pid_wait_quick_chain();
  doinkerRightState = true;
  pros::delay(100);

  EzChassis.pid_swing_set(ez::LEFT_SWING, -317, SWING_SPEED, 50);
  //EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(280, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-112.5, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  intakeAndHookSet(12000);
  doinkerLeftState = false;
  pros::delay(350);
  EzChassis.pid_turn_set(-129, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(40, 65);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-19, 45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(9, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-5, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-0, 30);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(30, 90);
  intakeAndHookSet(12000);
  armPos(ARM_PRIME1);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-53, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(13, 127);
  EzChassis.pid_wait_quick_chain();
  hookSet(100);
  armPos(14000);
  pros::delay(250);
  hookSet(12000);
  pros::delay(1000);

}

void newSoloAwpRed() {
  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(130.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(340, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = true;
  intakeSet(12000);
  EzChassis.pid_drive_set(32, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(310, TURN_SPEED);
  EzChassis.pid_drive_set(-23, DRIVE_SPEED);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait_quick_chain();
  hookSet(12000);
  EzChassis.pid_turn_set(290, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerLeftState = false;
  pros::delay(150);
  EzChassis.pid_turn_set(270, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 70);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(118, 60);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(70, 127);
  EzChassis.pid_wait_until(25);
  EzChassis.pid_speed_max_set(40);
  EzChassis.pid_wait_until(55);
  EzChassis.pid_speed_max_set(127);
  startColorUntil(1);
  autoClampActive = false;
  clampState = false;
  EzChassis.pid_wait_quick_chain();
  // doinkerLeftState = true;
  // pros::delay(250);
  EzChassis.pid_turn_set(185, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-32, 90);
  autoClampActive = true;
  clampState = false;
  EzChassis.pid_wait_until(-12);
  clampState = false;
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  pros::delay(250);
  EzChassis.pid_turn_set(90, TURN_SPEED);
  EzChassis.pid_wait_quick();
  intakeAndHookSet(12000);
  EzChassis.pid_drive_set(20, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-24, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-70, TURN_SPEED);
  EzChassis.pid_wait_quick();
  armPos(17000);
  
  // EzChassis.pid_turn_set(115, TURN_SPEED);
  // EzChassis.pid_wait_quick();
  // doinkerLeftState = false;
  // pros::delay(250);
  // EzChassis.pid_turn_set(90, TURN_SPEED);
  // EzChassis.pid_wait_quick();
  // EzChassis.pid_drive_set(22, DRIVE_SPEED);
  // EzChassis.pid_wait_quick_chain();
  // EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  // EzChassis.pid_wait_quick_chain();
  // EzChassis.pid_turn_set(-70, TURN_SPEED);
  // armPos(17000);
  // EzChassis.pid_wait_quick();

}

void newSoloAwpRed1() {
  isRed = true;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(130.5);
  EzChassis.pid_drive_set(-14, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-24, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(150);

  EzChassis.pid_turn_set(308, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  intakeAndHookSet(12000);
  EzChassis.pid_drive_set(19, DRIVE_SPEED);
  doinkerLeftState = true;
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-9, DRIVE_SPEED);
  doinkerLeftState = false;
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(242, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(16, 127);
  EzChassis.pid_wait_quick();

  EzChassis.pid_turn_set(120, TURN_SPEED, true);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(30, 127, true);
  EzChassis.pid_wait_until(24);
  clampState = false;
  EzChassis.pid_wait_quick_chain();
  intake_vltg = 0;
  doinkerLeftState = true;
  pros::delay(150);

  EzChassis.pid_turn_set(237.5, 45, true);
  EzChassis.pid_wait_quick();

  EzChassis.pid_drive_set(-42, DRIVE_SPEED, true);
  EzChassis.pid_wait_until(-20);
  EzChassis.pid_speed_max_set(40);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(200);

  EzChassis.pid_turn_set(110, 60);
  EzChassis.pid_wait();
  doinkerLeftState = false;
  pros::delay(100);
  EzChassis.pid_turn_set(90, TURN_SPEED);
  intake_vltg = 12000;
  EzChassis.pid_drive_set(20, 90);
  EzChassis.pid_wait_quick_chain(); 
  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(300, TURN_SPEED);
  EzChassis.pid_wait_quick();
  armPid.target_set(16750);
  pros::delay(500);
}

void newSoloAwpBlue() {
  isRed = false;
  autoClampActive = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-130.5);
  EzChassis.pid_drive_set(1, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(-340, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = true;
  intakeSet(12000);
  EzChassis.pid_drive_set(32, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-310, TURN_SPEED);
  EzChassis.pid_drive_set(-22, DRIVE_SPEED);
  EzChassis.pid_wait_until(-10);
  EzChassis.pid_speed_max_set(75);
  EzChassis.pid_wait_quick_chain();
  hookSet(12000);
  EzChassis.pid_turn_set(-290, TURN_SPEED);
  EzChassis.pid_wait_quick();
  doinkerRightState = false;
  pros::delay(250);
  EzChassis.pid_turn_set(-267, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(24, 70);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(-113, 60);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(70, 127);
  EzChassis.pid_wait_until(25);
  EzChassis.pid_speed_max_set(30);
  EzChassis.pid_wait_until(55);
  EzChassis.pid_speed_max_set(127);
  //startColorUntil(1);
  autoClampActive = false;
  clampState = false;
  EzChassis.pid_wait_quick_chain();
  // // doinkerLeftState = true;
  // // pros::delay(250);
  hookSet(0);
  EzChassis.pid_turn_set(-185, TURN_SPEED);
  hookSet(0);
  EzChassis.pid_wait_quick();
  hookSet(0);
  EzChassis.pid_drive_set(-34, 90);
  autoClampActive = true;
  clampState = false;
  EzChassis.pid_wait_until(-12);
  clampState = false;
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  pros::delay(250);
  EzChassis.pid_turn_set(-90, 50);
  EzChassis.pid_wait_quick();
  intakeAndHookSet(12000);
  EzChassis.pid_drive_set(20, 127);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(70, 50);
  EzChassis.pid_wait_quick();
  armPos(17000);
}

void soloAwpRed() {
  isRed = true;
  autoClampActive = false;
  ColorLoopActive = false;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(130.5);
  EzChassis.pid_drive_set(4, DRIVE_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(200);

  EzChassis.pid_turn_set(305, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  intake_vltg = 12000;
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-6, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(242, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(15, 127);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(112, TURN_SPEED, true);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(64, 127, true);
  EzChassis.pid_wait_until(24);
  EzChassis.pid_speed_max_set(35);
  clampState = false;
  EzChassis.pid_wait_until(58);
  ColorLoopActive = false;
  //startColorUntil(1);
  EzChassis.pid_wait_until(61);
  intake_vltg = 0;
  EzChassis.pid_wait_quick_chain();

  autoClampActive = false;
  EzChassis.pid_turn_set(190, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-30, DRIVE_SPEED);
  EzChassis.pid_wait_until(-12);
  EzChassis.pid_speed_max_set(40);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(200);


  EzChassis.pid_turn_set(90, TURN_SPEED);
  EzChassis.pid_wait_quick();
  //stopColorUntilFunction();
  intake_vltg = 12000;

  EzChassis.pid_drive_set(18, 127);
  EzChassis.pid_wait_quick_chain();
  startColorUntil(1);
  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(300, TURN_SPEED);
  EzChassis.pid_wait_quick();
  stopColorUntilFunction();
  armPid.target_set(16750);
  pros::delay(500);
  intake_vltg = 12000;
  pros::delay(1000);
}

void soloAwpBlue() {
  isRed = false;
  autoClampActive = false;
  ColorLoopActive = false;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(-130.5);
  EzChassis.pid_drive_set(4, DRIVE_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-26, DRIVE_SPEED);
  EzChassis.pid_wait_until(-6);
  EzChassis.pid_speed_max_set(60);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(200);

  EzChassis.pid_turn_set(-310, TURN_SPEED, true);
  EzChassis.pid_wait_quick();
  intake_vltg = 12000;
  EzChassis.pid_drive_set(16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-8, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(-250, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(15, 127);
  EzChassis.pid_wait_quick_chain();

  EzChassis.pid_turn_set(-112, TURN_SPEED, true);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(64, 127, true);
  EzChassis.pid_wait_until(24);
  EzChassis.pid_speed_max_set(35);
  clampState = false;
  EzChassis.pid_wait_until(58);
  ColorLoopActive = true;
  //startColorUntil(1);
  EzChassis.pid_wait_until(60);
  intake_vltg = 0;
  EzChassis.pid_wait_quick_chain();

  ColorLoopActive = false;
  autoClampActive = false;
  EzChassis.pid_turn_set(-195, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-32, DRIVE_SPEED);
  EzChassis.pid_wait_until(-12);
  EzChassis.pid_speed_max_set(40);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(200);


  EzChassis.pid_turn_set(-90, TURN_SPEED);
  EzChassis.pid_wait_quick();
  stopColorUntilFunction();
  intake_vltg = 12000;

  EzChassis.pid_drive_set(18, 127);
  EzChassis.pid_wait_quick_chain();
  startColorUntil(1);
  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-300, TURN_SPEED);
  EzChassis.pid_wait_quick();
  stopColorUntilFunction();
  armPid.target_set(16750);
  pros::delay(500);
  intake_vltg = 12000;
  pros::delay(1000);
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

void skills() {
  isRed = true;
  ColorLoopActive = true;
  rotation_arm.set_position(ARM_PRIME1);
  EzChassis.drive_angle_set(130.5);
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  intake_vltg = 12000;  // Start intake motor
  EzChassis.pid_drive_set(-19, 60);
  EzChassis.pid_wait();
  armPid.target_set(ARM_DOWN);
  clampState = true;
  pros::delay(200);
  EzChassis.pid_turn_set(0, 60);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(16, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-24, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(54, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-12.5, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-24, DRIVE_SPEED, true);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(-90, TURN_SPEED);
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(14, 80);
  EzChassis.pid_wait();
  pros::delay(750);
  EzChassis.drive_set(60, 60);
  intake_vltg = 0;
  armPid.target_set(16000);
  pros::delay(600);
  EzChassis.drive_set(0, 0);

  EzChassis.pid_drive_set(-16, DRIVE_SPEED);
  EzChassis.pid_wait();
  intake_vltg = 12000;
  EzChassis.pid_turn_set(-180, TURN_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_DOWN);
  EzChassis.pid_drive_set(59, 127, true);
  EzChassis.pid_wait_until(24);
  EzChassis.pid_speed_max_set(25);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-24, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(210, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(18, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-6, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(20, 60);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-22, DRIVE_SPEED);
  EzChassis.pid_wait();
  clampState = false;
  pros::delay(500);

  EzChassis.pid_drive_set(3, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(270, TURN_SPEED, true);
  EzChassis.pid_wait();
  // EzChassis.drive_set(45,  45);
  // pros::delay(500);
  // EzChassis.drive_set(0, 0);
  // EzChassis.drive_angle_set(270);
  // EzChassis.pid_drive_set(-88, 127, true);
  // EzChassis.pid_wait_until(-60);
  // EzChassis.pid_speed_max_set(45);
  EzChassis.pid_drive_set(-80, 127, true);
  EzChassis.pid_wait_until(-50);
  EzChassis.pid_speed_max_set(45);
  EzChassis.pid_wait();
  clampState = true;
  pros::delay(250);

  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(14, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(27 , TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(50, DRIVE_SPEED);
  EzChassis.pid_wait_until(30);
  EzChassis.pid_speed_max_set(45);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(13, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-20, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(90, TURN_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_drive_set(16, DRIVE_SPEED);
  EzChassis.pid_wait();
  pros::delay(750);
  EzChassis.drive_set(60, 60);
  intake_vltg = 0;
  armPid.target_set(16000);
  pros::delay(600);
  EzChassis.drive_set(0, 0);
  
  EzChassis.pid_drive_set(-14, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(180, TURN_SPEED);
  EzChassis.pid_wait();
  armPid.target_set(ARM_DOWN);
  intake_vltg = 12000;
  EzChassis.pid_drive_set(58, DRIVE_SPEED, true);
  EzChassis.pid_wait_until(20);
  EzChassis.pid_speed_max_set(25);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-22, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(150, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(16, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-6, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-20, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-22, DRIVE_SPEED);
  EzChassis.pid_wait();
  intake_vltg = 0;
  clampState = false;
  pros::delay(150);

  EzChassis.pid_drive_set(24, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(ARM_PRIME1);
  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait_quick();
  intake_vltg = 12000;
  EzChassis.pid_drive_set(77.5, 127, true);
  EzChassis.pid_wait();
  pros::delay(500);
  EzChassis.pid_turn_set(90, DRIVE_SPEED);
  EzChassis.pid_wait();
  EzChassis.pid_drive_set(-52, DRIVE_SPEED);
  EzChassis.pid_wait_until(-20);
  EzChassis.pid_speed_max_set(40);
  EzChassis.pid_wait();
  pros::delay(250);

  EzChassis.pid_turn_set(0, TURN_SPEED);
  EzChassis.pid_wait();
  EzChassis.drive_set(60, 60);
  pros::delay(750);
  EzChassis.drive_set(0, 0);
  EzChassis.pid_drive_set(-8, DRIVE_SPEED, false, false);
  EzChassis.pid_wait();
  intake_vltg = 0;
  armPid.target_set(ARM_ALLIANCE);
  pros::delay(750);
  EzChassis.pid_drive_set(-4, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(2000);
  EzChassis.pid_turn_set(240, TURN_SPEED);
  EzChassis.pid_wait_quick();
  EzChassis.pid_drive_set(-72, DRIVE_SPEED, false, false);
  EzChassis.pid_wait();
  EzChassis.pid_turn_set(220, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(30, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(120, DRIVE_SPEED, true);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-42, 125);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(100, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(-44, DRIVE_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(145, TURN_SPEED);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_drive_set(42, 125);
  EzChassis.pid_wait_quick_chain();
  EzChassis.pid_turn_set(-47, 100, true);
  EzChassis.pid_wait_quick_chain();
  armPid.target_set(10000);
  EzChassis.drive_set(-35, -35);
  pros::delay(2000);
  armPid.target_set(ARM_PRIME1);
  EzChassis.drive_set(10, 10);
  pros::delay(500);
  EzChassis.drive_set(0, 0);

}