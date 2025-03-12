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

using namespace std;    //using standard namespace

void intakeSet(int vltg) {
    intake_vltg = vltg;
} 

int stuckTime = 0;

void unjam() {
    if (isStuck) {
        int prevIntakeVltg = intake_vltg;
        intake_vltg = -1 * intake_vltg;
        stuckTime += util::DELAY_TIME;
        if (stuckTime >= 500) {
            isStuck = false;
            stuckTime = 0;
            intakeSet(prevIntakeVltg);
        }
    }

    else if (abs(intake_vltg) >= 1000 && motor_intake.get_efficiency() < 10) {
        stuckTime += util::DELAY_TIME;
        if (stuckTime >= 50) {
            isStuck = true;
        }
    }
}

// function for controlling the intake
void intake_control() {
    if (isAuto == true) {return;}    // if in auto, return
    if (wrongColorDetected == true) return; //if the wrong auto is detected, return to let the color sorting function take over
    if (isStuck == true) return;    //if the intake is stuck, return to let the unjamming function take over
    

    else if (controlla.get_digital(BUTTON_INTAKE)) { intakeSet(12000); }  // if intake button is pressed, set intake voltage variable to 12000
    else if (controlla.get_digital(BUTTON_INTAKE_REVERSE)) { intakeSet(-12000); }   // if intake reverse button is pressed, set intake voltage variable to -12000
    else { intake_vltg = 0; }   // if no buttons are pressed, set intake voltage to 0        
}

// task for controlling the intake
void intake_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {          // infinite loop
        unjam();            //checks if the intake is jammed
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
    while (armPid.exit_condition(motor_arm, true) == ez::RUNNING) { //while the arm is running
        pros::delay(ez::util::DELAY_TIME);  //wait
    }
}

// function for controlling the arm ***LEGACY***
void arm_control() {
    if (isAuto) { return; }    // if in auto, return
    else if (controlla.get_digital_new_press(BUTTON_ARM_PRIME)) {   // if the arm prime button is pressed, cycle through the arm states using this code
        if (armState == 0) { armPos(ARM_DOWN); armState++; }       // if the arm state is 0, set the arm position to ARM_PRIME1 and increment the arm state
        else if (armState == 1) { armPos(ARM_PRIME1); armState--; }  // if the arm state is 1, set the arm position to ARM_PRIME2 and increment the arm state
       // else if (armState == 2) { armPos(ARM_DOWN); armState = 0; }  // if the arm state is 2, set the arm position to ARM_DOWN and reset the arm state
    }
    // **OUTDATED**
    // else if (controlla.get_digital_new_press(BUTTON_ARM_SCORE)) {
    //     armPos(18000);
    //     armState = 1;
    // }
}

// task for controlling the arm
void arm_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {    // infinite loop
        if  (reset_switch.get_value() == 1) {   //if the reset switch it pressed
            rotation_arm.set_position(1000);    //set the value to 0 (1000 is used to fix errors with the rotation sensor and negative values)
        }
        if (controlla.get_digital(BUTTON_ARM)) {    //if the button is pressed
            arm_vltg = 12000;                              //the arm will move at max voltage
            arm_wait();                                    //the code will wait until the arm is done to start the next task
            armPos(rotation_arm.get_position());    //the pid will set it's new position to the current one, making the arm vltg and pid not fight each other
            }
        else if (controlla.get_digital(BUTTON_ARM_REVERSE)) {   //same as above, but now reversed
            arm_vltg = -12000;
            arm_wait();
            armPos(rotation_arm.get_position());
        }
        else { arm_vltg = armPid.compute(rotation_arm.get_position()); }
        arm_control();                              // run the arm control function to constantly update the arm voltage variable during driver control
        motor_arm.move_voltage(arm_vltg);  // move the arm motor with the arm voltage variable
         //printing out values to the brain, most don't have to do with the arm but it's nice to have all in one place.
         pros::lcd::print(4, "imu: %f", imu.get_rotation());
         pros::lcd::print(5, "angle: %d", rotation_arm.get_position());
         pros::lcd::print(6, "color prox: %d", optical_sort.get_proximity());
         pros::lcd::print(7, "clamp prox: %d", optical_clamp.get_proximity());

        pros::delay(ez::util::DELAY_TIME);                                    // delay to prevent the v5 cortex from being overworked
    }
}

