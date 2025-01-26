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

void moveIntake(int vltg)   {motor_intake.move_voltage(vltg);}
void armPos(int pos)  {armPid.target_set(pos);}

void control_intake() {
    if (controlla.get_digital(BUTTON_INTAKE)) {
        moveIntake(12000);
    }   else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) {
        moveIntake(-12000);
    }   else {
        moveIntake(0);
    }
}

void arm_wait() {
    while (armPid.exit_condition(motor_arm, true) == ez::RUNNING) {
        pros::delay(ez::util::DELAY_TIME);
    }
}
    int prime = 0;

void control_arm() {

    if (controlla.get_digital(BUTTON_ARM)) {
        armPid.constants_set(0, 0, 0);
        motor_arm.move_voltage(12000);
        armPid.target_set(rotation_arm.get_position());
    }
    else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
        armPid.constants_set(0, 0, 0);
        motor_arm.move_voltage(-12000);
        armPid.target_set(rotation_arm.get_position());
    }
    else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {
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
    else if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {
        armPid.target_set(ARM_SCORE);
        arm_wait();
    }
    else {
        // armPid.target_set(rotation_arm.get_position());
        armPid.constants_set(armKp, 0, armKd);
    }
}

// void control_arm()  {
//     if (controlla.get_digital(BUTTON_ARM)) {
//         armPid.target_set(armPid.target_get() + 200);
//         //motor_arm.move_voltage(12000);
//     }   if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
//         armPid.target_set(armPid.target_get() - 200);
//         //motor_arm.move_voltage(-12000);
//     }   if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {
//         armStateIndex = (armStateIndex + 1) % (sizeof(armStateArray) / sizeof(armStates[0]));
//         armPid.target_set(armStateArray[armStateIndex]);
//     }   if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {          
//         armPos(ARM_SCORE);
//     }   
//         armPid.target_set(armPid.target_get());
// }

// void controlArm()   {
//     if (controlla.get_digital(BUTTON_ARM)) {
//         if (rotation_arm.get_position() < 24000) {
//         armPid.target_set(armPid.target_get() + 500);
//         }
//         else {
//         armPid.target_set(22000);
//         }
//     }
//     else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
//         if (rotation_arm.get_position() > 1000) {
//         armPid.target_set(armPid.target_get() - 500);
//         }
//         else {
//         armPid.target_set(1000);
//         }
//     }
//     else {
//         armPid.target_set(armPid.target_get());
//     }
// }

// void controlArmPrime() {
//     if  (controlla.get_digital_new_press(BUTTON_ARM_PRIME))   {
//         armStateIndex = (armStateIndex + 1) % (sizeof(armStateArray) / sizeof(armStateArray[0]));
//         armPid.target_set(armStateArray[armStateIndex]);
//     }
// }

// void controlArmScore()  {
//     if  (controlla.get_digital_new_press(BUTTON_ARM_SCORE))   {
//         armPid.target_set(ARM_SCORE);
//     }
// }

void control_clamp()   { if (controlla.get_digital_new_press(BUTTON_CLAMP)) { piston_clamp.set(!piston_clamp.get()); } }
void control_lift()    { if (controlla.get_digital_new_press(BUTTON_LIFT)) { piston_lift.set(!piston_lift.get()); } }
void control_doinker_left()  { if (controlla.get_digital_new_press(BUTTON_DOINKER_LEFT)) { piston_doinker_left.set(!piston_doinker_left.get()); } }
void control_doinker_right() { if (controlla.get_digital_new_press(BUTTON_DOINKER_RIGHT)) { piston_doinker_right.set(!piston_doinker_right.get()); } }

void controlArmTask()   {
    pros::delay(1000);
    while (true) {
        motor_arm.move_voltage(armPid.compute(rotation_arm.get_position()));
        pros::lcd::print(3, "angle: %f", IMU.get_rotation());
        pros::lcd::print(4, "prime: %d", prime);
        pros::lcd::print(5, "Arm Pid value: %d", armPid.target_get());
        pros::lcd::print(6, "Arm Rotation Value %d", rotation_arm.get_position());
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

        //if we are allowing red rings to pass
        if (passRed) {
            if ((int)optical_sort.get_hue() >= red1 && (int)optical_sort.get_hue() <= red2 && optical_sort.get_proximity() >= 100) {
                moveIntake(-12000);

            }
        }   
        //if we are allowing blue rings to pass
        else if (!passRed) {
            if ((int)optical_sort.get_hue() >= blue1 && (int)optical_sort.get_hue() <= blue2 && optical_sort.get_proximity() >= 100) {
                while (true) {
                    if (limitHook.get_value() == LOW) {
                        moveIntake(-12000);
                        break; 
                    }
                    pros::delay(ez::util::DELAY_TIME);
                }
            }
        }
        pros::lcd::print(7, "Optical promitiy value: %d", optical_sort.get_proximity());
        // pros::lcd::print(1, "Total Rings: %d", totalRings);
        // pros::lcd::print(2, "Red Rings: %d", redRings);
        // pros::lcd::print(3, "Blue Rings: %d", blueRings);
        pros::delay(ez::util::DELAY_TIME);
    }
}
