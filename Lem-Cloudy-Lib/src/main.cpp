// no longer using this, lvgl issues haha
#include "main.h"
#include "arm.hpp"
#include "autos.hpp"
#include "devices.hpp"
#include "misc.hpp"
#include "pros/adi.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/screen.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  chassis.calibrate();
  armRotation.reset_position();
  clampRetract();
  checkAllDevices();
  //   pros::lcd::initialize();
  pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, "-.");
}
// yap
void disabled() {}

// yap
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  bool toggleClamp = LOW;
  bool toggleDoinker = LOW;
  bool toggleRingStopper = LOW;

  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  conveyor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  while (true) {
    pros::lcd::print(0, "%d %d %d",
                     (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                     (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                     (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >>0); // Prints status of the emulated screen LCDs

    // tank drive {

    int leftControl = controlla.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightControl = controlla.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    // activates tank drive for user control
    chassis.tank(leftControl, rightControl, false);

    // //2 stick arcade drive {
    // int leftY = controlla.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    // int rightX = controlla.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // chassis.arcade(leftY, rightX);
    // //}

    intakeControl();
    armControl();
    intakeLiftControl();
    clampControl();
	  doinkerControl();
	  ringStopperControl();

    pros::c::delay(25);
  }
}
