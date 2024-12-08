#include "constants.hpp"
#include "main.h"
#include "pros/adi.h"

bool toggleClamp   = false;
bool toggleDoinker = false;
bool toggleLift    = false;
bool toggleHang    = false;

void moveIntake(double vltg)    {
    MOTOR_INTAKE.move_voltage(vltg);
}

void moveArm(double vltg)  {
    MOTORGROUP_ARM.move_voltage(vltg);
}

void moveArmStates(int state)    {

}

void controlIntake()    {
    if (controlla.get_digital(BUTTON_INTAKE)) {
        moveIntake(12000);
    }
    else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) {
        moveIntake(-12000);
    }
    else {
        moveIntake(0);
    }
}

void controlArm()   {
    if (controlla.get_digital(BUTTON_ARM)) {
        moveArm(12000);
    }
    else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
        moveArm(-12000);
    }
    else {
        moveArm(0);
    }
}

void controlArmStates() {
    
}

void controlClamp() {
    if (controlla.get_digital_new_press(BUTTON_CLAMP)) {
        toggleClamp = !toggleClamp;
    }   PISTON_CLAMP.set_value(toggleClamp);
}

void controlDoinker() {
    if (controlla.get_digital_new_press(BUTTON_DOINKER)) {
        toggleDoinker = !toggleDoinker;
    }   PISTON_DOINKER.set_value(toggleDoinker);
}

void controlLift() {
    if (controlla.get_digital_new_press(BUTTON_LIFT)) {
        toggleLift = !toggleLift;
    }   PISTON_LIFT.set_value(toggleLift);
}

void controlHang() {
    if (controlla.get_digital_new_press(BUTTON_HANG)) {
        toggleHang = !toggleHang;
    }   PISTON_HANG.set_value(toggleHang);
}