#include "constants.hpp"
#include "main.h"
#include "pros/misc.h"

bool toggleIntakeLift = false;
bool toggleClamp = false;
bool toggleHammer = false;
bool toggleHang = false;
bool toggleHoodLift = false;
bool toggleArmPivot = false;
bool toggleArmClamp = false;

//activates the intake lift
void activateIntakeLift() {
    pistonIntakeLift.set_value(true);
    toggleIntakeLift = true;
}

//deactivates the intake lift
void deActivateIntakeLift() {
    pistonIntakeLift.set_value(false);
    toggleIntakeLift = false;
}

//controls the intake lift in driver control
void controlIntakeLift() {
    if (controlla.get_digital(buttonIntakeLift)) {
        toggleIntakeLift = !toggleIntakeLift;
    }
    pistonIntakeLift.set_value(toggleIntakeLift);
}

//activates the clamp
void activateClamp() {
    pistonClampLeft.set_value(true);
    pistonClampRight.set_value(true);
    toggleClamp = true;
}

//deactivates the clamp
void deActivateClamp() {
    pistonClampLeft.set_value(false);
    pistonClampRight.set_value(false);
    toggleClamp = false;
}

//controls the clamp in driver control
void controlClamp() {
    if (controlla.get_digital(buttonClamp)) {
    toggleClamp = !toggleClamp;
    }
    pistonClampLeft.set_value(toggleClamp);
    pistonClampRight.set_value(toggleClamp);
}

//activates the hammer
void activateHammer() {
    pistonHammer.set_value(true);
}

//deactivates the hammer
void deActivateHammer() {
    pistonHammer.set_value(false);
}

//controls the hammer in driver control
void controlHammer() {
    if (controlla.get_digital(buttonHammer)) {
    toggleHammer = !toggleHammer;
    }
    pistonHammer.set_value(toggleHammer);
}

//activates the hang
void activateHang() {
    pistonHang.set_value(true);
}

//deactivates the hang
void deActivateHang() {
    pistonHang.set_value(false);
}

//controls the hang in driver control
void controlHang() {
    if (controlla.get_digital(buttonHang)) {
    toggleHang = !toggleHang;
    }
    pistonHang.set_value(toggleHang);
}

// void activate() {

// }

// void deActivate() {

// }

// void control() {
    
// }

void intakevoltage(int vltg)    {
    MotorIntakeLeft.move_voltage(vltg);
    MotorIntakeRight.move_voltage(vltg);
}

void armVoltage(int vltg)   {
    MotorArm.move_voltage(vltg);
}

void intakeControl(int vltg)    {
    if (controlla.get_digital(buttonIntake)) {
        intakevoltage(12000);
    }
    else if (controlla.get_digital(buttonIntakeReverse)) {
        intakevoltage(-12000);
    }
}

void armControl(int vltg)   {
    if (controlla.get_digital(buttonArm)) {
        armVoltage(12000);
    }
    else if (controlla.get_digital(buttonArmReverse)) {
        armVoltage(-12000);
    }
}