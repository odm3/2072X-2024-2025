#include "controls.hpp"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "constants.hpp"
#include "main.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"

void moveIntake(int vltg)   {motor_intake.move_voltage(vltg);}
void armPos(int pos)  {armPid.target_set(pos);}

void activate_clamp() {piston_clamp.set(true);}
void activate_lift() {piston_lift.set(true);}
void activate_doinker() {piston_doinker.set(true);}
void deactivate_clamp() {piston_clamp.set(false);}
void deactivate_lift() {piston_lift.set(false);}
void deactivate_doinker() {piston_doinker.set(false);}

void control_intake() {
    if (controlla.get_digital(BUTTON_INTAKE)) {
        moveIntake(12000);
    }   else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) {
        moveIntake(-12000);
    }   else {
        moveIntake(0);
    }
}

void control_arm()  {
    if (controlla.get_digital(BUTTON_ARM)) {

        armPid.target_set(armPid.target_get() + 200);
        //motor_arm.move_voltage(12000);

    }   else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {

        armPid.target_set(armPid.target_get() - 200);
        //motor_arm.move_voltage(-12000);

    }   else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {

        armStateIndex = (armStateIndex + 1) % (sizeof(armStateArray) / sizeof(armStates[0]));
        armPid.target_set(armStateArray[armStateIndex]);

    }   else if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {
            
        armPos(ARM_SCORE);

    }   else {

        armPid.target_set(armPid.target_get());

    }
}

void controlArm()   {
    if (controlla.get_digital(BUTTON_ARM)) {
        if (rotation_arm.get_position() < 22000) {
        armPid.target_set(armPid.target_get() + 500);
        }
        else {
        armPid.target_set(22000);
        }
    }
    else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
        if (rotation_arm.get_position() > 1000) {
        armPid.target_set(armPid.target_get() - 500);
        }
        else {
        armPid.target_set(1000);
        }
    }
    else {
        armPid.target_set(armPid.target_get());

    }
}

void controlArmPrime() {
    if  (controlla.get_digital_new_press(BUTTON_ARM_PRIME))   {
        armStateIndex = (armStateIndex + 1) % (sizeof(armStateArray) / sizeof(armStateArray[0]));
        armPid.target_set(armStateArray[armStateIndex]);
    }
}

void controlArmScore()  {
    if  (controlla.get_digital_new_press(BUTTON_ARM_SCORE))   {
        armPid.target_set(ARM_SCORE);
    }
}

void control_clamp()   {piston_clamp.button_toggle(BUTTON_CLAMP);}
void control_lift()    {piston_lift.button_toggle(BUTTON_LIFT);}
void control_doinker() {piston_doinker.button_toggle(BUTTON_DOINKER);}

void controlArmTask()   {
    pros::delay(2500);
    while (true) {
        motor_arm.move_voltage(armPid.compute(rotation_arm.get_position()));
        pros::delay(ez::util::DELAY_TIME);
    }
}

void autoClampTask()  {
    pros::delay(2500);
    while (true) {
        if (distance_clamp.get_distance() < 37) {
            piston_clamp.set(true);
            pros::delay(2500);
        }   else {
            piston_clamp.set(false);
        }
        pros::delay(ez::util::DELAY_TIME);
    }
}

void colorSortTask()    {
    pros::delay(1000);

    while (true) {

        if (passRed) {
            if ((int)optical_sort.get_hue() >= red1 && (int)optical_sort.get_hue() <= red2) {
                pros::delay(300);
                moveIntake(-12000);
                pros::delay(100);
                moveIntake(12000);
            }
        }   
        else if (!passRed) {
            if ((int)optical_sort.get_hue() >= blue1 && (int)optical_sort.get_hue() <= blue2) {
                pros::delay(300);
                moveIntake(-12000);
                pros::delay(100);
                moveIntake(12000);
            }
        }

        pros::delay(ez::util::DELAY_TIME);
    }
}

//   pros::Task armTask(controlArmTask);
//   pros::Task clampTask(autoClampTask);
//   pros::Task sortTask(colorSortTask);