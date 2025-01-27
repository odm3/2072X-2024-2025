#include "main.h"
#include "drivercontrol.hpp"
#include "devices.hpp"
#include "autons.hpp"
#include "gif-pros/gifclass.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "screen.hpp"
#include "display/lvgl.h" 

// Enter your autons here!
AutonFunction autonFunctions[] = {
    {"Solo Awp (BLUE)", soloAwpBlue},
    {"Solo Awp (RED)", soloAwpRed},
    {"skills", skillsv2},
    {"QUALS Positive side (RED)", positiveSideQualsRed},
    {"QUALS Positive side (BLUE)", positiveSideQualsBlue},
    {"QUALS Negative side (RED)", negativeSideQualsRed},
    {"QUALS Negative side (BLUE)", negativeSideQualsBlue},
    {"SIMPLE Positive side (RED)", positiveSideSimpleRed},
    {"SIMPLE Positive side (BLUE)", positiveSideSimpleBlue},
    {"SAMS POSITIVE side (RED)", samsPositiveSideRed},
    {"SAMS POSITIVE side (BLUE)", samsPositiveSideBlue},
    {"Positive side (RED)", positiveSideRed},
    {"Positive side (BLUE)", positiveSideBlue},
    {"Negative side (RED)", negativeSideRed},
    {"Negative side (BLUE)", negativeSideBlue},
    {"9123 Negative side (RED)", negativeSide9123Red},
    {"9123 Negative side (BLUE)", negativeSide9123Blue},
    {"Solo awp safe (RED)", soloAwpSafeRed},
    {"Solo awp safe (BLUE)", soloAwpSafeBlue},
    {"Nothing", doNothingAuto}
};

// this is needed for LVGL displaying! Do not touch!
size_t autonCount = sizeof(autonFunctions) / sizeof(autonFunctions[0]);

void initialize() {
    pros::delay(750); // Stop the user from doing anything while legacy ports configure.

	// screen init
    calibrationScreenInit();

    calibrateChassis();
    
    autonSelectorScreenInit(
        // your auton funcitons
        autonFunctions, 
        // auton count needed for LVGL displaying
        autonCount, 
        // customizable color scheme, play around with it!
        LV_COLOR_MAKE(0xD2, 0x46, 0x8C)
    );

    chassisInits();

    liftLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    // piston inits
    intakeRaise.set_value(false);
    backClamp.set_value(false);
    doinker.set_value(false);
    ringRush.set_value(false);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
} 

/**
 * Runs after initialize(), and before autonomous when connected to the Field

 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 */
void autonomous() {
    set_drive_to_hold();

    runSelectedAuton(autonFunctions, autonCount);
}

/**
 * Runs the operator control code. This function will be started in its own task
 */
void opcontrol() {
    set_drive_to_coast();

    // task to make sure all motors are plugged in and check the temperature of the drivetrain
    pros::Task motorCheck(checkMotorsAndPrintTemperature);

    bool backClamped = false;
    bool clawUp = false;

	while (true) {
        chassis.opcontrol_tank();

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeRaise.set_value(false);
            doinker.set_value(false);

            liftControl();
        } else {           
            liftAutoControl(-1);
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { intake = 127; doinker.set_value(true); } 
            else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {intake = 127; doinker.set_value(false); }
            else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { intake = -127; doinker.set_value(false); } 
            else { intake = 0; doinker.set_value(false); }   

            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
               backClamp.set_value(true);
            } else {
               backClamp.set_value(false);
            }
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) { motorCheck.suspend(); }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) { liftSensor.reset_position(); }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) { FIRST_RING_LIFT_VALUE += 0.001 * 360 * 100; pros::delay(40); }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) { FIRST_RING_LIFT_VALUE -= 0.001 * 360 * 100; pros::delay(40); }

        ringRush.set_value(false);

		pros::delay(10);
	}
}