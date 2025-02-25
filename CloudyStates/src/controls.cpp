// list of includesa
#include "controls.hpp"
#include <cmath>
#include "main.h"
#include "EZ-Template/util.hpp"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

// function for controlling the intake
void intake_control() {
    if (isAuto) { return; }    // if in auto, return
    else if (controlla.get_digital(BUTTON_INTAKE)) { intake_vltg = 12000; }  // if intake button is pressed, set intake voltage variable to 12000
    else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) { intake_vltg = -12000; }   // if intake reverse button is pressed, set intake voltage variable to -12000
    else { intake_vltg = 0; }   // if no buttons are pressed, set intake voltage to 0              
}

// task for controlling the intake
void intake_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {          // infinite loop
        intake_control();   // run the intake control function to constantly update the intake voltage variable during driver control
        motor_intake.move_voltage(intake_vltg);  // move the intake motor with the intake voltage variable
        pros::delay(ez::util::DELAY_TIME);  // delay to prevent the v5 cortex from being overworked
    }
}

// function for setting the arm position
void armPos(int target) {
    armPid.target_set(target);
}

void arm_wait() {
    while (armPid.exit_condition(motor_arm, true) == ez::RUNNING) {
        pros::delay(ez::util::DELAY_TIME);
    }
    }

// function for controlling the arm ***LEGACY***
void arm_control_legacy() {
    if (isAuto) { return; }    // if in auto, return
    else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {   // if the arm prime button is pressed, cycle through the arm states using this code
        if (armState == 0) { armPos(ARM_PRIME1); armState++; }       // if the arm state is 0, set the arm position to ARM_PRIME1 and increment the arm state
        else if (armState == 1) { armPos(ARM_PRIME2); armState++; }  // if the arm state is 1, set the arm position to ARM_PRIME2 and increment the arm state
        else if (armState == 2) { armPos(ARM_DOWN); armState = 0; }  // if the arm state is 2, set the arm position to ARM_DOWN and reset the arm state
    }
    else if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {
        armPos(ARM_SCORE);
        armState = 0;
    }
}

void arm_control() {
    if (isAuto) { return; }    // if in auto, return
    else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) { armPos(ARM_PRIME1); }  // if the arm prime button is pressed, set the arm position to ARM_PRIME1
}

// task for controlling the arm
void arm_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {    // infinite loop
        if (controlla.get_digital(BUTTON_ARM)) {
            arm_vltg = 12000;
            arm_wait();
            armPos(rotation_arm.get_angle());
            }                // if the arm button is pressed, set the arm voltage variable to 12000
        else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
            arm_vltg = -12000;
            arm_wait();
            armPos(rotation_arm.get_angle());
        }  // if the arm reverse button is pressed, set the arm voltage variable to -12000
        //else { arm_vltg = 0; }                                                             // if no buttons are pressed, set the arm voltage variable to 0
        else { arm_vltg = armPid.compute(rotation_arm.get_angle()); }
        arm_control();                                                                      // run the arm control function to constantly update the arm voltage variable during driver control
        motor_arm.move_voltage(arm_vltg);                                          // move the arm motor with the arm voltage variable
        pros::lcd::print(3, "rotation state: %d", armState);
        pros::lcd::print(5, "angle: %d", rotation_arm.get_angle());

        pros::delay(ez::util::DELAY_TIME);                                    // delay to prevent the v5 cortex from being overworked
    }
}

// function for color sorting the rings
void colorSort() {
    if (!runColorSort) { return; }  // if the color sort variable is false, return
    
}

// function for controlling the pistons
void piston_control() {
    if (isAuto) { return;} // if in auto, return
    else if (controlla.get_digital_new_press(BUTTON_CLAMP)) { clampState = !clampState; }  // if the clamp button is pressed, toggle the clamp state
    else if (controlla.get_digital_new_press(BUTTON_LIFT)) { liftState = !liftState; }    // if the lift button is pressed, toggle the lift state
    else if (controlla.get_digital_new_press(BUTTON_DOINKER_LEFT)) { doinkerLeftState = !doinkerLeftState; }  // if the doinker left button is pressed, toggle the doinker left state
    else if (controlla.get_digital_new_press(BUTTON_DOINKER_RIGHT)) { doinkerRightState = !doinkerRightState; }  // if the doinker right button is pressed, toggle the doinker right state
}

// task for controlling the pistons
void piston_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {                   // infinite loop
        if (controlla.get_digital_new_press(BUTTON_COLOR_SORT)) { runColorSort = !runColorSort; }  // if the color sort button is pressed, toggle the color sort variable
        piston_control();            // run the piston control function to constantly update the piston states during driver control
        piston_clamp.set(clampState);                   // set the clamp piston to the clamp state
        piston_lift.set(liftState);                     // set the lift piston to the lift state
        piston_doinker_left.set(doinkerLeftState);      // set the doinker left piston to the doinker left state
        piston_doinker_right.set(doinkerRightState);    // set the doinker right piston to the doinker right state
        pros::delay(ez::util::DELAY_TIME);       // delay to prevent the v5 cortex from being overworked
    }
}

