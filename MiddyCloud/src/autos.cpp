#include "constants.hpp"
#include "controls.hpp"
#include "main.h" 
#include "pros/rtos.hpp"

// a universal speed for the EzTempChassis to follow. These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

//nothing happens during auto, last ditch effort if no autos work
//(0 stakes, 0 rings, no lader, 0pts.)
void noAuto()   {

}

void bluePos()  {

}

void redPos()   {

    LemLibChassis.setPose(0,0,0);
    LemLibChassis.moveToPose(3.6, -22.65, -19.6, 99999, {false});
    LemLibChassis.waitUntilDone();
    activateClamp();
    intakeVoltage(12000);
    pros::delay(500);
    LemLibChassis.moveToPoint(-9.5, -29, 99999);
    LemLibChassis.waitUntilDone();
    pros::delay(500);
    LemLibChassis.moveToPoint(22.5, -11.25, 99999, {false});
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPoint(3, -17, 99999);
    LemLibChassis.waitUntilDone();
    LemLibChassis.moveToPose(22.7, -43, 135, 99999);
    deActivateClamp();
    LemLibChassis.waitUntilDone();
    activateHang();


}

void blueNeg()  {

}

void redNeg()   {

}

void bluePosRush()  {

}

void redPosRush()   {

}

void blueNegRush()  {

}

void redNegRush()   {

}