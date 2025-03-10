// list of includesa
#include "controls.hpp"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include "liblvgl/llemu.hpp"
#include "main.h"
#include "EZ-Template/util.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

bool wrongColorDetected;

void intakeSet(int vltg) {
    intake_vltg = vltg;
} 

int stuckTime = 0;

void unjam() {
    // if (isStuck) {
    //     int prevIntakeVltg = intake_vltg;
    //     intake_vltg = -1 * intake_vltg;
    //     stuckTime += util::DELAY_TIME;
    //     if (stuckTime >= 500) {
    //         isStuck = false;
    //         stuckTime = 0;
    //         intakeSet(prevIntakeVltg);
    //     }
    // }

    // else if (abs(intake_vltg) >= 1000 && motor_intake.get_actual_velocity() < 10) {
    //     stuckTime += util::DELAY_TIME;
    //     if (stuckTime >= 30) {
    //         isStuck = true;
    //     }
    // }
}

// function for controlling the intake
void intake_control() {
    if (isAuto == true) {return;}    // if in auto, return
    if (wrongColorDetected == true) return;
    if (isStuck == true) return;
    

    else if (controlla.get_digital(BUTTON_INTAKE)) { intakeSet(12000); }  // if intake button is pressed, set intake voltage variable to 12000
    else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) { intakeSet(-12000); }   // if intake reverse button is pressed, set intake voltage variable to -12000
    else { intake_vltg = 0; }   // if no buttons are pressed, set intake voltage to 0        
}

// task for controlling the intake
void intake_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {          // infinite loop
        unjam();
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
        if (armState == 0) { armPos(ARM_DOWN); armState++; }       // if the arm state is 0, set the arm position to ARM_PRIME1 and increment the arm state
        else if (armState == 1) { armPos(ARM_PRIME1); armState--; }  // if the arm state is 1, set the arm position to ARM_PRIME2 and increment the arm state
       // else if (armState == 2) { armPos(ARM_DOWN); armState = 0; }  // if the arm state is 2, set the arm position to ARM_DOWN and reset the arm state
    }
    else if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {
        armPos(18000);
        armState = 1;
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
        if  (reset_switch.get_value() == 1) {
            rotation_arm.set_position(1000);
        }
        if (controlla.get_digital(BUTTON_ARM)) {
            arm_vltg = 12000;
            arm_wait();
            armPos(rotation_arm.get_position());
            }                // if the arm button is pressed, set the arm voltage variable to 12000
        else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {
            arm_vltg = -12000;
            arm_wait();
            armPos(rotation_arm.get_position());
        }  // if the arm reverse button is pressed, set the arm voltage variable to -12000
        //else { arm_vltg = 0; }                                                             // if no buttons are pressed, set the arm voltage variable to 0
        else { arm_vltg = armPid.compute(rotation_arm.get_position()); }
        arm_control_legacy();                                                                      // run the arm control function to constantly update the arm voltage variable during driver control
        motor_arm.move_voltage(arm_vltg);                                          // move the arm motor with the arm voltage variable
        // pros::lcd::print(3, "rotation state: %d", armState);
         pros::lcd::print(4, "imu: %f", imu.get_rotation());
         pros::lcd::print(5, "angle: %d", rotation_arm.get_position());
        // pros::lcd::print(6, "color prox: %d", optical_sort.get_proximity());
        // pros::lcd::print(7, "clamp prox: %d", optical_clamp.get_proximity());

        pros::delay(ez::util::DELAY_TIME);                                    // delay to prevent the v5 cortex from being overworked
    }
}

// // Driver Control Functions

// function for controlling the pistons
void piston_control() {
    if (isAuto) { return;} // if in auto, return
    /* NOT IN USE DUE TO AUTOCLAMP FUNCTION*/
    if (controlla.get_digital_new_press(BUTTON_CLAMP)) { clampState = !clampState; }  // if the clamp button is pressed, toggle the clamp state
    if (controlla.get_digital_new_press(BUTTON_LIFT)) { liftState = !liftState; }    // if the lift button is pressed, toggle the lift state
    if (controlla.get_digital_new_press(BUTTON_DOINKER_LEFT)) { doinkerLeftState = !doinkerLeftState; }  // if the doinker left button is pressed, toggle the doinker left state
    if (controlla.get_digital_new_press(BUTTON_DOINKER_RIGHT)) { doinkerRightState = !doinkerRightState; }  // if the doinker right button is pressed, toggle the doinker right state
}

// task for controlling the pistons
void piston_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {                   // infinite loop
        if (controlla.get_digital_new_press(BUTTON_COLOR_SORT)) { ColorLoopActive = !ColorLoopActive; }  // if the color sort button is pressed, toggle the color sort variable
        piston_control();            // run the piston control function to constantly update the piston states during driver control
        piston_clamp.set(clampState);                   // set the clamp piston to the clamp state
        piston_lift.set(liftState);                     // set the lift piston to the lift state
        piston_doinker_left.set(doinkerLeftState);      // set the doinker left piston to the doinker left state
        piston_doinker_right.set(doinkerRightState);    // set the doinker right piston to the doinker right state
        pros::delay(ez::util::DELAY_TIME);       // delay to prevent the v5 cortex from being overworked
    }
}

void clamp_t() {
    pros::delay(100);
    while (true) {
        setMogoMotors();
        piston_clamp.set(clampState);
        if (clampState == false) {
            pros::delay(500);
        }
        pros::delay(ez::util::DELAY_TIME);
    }
}




using namespace std;

