#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "subsystems.hpp"
#include "controls.hpp"

void intake_control() {
    if (is_auto) { return; }

    if (controlla.get_digital(BUTTON_INTAKE)) { intake_vltg = 12000; } 
    else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) { intake_vltg = -12000; }   
    else { intake_vltg = 0; }
}

void intake_t() {
    pros::delay(100);
    while (true) {
        intake_control();
        motor_intake.move_voltage(intake_vltg);
        pros::delay(ez::util::DELAY_TIME);
    }
}

#define armKp 2
#define armKd 0
ez::PID armPid(armKp, 0, armKd, 0, "Lady Brown PID");

void armPos(int target) {
    armPid.target_set(target);
}

void arm_control() {
    if (is_auto) { return; }

    else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {
        if (armState == 0) { armPid.target_set(ARM_PRIME1); armState++; }
        else if (armState == 1) { armPos(ARM_PRIME2); armState++; }
        else if (armState == 2) { armPos(ARM_DOWN); armState = 0; }
    }
    else if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {
        armPos(ARM_SCORE);
    }
}

void arm_t() {
    pros::delay(100);
    while (true) {
        if (controlla.get_digital(BUTTON_ARM)) { arm_vltg = 12000; }
        else if (controlla.get_digital(BUTTON_ARM_REVERSE)) { arm_vltg = -12000; }
        else { arm_vltg = 0; }
        // else { arm_vltg = armPid.compute(rotation_arm.get_position()); }
        arm_control();
        motor_arm.move_voltage(arm_vltg);
        pros::lcd::print(3, "rotation state: %d", armState);
        pros::lcd::print(4, "arm rotation value: %f", rotation_arm.get_position());

        pros::delay(ez::util::DELAY_TIME);
    }
}