// function for controlling the pistons
void piston_control() {
    if (isAuto) { return;} // if in auto, return
    //if the buttons for pistons are pressed, toggle the boolean value of the piston state variables
    if (controlla.get_digital_new_press(BUTTON_CLAMP)) { clampState = !clampState; }  
    if (controlla.get_digital_new_press(BUTTON_LIFT)) { liftState = !liftState; }    
    if (controlla.get_digital_new_press(BUTTON_DOINKER_LEFT)) { doinkerLeftState = !doinkerLeftState; }  
    if (controlla.get_digital_new_press(BUTTON_DOINKER_RIGHT)) { doinkerRightState = !doinkerRightState; }
}

// task for controlling the pistons
void piston_t() {
    pros::delay(100);   // small delay to prevent the task from running when ez-temp is initializing
    while (true) {                   // infinite loop
        piston_control();            // run the piston control function to constantly update the piston state variables during driver control
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

void startColorUntil(int rings) {
    colorUntilActivated = true;
    colorUntilRings = rings;
    ringsSeen = 0;
}

void stopColorUntilFunction() {
    colorUntilActivated = false;
}

void doColorSort() {
    if (isRed != true && isRed != false) {  //if an alliance color has not been selected
        ColorLoopActive = false;    //turn off color sort
        return; //dont run anything else
    }
    double redComponent = optical_sort.get_rgb().red;   //returns the R part of current sensed RGB value
    double blueComponent = optical_sort.get_rgb().blue; //returns the B part of current sensed RGB value
    double currentColorDiff = blueComponent - redComponent; //returns the difference of the 2 values
    double currentProximity = optical_sort.get_proximity(); //returns the proximity or distance value
    
    if (currentProximity < ambientProximity) {
        ambientProximity = currentProximity; // calibrate proximity
    }
    if (fabs(currentProximity - ambientProximity) < 5) {
        ambientColorDiff = currentColorDiff;    //calibrates color diff using proximity
    }

    const int PROXIMITY_DIFF_REQUIRED = 100;    //sets the difference from ambient to current proximity to actiavte color sort

    if (controlla.get_digital_new_press(BUTTON_COLOR_SORT)) { ColorLoopActive = !ColorLoopActive; } //toggle the color sort variable if not desired

    if (ColorLoopActive) {  //if the variable is true
        if (currentProximity - ambientProximity > PROXIMITY_DIFF_REQUIRED && !rightRingBeingSeen) { //if a wrong color ring is being sensed
            if (currentColorDiff - ambientColorDiff > 5) { //if a blue ring is sensed when alliance is red
                handleBlueRing();
            } else if (currentColorDiff - ambientColorDiff < -5) { //if a red ring is sensed when allaince is blue
                handleRedRing();
            }
        } else {    
            rightRingBeingSeen = false;
        }
    }

    if (master.get_digital_new_press(BUTTON_COLOR_SORT)) {  //if pressed, the color sort will toggle between on and off, and state is shown on brain screen
        ColorLoopActive = !ColorLoopActive;
        if (ColorLoopActive == true) pros::lcd::set_text(6, "color sort: on");
        if (ColorLoopActive == false) pros::lcd::set_text(6, "color sort: off");
    }
}

//handles blue rings
void handleBlueRing() {
    if (isRed) { // blue ring is wrong color
        //cout << "BLUE DETECTED" << "\n";
        master.rumble(".");
        wrongColorDetected = true;  //stops driver control intake function
        intakeSet(12000);   //set intake to max vltg
        long start = pros::millis();    //start counting from when ring was sensed
        while (optical_sort.get_proximity() > ambientProximity && pros::millis() - start < 125) {   //while the ring is travelling up
            intakeSet(10000);   //set the intake to 10 volts
            pros::delay(10);    //delay to not overwork v5 cortex
        }
        intakeSet(-12000);  //set intake to revese at max vltg
        pros::delay(200);   //wait for 0.2 seconds
        intakeSet(12000);   //set intake to forward speed
        wrongColorDetected = false; //no longer seeing wrong color, resume driver control
    } else {
        handleRightColor(); //if blue ring is the right color then handle as normal
    }
}

//same as above, but for red rings
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

//handles the right color of rights
void handleRightColor() {
    if (colorUntilActivated && !rightRingBeingSeen) {   //if trying to keep ring in intake
        ringsSeen++;
        rightRingBeingSeen = true;
        if (ringsSeen >= colorUntilRings) { //once rings seen has been reached
            intakeSet(-12000);  //reverse to lose momentum
            pros::delay(75);    //wait for 0.075seconds
            intakeSet(0);   //stop intake
            colorUntilActivated = false;
        } else if (safeScoring) {   //prevents scoring while turning for better consistency
            while ((imu.get_heading() - prevHeading) / (pros::millis() - prevTime) > 0.5) {
                intakeSet(0);
                pros::delay(10);
            }
            intakeSet(12000);
        }
    }
}

//task for color sorting
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

// Driver Control Functions
void  setMogoMotors() {
    double curDistance = optical_clamp.get_proximity(); //returns the proximity or distance from the sensor
    int clampColor = optical_clamp.get_hue();   //returns the color of whatever is in front of the clamp

    if (master.get_digital_new_press(BUTTON_CLAMP)) { //if button pressed, toggle clamp state manually
        clampState = !clampState;
    }

    if (autoClampActive == true) {  //if auto clamping is desired
    if (curDistance > AUTOCLAMP_DISTANCE && clampColor <= 75 && clampColor >= 60) { //if an object is within distance and hue matches a goal
        clampState = true;  //make the clamp state true, turning on the clamp
        controlla.rumble(".");  //vibrate the controller
    }
    }  
    else {
    return; //if a goal is not in the sensor, do nothing
    } 
}

//counts down time in driver control for matches
void driverControlCountdown() {
    if (COMPETITION_CONNECTED != true) { return; }  //only run when connected to a compeition field
    
    int totalTime = 105; // 1 minute 45 seconds
    int startTime = pros::millis(); //start counting time

    while (true) {
        int currentTime = pros::millis();
        int elapsedTime = (currentTime - startTime) / 1000; // elapsed time in seconds
        int timeLeft = totalTime - elapsedTime;

        if (timeLeft == 60) {   //when there is a minute left
            controlla.rumble(".");  //vibrate a little
        } else if (timeLeft <= 5 && timeLeft > 0) { //during the last 5 seconds
            controlla.rumble("-");  //continiously vibrate
        } else if (timeLeft <= 0) { //once time is over
            break;  //stop this function
        }

        pros::delay(20);    //little delay to prevent overworking the v5 cortex
    }
}

//checks motors and prints the temperature to the controller
void checkMotorsAndPrintTemperature() {
    std::vector<pros::Motor> motors = {
      motor_LF, motor_LB, motor_LM, motor_RF, motor_RB, motor_RM, motor_intake, motor_arm,
    };

    int totalTime = 105; // 1 minute 45 seconds
    int startTime = pros::millis();

    while (true) {
        double totalTemp = 0.0;
        int count = 0;

        for (auto& motor : motors) {
            double temp = motor.get_temperature();
            if (temp == PROS_ERR_F) { // PROS_ERR_F is returned when the motor is unplugged
                master.set_text(0, 0, "Motor " + std::to_string(motor.get_port()) + " unplugged.");
                pros::delay(250);
                master.rumble("---");   //if motor is unplugged, vibrate controller and say which is unplugged
            }

            if (count < 6) {
                totalTemp += temp;
            }
            ++count;
        }

        if (count == 0) master.set_text(0, 0, "No motors found.");

        double averageTempCelsius = totalTemp / 6;  //get the average temp
        double averageTempFahrenheit = averageTempCelsius * 9.0 / 5.0 + 32.0; //convert to fahrenheit
        master.set_text(0, 0, "Avg Temp: " + std::to_string(averageTempFahrenheit)); //print to controller

        pros::delay(250);
    }
}