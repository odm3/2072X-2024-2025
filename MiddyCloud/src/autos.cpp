#include "EZ-Template/drive/drive.hpp"
#include "constants.hpp"
#include "controls.hpp"
#include "main.h" 
#include "pros/device.hpp"
#include "pros/rtos.hpp"

// a universal speed for the EzTempChassis to follow. These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

//nothing happens during auto, last ditch effort if no autos work
//(0 stakes, 0 rings, no lader, 0pts.)
void noAuto()   {

}

void testEzDrive()  {
    EzTempChassis.pid_drive_set(24_in, DRIVE_SPEED, false);
    EzTempChassis.pid_wait();
    pros::delay(250);
    EzTempChassis.pid_drive_set(-24_in, DRIVE_SPEED, false);
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

void testLLDrive()  {
    LemLibChassis.setPose(0,0,0);
    LemLibChassis.moveToPoint(0, 24, 9999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPose(0, 0, 0, 9999, {false});
    LemLibChassis.waitUntilDone();
}

void testLLTurn()   {
    LemLibChassis.setPose(0,0,0);
    LemLibChassis.turnToHeading(90, 9999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.turnToHeading(-45, 9999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.turnToHeading(0, 9999);
    LemLibChassis.waitUntilDone();
}


void driveToLadder()    {
    EzTempChassis.drive_set(50, 50);
    pros::delay(5000);
    EzTempChassis.drive_set(0, 0);
}

void redPos()   {

    LemLibChassis.setPose(0,0,0);
    LemLibChassis.moveToPoint(0, -15, 999, {false});
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPose(3, -23.5, -27, 999, {false});
    LemLibChassis.waitUntilDone();
    activateClamp();
    pros::delay(250);
    intakeVoltage(12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-8.5, -30, 999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.turnToHeading(275, 999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-20, -25, 9999);
    LemLibChassis.waitUntilDone();

}

void redNeg()  {

    LemLibChassis.setPose(0,0,0);
    LemLibChassis.moveToPoint(0, -15, 999, {false});
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPose(-3, -23.5, 27, 999, {false});
    LemLibChassis.waitUntilDone();
    activateClamp();
    pros::delay(250);
    intakeVoltage(12000);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(8.5, -30, 999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.turnToHeading(-275, 999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(-20, -25, 9999);
    LemLibChassis.waitUntilDone();
    
    deActivateClamp();

}


void RedPosBlueNeg2AWP()  {
    EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-27_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-3.5_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();
    EzTempChassis.pid_turn_set(-85_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    intakeVoltage(12000);
    EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();

    // EzTempChassis.pid_turn_set(90_deg, TURN_SPEED, true);
    // EzTempChassis.pid_wait();
    // EzTempChassis.pid_drive_set(18_in, 127);
    // EzTempChassis.pid_wait();
}

void RedNegBluePos2AWP()  {
    EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(27_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-3.5_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();
    EzTempChassis.pid_turn_set(85_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    intakeVoltage(12000);
    EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(-90_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(18_in, 127);
    EzTempChassis.pid_wait();
    
}


void RedNegBluePos3AWP()   {
    EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(27_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-3.5_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();
    EzTempChassis.pid_turn_set(85_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    intakeVoltage(12000);
    EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-60_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(22_in, DRIVE_SPEED, true);
    activateIntakeLift();
    EzTempChassis.pid_wait();
    pros::delay(250);
    deActivateIntakeLift();
    pros::delay(100);
    EzTempChassis.pid_drive_set(-6_in,DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-130_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateHang();
}

void RedPosBlueNeg3AWP()   {
    EzTempChassis.pid_drive_set(-12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(-27_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(-3.5_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateClamp();
    EzTempChassis.pid_turn_set(-85_deg, TURN_SPEED);
    EzTempChassis.pid_wait();
    intakeVoltage(12000);
    EzTempChassis.pid_drive_set(10_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(60_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(22_in, DRIVE_SPEED, true);
    activateIntakeLift();
    EzTempChassis.pid_wait();
    pros::delay(250);
    deActivateIntakeLift();
    pros::delay(100);
    EzTempChassis.pid_drive_set(-6_in,DRIVE_SPEED);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_turn_set(130_deg, TURN_SPEED, true);
    EzTempChassis.pid_wait();
    EzTempChassis.pid_drive_set(12_in, DRIVE_SPEED);
    EzTempChassis.pid_wait();
    activateHang();
}

void bluePosRush()  {

}

void redPosRush()   {

}

void blueNegRush()  {

}

void redNegRush()   {

}