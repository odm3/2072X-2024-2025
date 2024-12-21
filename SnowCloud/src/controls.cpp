#include "EZ-Template/util.hpp"
#include "constants.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/rotation.h"
#include "pros/rtos.hpp"

bool toggleClamp     = false;
bool toggleDoinker   = false;
bool toggleLift      = false;
bool toggleHang      = false;
bool toggleArmStates = false;
int lbDriverIndex = 0; 

int lbArray [2] = { ARM_DOWN, ARM_PRIME};

void moveIntake(double vltg)    {
    MOTOR_INTAKE.move_voltage(vltg);
}

void moveArm(double vltg)  {
    MOTORGROUP_ARM.move_voltage(vltg);
}

void activateClamp()    {
    toggleClamp = true;
    PISTON_CLAMP.set_value(toggleClamp);
    pros::delay(150);
}

void deactivateClamp()  {
    toggleClamp = false;
    PISTON_CLAMP.set_value(toggleClamp);
    pros::delay(150);
}

void activateDoinker()    {
    toggleDoinker = true;
    PISTON_DOINKER.set_value(toggleDoinker);
}

void deactivateDoinker()  {
    toggleDoinker = false;
    PISTON_DOINKER.set_value(toggleDoinker);
}

void activateLift()    {
    toggleLift = true;
    PISTON_LIFT.set_value(toggleLift);
}

void deactivateLift()  {
    toggleLift = false;
    PISTON_LIFT.set_value(toggleLift);
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
        if (ROTATION_ARM.get_position() < 23000) {
        armPID.target_set(armPID.target_get() + 300);
        }
        else {
        armPID.target_set(24000);
        }
    }
    else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
        if (ROTATION_ARM.get_position() > 1000) {
        armPID.target_set(armPID.target_get() - 300);
        }
        else {
        armPID.target_set(1000);
        }
    }
    else {
        armPID.target_set(armPID.target_get());

    }
}

void controlArmPrime() {
    if  (controlla.get_digital_new_press(BUTTON_ARM_PRIME))   {
        lbDriverIndex = (lbDriverIndex + 1) % (sizeof(lbArray) / sizeof(lbArray[0]));
        armPID.target_set(lbArray[lbDriverIndex]);
    }
}

void controlArmScore()  {
    if  (controlla.get_digital_new_press(BUTTON_ARM_SCORE))   {
        armPID.target_set(ARM_SCORE);
    }
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

void controlArmTask() {
    pros::delay(1000);
    while(true) {
        moveArm(armPID.compute(ROTATION_ARM.get_position()));
        printf("Target: %.2f\n", armPID.target_get());
        printf("LB Value: %d", ROTATION_ARM.get_position());
        pros::delay(ez::util::DELAY_TIME);
    }
}