bool ColorLoopActive = false;
bool colorUntilActivated = false;
double ambientColorDiff = 0; // TODO: NEEDS TO BE TUNED AT COMPETITION
double ambientProximity = 60; // TODO: NEEDS TO BE TUNED AT COMPETITION
bool colorLoopStarted = false;
int ringsSeen = 0;
int colorUntilRings = 0;
bool safeScoring = false;
bool rightRingBeingSeen = false;
double prevHeading = 0;
long prevTime = 0;



/**
 * @param rings number of rings to intake until
 */
void startColorUntil(int rings) {
    colorUntilActivated = true;
    colorUntilRings = rings;
    ringsSeen = 0;
}

/**
 * in case you don't want to continue looking for the right ring
 */
void stopColorUntilFunction() {
    colorUntilActivated = false;
}

/**
 * Main color sort loop, features...
 * Autocalibration - calibrates proximity to lowest and calibrates color difference when proximity is normal
 * Color Sort - detects blue and red rings and flings them when wrong color
 * Color Until - intakes until a certain color is seen, then stops and keeps it in intake
 * Safe Scoring - waits until not turning to intake; NOTE: not tested yet, not needed
 * Proximity Detection - detects when ring is gone to reverse intake
 */
void doColorSort() {
    if (isRed != true && isRed != false) {
        return;
    }
    optical_sort.set_led_pwm(100);
    double redComponent = optical_sort.get_rgb().red;
    double blueComponent = optical_sort.get_rgb().blue;
    double currentColorDiff = blueComponent - redComponent;
    double currentProximity = optical_sort.get_proximity();
    
    if (currentProximity < ambientProximity) {
        ambientProximity = currentProximity; // calibrate proximity
    }
    if (fabs(currentProximity - ambientProximity) < 5) {
        ambientColorDiff = currentColorDiff;
    }

    const int PROXIMITY_DIFF_REQUIRED = 100;
    const int PROXIMITY_CUSHION = 0;

    if (ColorLoopActive) {
        if (currentProximity - ambientProximity > PROXIMITY_DIFF_REQUIRED && !rightRingBeingSeen) {
            if (currentColorDiff - ambientColorDiff > 5) { // blue ring
                handleBlueRing();
            } else if (currentColorDiff - ambientColorDiff < -5) { // red ring
                handleRedRing();
            }
        } else {
            rightRingBeingSeen = false;
        }
    }

    if (master.get_digital_new_press(BUTTON_COLOR_SORT)) {
        ColorLoopActive = !ColorLoopActive;
        if (ColorLoopActive == true) pros::lcd::set_text(6, "color sort: on");
        if (ColorLoopActive == false) pros::lcd::set_text(6, "color sort: off");
    }
}

void handleBlueRing() {
    if (isRed) { // wrong color
        cout << "BLUE DETECTED" << "\n";
        master.rumble(". .");
        wrongColorDetected = true;
        intakeSet(12000);
        long start = pros::millis();
        while (optical_sort.get_proximity() > ambientProximity && pros::millis() - start < 125) {
            intakeSet(10000);
            pros::delay(10);
        }
        intakeSet(-12000);
        pros::delay(200);
        intakeSet(12000);
        wrongColorDetected = false;
    } else {
        handleRightColor();
    }
}

void handleRedRing() {
    if (!isRed) { // wrong color
        cout << "RED DETECTED" << "\n";
        master.rumble(". .");
        wrongColorDetected = true;
        intakeSet(12000);
        long start = pros::millis();
        while (optical_sort.get_proximity() > ambientProximity && pros::millis() - start < 125) {
            intakeSet(10000);
            pros::delay(10);
        }
        intakeSet(-12000);
        pros::delay(200);
        intakeSet(12000);
        wrongColorDetected = false;
    } else {
        handleRightColor();
    }
}

void handleRightColor() {
    if (colorUntilActivated && !rightRingBeingSeen) {
        ringsSeen++;
        rightRingBeingSeen = true;
        if (ringsSeen >= colorUntilRings) {
            intakeSet(-12000);
            pros::delay(75);
            intakeSet(0);
            colorUntilActivated = false;
        } else if (safeScoring) {
            while ((imu.get_heading() - prevHeading) / (pros::millis() - prevTime) > 0.5) {
                intakeSet(0);
                pros::delay(10);
            }
            intakeSet(12000);
        }
    }
}

void colorSort_t() {
    while (true) {
        if ((int)armPid.target_get() != ARM_PRIME1) {
            doColorSort();
        }
        prevHeading = imu.get_heading();
        prevTime = pros::millis();
        pros::delay(10);
    }
}

auto mogoTrigger = BUTTON_CLAMP;

const double AUTOCLAMP_DISTANCEREACTIVATE = 50;

const double AUTOCLAMP_DISTANCE = 235;

bool autoClampActivated = false;

bool tempDisableAutoclamp = false;

void clampMogo(bool active) {
    piston_clamp.set(!piston_clamp.get());
}

// Driver Control Functions
void  setMogoMotors() {
    double curDistance = optical_clamp.get_proximity();
    int clampColor = optical_clamp.get_hue();
    // if (piston_clamp.get() == 0 && curDistance > AUTOCLAMP_DISTANCE && autoClampActivated && !tempDisableAutoclamp) { // unclamped and ready to auto clamp
    //     clampState = true;
    //     tempDisableAutoclamp = true;
    // }
    if (master.get_digital_new_press(mogoTrigger)) { // button pressed 
        clampState = !clampState;
    }

    if (autoClampActive == true) {
    if (curDistance > AUTOCLAMP_DISTANCE && clampColor <= 75 && clampColor >= 60) {
        clampState = true;
        controlla.rumble(".");
    }
    }  
    else {
    return;
    } 
}