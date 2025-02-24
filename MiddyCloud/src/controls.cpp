#include "constants.hpp"
#include "main.h"
#include "pros/misc.h"

// declares booleans for subsystem control
bool toggleIntakeLift = false;
bool toggleClamp = false;
bool toggleDoinker = false;
bool toggleHang = false;
bool toggleHoodLift = false;
bool toggleArmPivot = false;
bool toggleArmClamp = false;

// moves the intake motors at a specified voltage
void intakeVoltage(int vltg)    {
    MotorIntakeLeft.move_voltage(vltg);
    MotorIntakeRight.move_voltage(vltg);
}

// moves the arm motor at a specified voltage
void armVoltage(int vltg)   {
    MotorArm.move_voltage(vltg);
}


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

//activates the clamp
void activateClamp() {
    pistonClamp.set_value(true);
    toggleClamp = true;
}

//deactivates the clamp
void deActivateClamp() {
    pistonClamp.set_value(false);
    toggleClamp = false;
}

//activates the Doinker
void activateDoinker() {
    pistonDoinker.set_value(true);
}

//deactivates the Doinker
void deActivateDoinker() {
    pistonDoinker.set_value(false);
}

//activates the hang
void activateHang() {
    pistonHang.set_value(true);
}

//deactivates the hang
void deActivateHang() {
    pistonHang.set_value(false);
}

// void activate() {

// }

// void deActivate() {

// }

// void control() {
    
// }

// activates the hood lift
void activateHoodLift() {
    pistonHoodLift.set_value(true);
    toggleHoodLift = true;
}

// deactivates the hood lift
void deActivateHoodLift() {
    pistonHoodLift.set_value(false);
    toggleHoodLift = false;
}

//  movees the intake in driver control
void controlIntake()    {
    if (controlla.get_digital(buttonIntake)) {
        intakeVoltage(12000);
    }
    else if (controlla.get_digital(buttonIntakeReverse)) {
        intakeVoltage(-12000);
    }
    else {
        intakeVoltage(0);
    }
}

// moves the arm in driver control
void controlArm()   {
    if (controlla.get_digital(buttonArm)) {
        armVoltage(12000);
    }
    else if (controlla.get_digital(buttonArmReverse)) {
        armVoltage(-12000);
    }
    else {
        armVoltage(0);
    }
}

// controls the intake lift in driver control
void controlIntakeLift() {
    if (controlla.get_digital_new_press(buttonIntakeLift)) {
        toggleIntakeLift = !toggleIntakeLift;
    }
    pistonIntakeLift.set_value(toggleIntakeLift);
}

// controls the clamp in driver control
void controlClamp() {
    if (controlla.get_digital_new_press(buttonClamp)) {
    toggleClamp = !toggleClamp;
    }
    pistonClamp.set_value(toggleClamp);
}

// controls the Doinker in driver control
void controlDoinker() {
    if (controlla.get_digital_new_press(buttonDoinker)) {
    toggleDoinker = !toggleDoinker;
    }
    pistonDoinker.set_value(toggleDoinker);
}

// controls the hang in driver control
void controlHang() {
    if (controlla.get_digital_new_press(buttonHang)) {
    toggleHang = !toggleHang;
    }
    pistonHang.set_value(toggleHang);
}

// controls the hood lift in driver control
void controlHoodLift() {
    if (controlla.get_digital_new_press(buttonHoodLift)) {
        toggleHoodLift = !toggleHoodLift;
    }
    pistonHoodLift.set_value(toggleHoodLift);
}