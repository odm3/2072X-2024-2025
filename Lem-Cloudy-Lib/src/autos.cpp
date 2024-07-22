#include "autos.hpp"
#include "arm.hpp"
#include "devices.hpp"
#include "intake.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: keep
#include "misc.hpp"
#include "pros/rtos.hpp"

ASSET(x)

void noAuto() {

}

void tuneLateral() {
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 40, 99999);
}

void qualLeft() {

}

void qualRight() {

}

void soloAWPLeft() {

}

void soloAWPRight() {
    chassis.setPose(58,-5.5,104);
    chassis.moveToPose(-35.5, -20, 104, 9999, {false});
    clampActivate();
    chassis.moveToPose(-43, -7, 333, 9999, {}, false);
    intakeVoltage(12000);
    pros::delay(500);
    intakeVoltage(-12000);
    chassis.waitUntilDone();
    chassis.moveToPose(-27, -40, 155, 9999, {}, false);
    pros::delay(750);
    intakeVoltage(12000);
    chassis.waitUntilDone();
    pros::delay(250);
    chassis.moveToPose(-9, -28, 60, 9999);
    armVoltage(12000);
    pros::delay(2000);
    armVoltage(0); 

}

void elimsLeft() {

}

void elimsRight() {

}



void Skills() {

}
