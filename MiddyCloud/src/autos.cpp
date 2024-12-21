#include "EZ-Template/drive/drive.hpp"
#include "constants.hpp"
#include "controls.hpp"
#include "main.h" 
#include "pros/device.hpp"
#include "pros/rtos.hpp"

// a universal speed for the EzTempChassis to follow. These are out of 127
const int DRIVE_SPEED = 90;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

//nothing happens during auto, last ditch effort if no autos work
//(0 stakes, 0 rings, no lader, 0pts.)
void noAuto()   {

}

void testEzDrive()  {
    EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    EzTempChassis.pid_wait();
    pros::delay(250);
    EzTempChassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
    EzTempChassis.pid_wait();
}

void testEzTurn()   {
    EzTempChassis.pid_turn_set(90_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    pros::delay(250);
    EzTempChassis.pid_turn_set(45_deg, TURN_SPEED, false);
    EzTempChassis.pid_wait();
    pros::delay(250);
    EzTempChassis.pid_turn_set(-45_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(0_deg, TURN_SPEED, false);
    EzTempChassis.pid_wait();
}


void driveToLadder()    {
    EzTempChassis.drive_set(50, 50);
    pros::delay(5000);
    EzTempChassis.drive_set(0, 0);
}

void left2()    {

    EzTempChassis.pid_drive_set(-4_in, DRIVE_SPEED, true);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-2_in, 60, true);
    EzTempChassis.pid_wait();

    activateClamp();

    EzTempChassis.pid_turn_set(-300_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();

    intakeVoltage(12000);

    EzTempChassis.pid_drive_set(10_in, 75);
    EzTempChassis.pid_wait();

    EzTempChassis.drive_set(0, 0);
    pros::delay(5000);

}

void left4()    {

    EzTempChassis.pid_drive_set(-4_in, DRIVE_SPEED, true);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-2_in, 60, true);
    EzTempChassis.pid_wait();

    activateClamp();

    EzTempChassis.pid_turn_set(-300_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();

    intakeVoltage(12000);

    EzTempChassis.pid_drive_set(16_in, 80);
    EzTempChassis.pid_wait();

    EzTempChassis.drive_set(0, 0);

    EzTempChassis.pid_turn_set(-230_deg, 60, true);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(16.5_in, 60, true);
    EzTempChassis.pid_wait();

    EzTempChassis.drive_set(0, 0);
    pros::delay(5000);
}

void right2()   {

    EzTempChassis.pid_drive_set(-4_in, DRIVE_SPEED, true);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-2_in, 60, true);
    EzTempChassis.pid_wait();

    activateClamp();

    EzTempChassis.pid_turn_set(-60_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();

    intakeVoltage(12000);

    EzTempChassis.pid_drive_set(12_in, 75);
    EzTempChassis.pid_wait();

    EzTempChassis.drive_set(0, 0);
    pros::delay(5000);
}

void Skills()   {

EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
activateClamp();
intakeVoltage(12000);
EzTempChassis.pid_turn_set(180_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_turn_set(90_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_turn_set(0_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(36_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_turn_set(-90_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
deActivateClamp();
EzTempChassis.pid_drive_set(-26_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(60_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_turn_set(100_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(-27_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
activateClamp();
EzTempChassis.pid_turn_set(180_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(25_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_turn_set(-90_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(25_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_turn_set(0_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
EzTempChassis.pid_drive_set(40_in, DRIVE_SPEED);
EzTempChassis.pid_wait();
EzTempChassis.pid_turn_set(90_deg, TURN_SPEED, true);
EzTempChassis.pid_wait();
deActivateClamp();
EzTempChassis.pid_drive_set(-30_in, DRIVE_SPEED);
}

void Skills1()  {

    EzTempChassis.pid_drive_set(12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-110_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(45_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-36_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(115_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(50_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-10_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(0_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(96_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-45_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(34_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-90_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(40_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-10_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(40_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(75_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(40_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(115_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(42_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-42_in, DRIVE_SPEED);

}

void soloAWPelim()  {

    EzTempChassis.pid_drive_set(-18_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-45_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-8_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();
    EzTempChassis.pid_turn_set(6_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    intakeVoltage(12000);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(8_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    intakeVoltage(0);
    EzTempChassis.pid_wait();
    deActivateClamp();
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(14_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-52_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-15_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(56_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    intakeVoltage(12000);
    EzTempChassis.pid_wait();
    activateIntakeLift();
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(20_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    deActivateIntakeLift();
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(4_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-160_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(18_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    deActivateClamp();
    EzTempChassis.pid_wait();
    activateHang();
   
}

void soloAWPreg()  {
    EzTempChassis.pid_turn_set(-25_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-13_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-105_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    intakeVoltage(12000);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-204_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    deActivateClamp(); //CUT OFF HERE FOR NO MIDDLE AUTO, STOPS AT STACK        

    pros::delay(200);
    EzTempChassis.pid_drive_set(6_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-3_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-15_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();


    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(2_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(55_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(32_in, DRIVE_SPEED, true); // changed value to 32 -- ansh
    activateIntakeLift();
    EzTempChassis.pid_wait();
    pros::delay(250);
    deActivateIntakeLift();
    pros::delay(100);
    EzTempChassis.pid_drive_set(-6_in,DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(135_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(6_in,DRIVE_SPEED);
    EzTempChassis.pid_wait();
    intakeVoltage(0);
    deActivateClamp();
    EzTempChassis.pid_wait();
}