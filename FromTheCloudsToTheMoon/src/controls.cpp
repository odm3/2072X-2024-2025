#include "controls.hpp"
#include "EZ-Template/PID.hpp"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "constants.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/device.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

void moveIntake(int vltg)   {motor_intake.move_voltage(vltg);}  //moves intake at a certain voltage
void armPos(int pos)  {armPid.target_set(pos);} //sets the arm to a certain position

//controls the intake during driver control
void control_intake() {
    if (controlla.get_digital(BUTTON_INTAKE)) { //if the intake button is pressed, move the intake at 12000 voltage
        moveIntake(12000);
    }   else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) {    //if the intake reverse button is pressed, move the intake at -12000 voltage
        moveIntake(-12000);
    }   else {  //if no buttons are pressed, stop the intake
        moveIntake(0);
    }
}

// has the robot wait while a the arm is moving, used for auto
void arm_wait() {
    while (armPid.exit_condition(motor_arm, true) == ez::RUNNING) { //while the arm is moving
        pros::delay(ez::util::DELAY_TIME);  //delay
    }
}

// declares an integer for the prime state
int prime = 0;

// controls the arm during driver control
void control_arm() {

    if (controlla.get_digital(BUTTON_ARM)) {    //if the arm button is pressed, move the arm at 12000 voltage
        armPid.constants_set(0, 0, 0);
        motor_arm.move_voltage(12000);
        armPid.target_set(rotation_arm.get_position());
    }
    else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {   //if the arm reverse button is pressed, move the arm at -12000 voltage
        armPid.constants_set(0, 0, 0);
        motor_arm.move_voltage(-12000);
        armPid.target_set(rotation_arm.get_position());
    }
    else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {   //if the arm prime button is pressed, cycle the arm moving from the down and prime position
        if (prime == 1) {
            armPid.target_set(ARM_DOWN);
            arm_wait();
            prime = 0;
        }   else if (prime == 0) {
            armPid.target_set(ARM_PRIME);
            arm_wait();
            prime = 1;
        }
    }
    // else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {
    //     armStateIndex = (armStateIndex + 1) % (sizeof(armStateArray) / sizeof(armStates[0]));
    //     armPid.target_set(armStateArray[armStateIndex]);
    //     arm_wait();
    // }
    else if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {   //if the arm score button is pressed, move the arm to the score position
        armPid.target_set(ARM_SCORE);
        arm_wait();
    }
    else {  //if no buttons are pressed, stop the arm
        // armPid.target_set(rotation_arm.get_position());  
        armPid.constants_set(armKp, 0, armKd);
    }
}

// controls the pistons during driver control
void control_clamp()   { if (controlla.get_digital_new_press(BUTTON_CLAMP)) { piston_clamp.set(!piston_clamp.get()); } }
void control_lift()    { if (controlla.get_digital_new_press(BUTTON_LIFT)) { piston_lift.set(!piston_lift.get()); } }
void control_doinker_left()  { if (controlla.get_digital_new_press(BUTTON_DOINKER_LEFT)) { piston_doinker_left.set(!piston_doinker_left.get()); } }
void control_doinker_right() { if (controlla.get_digital_new_press(BUTTON_DOINKER_RIGHT)) { piston_doinker_right.set(!piston_doinker_right.get()); } }

// controls the arm in a task
void controlArmTask()   {
    pros::delay(1000);  //delay in the beginning to not interfere with ez-template initialization
    while (true) {      //infinite loop
        motor_arm.move_voltage(armPid.compute(rotation_arm.get_position()));    //move the arm to the target position
        //printing various values to the brain screen
        pros::lcd::print(3, "Angle: %f", IMU.get_rotation());
        pros::lcd::print(4, "Prime: %d", prime);
        pros::lcd::print(5, "Arm Pid value: %d", armPid.target_get());
        pros::lcd::print(6, "Arm Rotation Value %d", rotation_arm.get_position());
        pros::delay(ez::util::DELAY_TIME);  //delay so the v5 cortex doesn't get overloaded
    }
}

//control the clamp in a task
void autoClampTask()  {
    pros::delay(2500); //delay in the beginning to not interfere with ez-template initialization
    while (true) {  //infinite loop
        if (distance_clamp.get_distance() < 37) {   //if the distance sensor reads a distance less than 37, activate the clamp
            piston_clamp.set(true);
            pros::delay(2500);
        }   else {  //if the distance sensor reads a distance greater than 37, deactivate the clamp
            piston_clamp.set(false);
        }
        pros::delay(ez::util::DELAY_TIME);  //delay so the v5 cortex doesn't get overloaded
    }
}

//control the color sorting in a task
void colorSortTask()    {
    pros::delay(1000);  //delay in the beginning to not interfere with ez-template initialization

    while (true) {  //infinite loop

        //if we are allowing red rings to pass
        if (passRed) {
            if ((int)optical_sort.get_hue() >= red1 && (int)optical_sort.get_hue() <= red2 && optical_sort.get_proximity() >= 100) { //if the hue is red and the proximity is greater than 100
                moveIntake(-12000);
            }
        }   
        //if we are allowing blue rings to pass
        else if (!passRed) {
            if ((int)optical_sort.get_hue() >= blue1 && (int)optical_sort.get_hue() <= blue2 && optical_sort.get_proximity() >= 100) { //if the hue is blue and the proximity is greater than 100
                while (true) {
                    if (limitHook.get_value() == LOW) { //if the hook limit switch is pressed, stop the intake
                        moveIntake(-12000);
                        break; 
                    }
                    pros::delay(ez::util::DELAY_TIME);
                }
            }
        }
        //printing various values to the brain screen
        pros::lcd::print(7, "Optical promitiy value: %d", optical_sort.get_proximity());
        // pros::lcd::print(1, "Total Rings: %d", totalRings);
        // pros::lcd::print(2, "Red Rings: %d", redRings);
        // pros::lcd::print(3, "Blue Rings: %d", blueRings);
        pros::delay(ez::util::DELAY_TIME);  //delay so the v5 cortex doesn't get overloaded
    }
}
