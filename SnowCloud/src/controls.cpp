#include <cstddef>
#include "EZ-Template/util.hpp"
#include "constants.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/rotation.h"
#include "pros/rtos.hpp"

// declares the subsystem control variables
bool toggleClamp     = false;
bool toggleDoinker   = false;
bool toggleLift      = false;
bool toggleHang      = false;
bool toggleArmStates = false;
int lbDriverIndex = 0; 
// declares an array for the arm
int lbArray [2] = { ARM_DOWN, ARM_PRIME};

// moves the intake at a specified voltage
void moveIntake(double vltg)    {
    MOTOR_INTAKE.move_voltage(vltg);
}

// moves the arm at a specified voltage
void moveArm(double vltg)  {
    // MOTORGROUP_ARM.move_voltage(vltg);
    MOTOR_ARM.move_voltage(vltg);
}

// activates the clamp
void activateClamp()    {
    toggleClamp = true;
    PISTON_CLAMP.set_value(toggleClamp);
    pros::delay(150);
}

// deactivates the clamp
void deactivateClamp()  {
    toggleClamp = false;
    PISTON_CLAMP.set_value(toggleClamp);
    pros::delay(150);
}

// activates the doinker
void activateDoinker()    {
    toggleDoinker = true;
    PISTON_DOINKER.set_value(toggleDoinker);
}

// deactivates the doinker
void deactivateDoinker()  {
    toggleDoinker = false;
    PISTON_DOINKER.set_value(toggleDoinker);
}

// activates the lift
void activateLift()    {
    toggleLift = true;
    PISTON_LIFT.set_value(toggleLift);
}

// deactivates the lift
void deactivateLift()  {
    toggleLift = false;
    PISTON_LIFT.set_value(toggleLift);
}
// controls the intake in driver control
void controlIntake()    {
    if (controlla.get_digital(BUTTON_INTAKE)) { // if the button is being pressed, the intake will move forward at max voltage
        moveIntake(12000);
    }
    else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) { // if the button is being pressed, the intake will move backwards at max voltage
        moveIntake(-12000);
    }
    else {
        moveIntake(0); // else the intake will not move
    }
}
// controls the arm in driver control manually
void controlArmManual() {
    if (controlla.get_digital(BUTTON_ARM)) {        // if the button is being pressed, the arm will move forward at max voltage
        moveArm(120000);
    }
    else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {   // if the button is being pressed, the arm will move backwards at max voltage
        moveArm(-12000);
    }
    else {
        moveArm(0);     // else the arm will not move
    }
}
// controls the arm in driver control
void controlArm()   {
    if (controlla.get_digital(BUTTON_ARM)) {        // if the button is being pressed, the arm will move up until 22,000 centidegrees, then no more
        if (ROTATION_ARM.get_position() < 22000) {          
        armPID.target_set(armPID.target_get() + 200);
        }
        else {
        armPID.target_set(22000);
        }
    }
    else if (controlla.get_digital(BUTTON_ARM_REVERSE)) { // if the button being pressed, the arm will move down to 1000 centidegrees, then no more
        if (ROTATION_ARM.get_position() > 1000) {
        armPID.target_set(armPID.target_get() - 200);
        }
        else {
        armPID.target_set(1000);
        }
    }
    else {                                                      // else the arms target will be set to the current position
        armPID.target_set(armPID.target_get());

    }
}

// controls the arm priming
void controlArmPrime() {
    if  (controlla.get_digital_new_press(BUTTON_ARM_PRIME))   { // if the button is pressed, the arm cycle through priming positions
        lbDriverIndex = (lbDriverIndex + 1) % (sizeof(lbArray) / sizeof(lbArray[0]));
        armPID.target_set(lbArray[lbDriverIndex]);
    }
}

// controls the arm scoring
void controlArmScore()  {
    if  (controlla.get_digital_new_press(BUTTON_ARM_SCORE))   { // if the button is pressed, the arm will move to the score position
        armPID.target_set(ARM_SCORE);
    }
}

// controls the doinker
void controlDoinker() { 
    if (controlla.get_digital_new_press(BUTTON_DOINKER)) {  // if the button is pressed, the doinker will toggle
        toggleDoinker = !toggleDoinker;
    }   PISTON_DOINKER.set_value(toggleDoinker);
}

// controls the lift
void controlLift() {
    if (controlla.get_digital_new_press(BUTTON_LIFT)) {   // if the button is pressed, the lift will toggle
        toggleLift = !toggleLift;
    }   PISTON_LIFT.set_value(toggleLift);
}

// controls the arm in a task
void controlArmTask() {
    pros::delay(1000);
    while(true) {
        moveArm(armPID.compute(ROTATION_ARM.get_position()));   // moves the arm at the computed value
        // prints various values to the brain screen for debugging
        printf("Target: %.2f\n", armPID.target_get());
        printf("LB Value: %d", ROTATION_ARM.get_position());
        pros::delay(ez::util::DELAY_TIME);
    }
}

// controls the clamp
void controlClamp() {
    if (controlla.get_digital_new_press(BUTTON_CLAMP)) {    // if the button is pressed, the clamp will toggle
        toggleClamp = !toggleClamp;
    }
}

// controls the clamp in a task
void autoClamp_task()   {
    pros::delay(1000);  // delay to prevent the clamp from activating immediately
    while (true) {  
        PISTON_CLAMP.set_value(toggleClamp);    // sets the value of the clamp to the boolean value
        pros::delay(ez::util::DELAY_TIME);
    }
}

// detects the clamp
void detectClamp()   {
    pros::delay(1000);  // delay to prevent the clamp from activating immediately
    while(true) {   // if the distance sensor detects an object within 37ms, the clamp will activate
        if (DISTANCE_AUTO_CLAMP.get_distance() <= 37) {
            pros::delay(100);
            toggleClamp = true;
            pros::delay(2500);
        }
        pros::delay(ez::util::DELAY_TIME);
    }
}

// sets the integer value of the toggleclamp from the boolean value
int toggleClampInt()    {
    if (toggleClamp == true) {  // if the clamp is toggled, the integer value will be 1
        return 1;
    }
    if (toggleClamp == false) { // if the clamp is not toggled, the integer value will be 0
        return 0;
    }
}