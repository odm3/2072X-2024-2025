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
    // else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
    //     moveArm(-12000);
    // }
    else {
        moveArm(0);
    }
}

void controlArmStates() {
    // if  (controlla.get_digital_new_press(BUTTON_ARM_REVERSE))   {
    //     armPID.target_set(100);
    // }
    // while (ROTATION_ARM.get_position() != 0) {
    //     MOTORGROUP_ARM.move(armPID.compute(ROTATION_ARM.get_position()));
    //     pros::delay(ez::util::DELAY_TIME);
    // }

    if(controlla.get_digital(BUTTON_ARM_REVERSE)) {
        armPID.target_set(500);
    } else if(controlla.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
        armPID.target_set(0);

    }

    double angle = 0.0;
    double error = MOTORGROUP_ARM.get_position() - armPID.target_get();
    pros::lcd::print(4,"Rotation Value: %.2f", MOTORGROUP_ARM.get_position());
    pros::lcd::print(5, "PID Value: %.2f", armPID.target_get());
    pros::lcd::print(6, "Computed Value: %.2f", fabs(armPID.compute(MOTORGROUP_ARM.get_position())));
    pros::lcd::print(7, "Computed Error: %.2f", fabs(armPID.compute_error(error, MOTORGROUP_ARM.get_position() )));
    MOTORGROUP_ARM.move(armPID.compute_error(error, MOTORGROUP_ARM.get_position()));
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