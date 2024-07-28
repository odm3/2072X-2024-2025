#include "main.h"
#include <iostream>
#include <string>
#include <type_traits>

//create an autonomous selector using robodash
rd::Selector autoSelector1( {

	{"noAuto",&noAuto},
	{"qualLeft",&qualLeft},
	{"qualLeftEz", &qualLeftEz},
	{"qualRight",&qualRight},
	{"soloAWPLeft",&soloAWPLeft},
	{"soloAWPRight",&soloAWPRight},
	{"elimsLeft",&elimsLeft},
	{"elimsRight",&elimsRight},
	{"Skills", &Skills},
	{"noAuto",&noAuto},
	{"tuneLateral",&tuneLateralLemLib},
	{"tuneAngular",&tuneAngularLemLib},
	{"drive_example", &drive_example},
	{"turn_example", &turn_example},
	{"drive_and_turn", &drive_and_turn},
	{"wait_until_change_speed", &wait_until_change_speed},
	{"swing_example", &swing_example},
	{"motion_chaining", &motion_chaining},
	{"interfered_example", &interfered_example},
	{"intakeforward", &intakeauto}
	}
);

//create a console using robodash
rd::Console(deviceConsole);

// bool isPlugged(int port) {

//     if ((pros::c::get_plugged_type(port) == pros::c::E_DEVICE_UNDEFINED) ||
//         pros::c::get_plugged_type(port) == pros::c::E_DEVICE_NONE) {
//         return false;
//     }
//     else {
//         return true;
//     }
// }

// void checkIfPlugged(int port, std::string deviceName) {
//     if (isPlugged(port) == false) {
//         controlla.rumble("---");
//         controlla.print(0, 0, ("sum aint plugged in yo"));
// 		deviceConsole.focus();
//         deviceConsole.println((deviceName + " not plugged in!").c_str());
//     }
// }

// void checkAllDevices() {
// 	checkIfPlugged(PORT_LF, "LF_motor");
// 	checkIfPlugged(PORT_LM, "LM_motor");
// 	checkIfPlugged(PORT_LB, "LB_motor");
// 	checkIfPlugged(PORT_RF, "RF_motor");
// 	checkIfPlugged(PORT_RM, "RM_motor");
// 	checkIfPlugged(PORT_RB, "RB_motor");
// 	checkIfPlugged(PORT_INTAKE, "intake");
// 	checkIfPlugged(PORT_CONVEYOR, "conveyor");
// 	checkIfPlugged(PORT_ARM, "arm");
// 	checkIfPlugged(PORT_IMU, "IMU");
// 	checkIfPlugged(PORT_INTAKE_LIFT, "intake_lift");
// 	checkIfPlugged(PORT_CLAMP_LEFT, "clamp_left");
// 	checkIfPlugged(PORT_CLAMP_RIGHT, "clamp_right");
// 	checkIfPlugged(PORT_DOINKER, "doinker");
// 	checkIfPlugged(PORT_RING_STOPPER, "ring_stopper");
// 	checkIfPlugged(PORT_ARM_ROTATION, "armRotation");
// 	checkIfPlugged(PORT_CONVEYOR_ROTATION, "conveyorRotation");
// }

// void checkAllDevicesTask() {
// 	while (true) {
	
// 	checkAllDevices();
// 	if (isPlugged(PORT_LF | PORT_LB | PORT_LM | PORT_RF | PORT_RM | PORT_RB |
// 				  PORT_INTAKE | PORT_CONVEYOR | PORT_ARM | PORT_IMU | PORT_INTAKE_LIFT |
// 				  PORT_CLAMP_LEFT | PORT_CLAMP_RIGHT | PORT_DOINKER | PORT_RING_STOPPER |
// 				  PORT_ARM_ROTATION | PORT_CONVEYOR_ROTATION) == false) {
// 		deviceConsole.focus();
// 	}
// 	controlla.rumble("-");
// 	pros::delay(250);

// 	}
// }

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	LemLibChassis.calibrate(false); // calibrate the lem lib chassis without imu
    // calibrate the chassis with imu
    EzTempChassis.opcontrol_curve_sd_initialize();
    EzTempChassis.drive_imu_calibrate(false);
    EzTempChassis.opcontrol_drive_sensors_reset();

	pros::delay(500);

	EzTempChassis.opcontrol_curve_default_set(3);
	EzTempChassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
    EzTempChassis.opcontrol_drive_activebrake_set(activeBreak_kp); // Sets the active brake kP. We recommend 0.1.
    // EzTempChassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
    default_constants(); // Set the drive to your own constants from autons.cpp!

	autoSelector1.focus();

	pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
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
	EzTempChassis.pid_targets_reset();                // Resets PID targets to 0
  	EzTempChassis.drive_imu_reset();                  // Reset gyro position to 0
  	EzTempChassis.drive_sensor_reset();               // Reset drive sensors to 0
  	EzTempChassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);  // Set motors to hold.
	autoSelector1.run_auton();
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
	EzTempChassis.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  	conveyor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	bool toggleClamp = false;
	bool toggleIntakeLift = false;
  	bool toggleDoinker = false;
  	bool toggleRingStopper = false;
  while (true) {
	// PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X))
        EzTempChassis.pid_tuner_toggle();

      // Trigger the selected autonomous routine
      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        	autonomous();
      }

      EzTempChassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

	std::cout << "motor current draw" << conveyor.get_current_draw();

	//drive styles, the uncommented one is which will be used
    EzTempChassis.opcontrol_tank();  // Tank control
    // chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .
    intakeControl();
    armControl();
    intakeLiftControl();
    clampControl();
	doinkerControl();
	ringStopperControl();
	// wallStakeLoad();

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}