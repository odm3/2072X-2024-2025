#include "main.h"
#include "devices.hpp"
#include "devices.hpp"
#include "pros/adi.h"
#include "pros/misc.h"


// using namespace globals;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(8, "I was pressed!");
	} else {
		pros::lcd::clear_line(8);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Haiii :3 - Ansh");
	chassis.calibrate();
	pros::lcd::register_btn1_cb(on_center_button);

	pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(3, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(4, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(5, "Theta: %f", chassis.getPose().theta); // heading
			 // print measurements from the rotation sensors
        	pros::lcd::print(6, "Rotation Sensor: %i", odom_vert_sensor.get_position());
        	pros::lcd::print(7, "Rotation Sensor: %i", odom_hozi_sensor.get_position());
            // delay to save resources
            pros::delay(20);
        }
    });
	

	pros::c::controller_rumble(pros::E_CONTROLLER_MASTER,"-.");

}

//yap
void disabled() {}

//yap
void competition_initialize(
) {}

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
	bool toggleIntakeLift = LOW;
	bool toggleClaw = LOW;

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	conveyor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
			(pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
			(pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs
	
			int leftControl = controlla.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			int rightControl = controlla.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		chassis.tank(leftControl, rightControl, false);

		clamp.set_value(toggleClamp);
		claw.set_value(toggleClaw);
		intake_lift_left.set_value(toggleIntakeLift);
		intake_lift_right.set_value(toggleIntakeLift);

		if (controlla.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move_voltage(12000);
			conveyor.move_voltage(12000);
		}
		else if (controlla.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move_voltage(-12000);
			conveyor.move_voltage(-12000);
		}
		else {
			intake.move_voltage(0);
			conveyor.move_voltage(0);
		}

		if (controlla.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			arm.move_voltage(4500);
		}
		else if (controlla.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			arm.move_voltage(-4500);
		}
		else {
			arm.move_voltage(0);
		}

		if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
			toggleClaw = !toggleClaw;
		}

		if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			toggleIntakeLift = !toggleIntakeLift;
		}

		if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			toggleClamp = !toggleClamp;
		}


	pros::c::delay(25);
	}
}