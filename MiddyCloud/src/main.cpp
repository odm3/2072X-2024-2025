#include "main.h"

//create an autonomous selector using robodash for compitiion paths
rd::Selector autoSelector1( {
	{"redPos", &redPos},
	}
);

rd::Console(mainConsole);




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//the following 4 commands calibrate both the LemLib and EzTemp chassis'
	EzTempChassis.drive_imu_calibrate();
	LemLibChassis.calibrate(false); 
    EzTempChassis.opcontrol_curve_sd_initialize();
    EzTempChassis.opcontrol_drive_sensors_reset();

	pros::delay(500); //a wait time of 500ms so the user cannot do anything while the chassis' are initializing

	mainConsole.focus();
	EzTempChassis.opcontrol_curve_default_set(3, 3); 		//Drive curve so the user can have better control in driver control
	EzTempChassis.opcontrol_curve_buttons_toggle(false); // Disables modifying the controller curve with buttons
    // EzTempChassis.opcontrol_drive_activebrake_set(activeBreak_kp); // Sets the active brake kP
    default_constants(); // Set the drive to your my constants from autons.cpp

	// autoSelector1.focus(); //makes the compition auton selector prioritized to select before a match

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
	EzTempChassis.pid_targets_reset();                					// Resets PID targets to 0
  	EzTempChassis.drive_imu_reset();                					  // Reset gyro position to 0
  	EzTempChassis.drive_sensor_reset();              					 // Reset drive sensors to 0
  	EzTempChassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);  // Set motors to hold for EzTemp
	LemLibChassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);			  // Set motors to hold for LemLib
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
	MotorIntakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	MotorIntakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	
	// PID/Auton Tuner
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID/Auton Tuner
      // When enabled:
      // * use A and Y to increment / decrement the constants
      // * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X))
        EzTempChassis.pid_tuner_toggle();

      // Trigger the selected autonomous routine
      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        autonomous();
        // EzTempChassis.drive_brake_set(driver_preference_brake);
      }

      EzTempChassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

	while (true) {

		// get the pose of the chassis
		lemlib::Pose Cpose = LemLibChassis.getPose();

		// PID Tuner / Auton Tester
    	if (!pros::competition::is_connected()) {
      		// Enable / Disable PID Tuner
      		// When enabled:
      		// * use A and Y to increment / decrement the constants
      		// * use the arrow keys to navigate the constants
      		if (master.get_digital_new_press(DIGITAL_X))
        	EzTempChassis.pid_tuner_toggle();

      		// Trigger the selected autonomous routine
      		if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
        		autonomous();
        		// EzTempChassis.drive_brake_set(driver_preference_brake);
      }

      EzTempChassis.pid_tuner_iterate();  // Allow PID Tuner to iterate

    }

		//drive chassis styles whichever is uncommented is active
		EzTempChassis.opcontrol_tank();
		// EzTempChassis.opcontrol_arcade_standard(ez::SINGLE);
		// EzTempChassis.opcontrol_arcade_standard(ez::SPLIT);

		//controls functions from controls.cpp/.hpp which let the user control all devices in opcontrol
		controlIntake();
		controlArm();
		controlIntakeLift();
		controlClamp();
		controlHammer();
		controlHang();

		  	if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))	{
			
		// print the x, y, and theta values of the pose
			mainConsole.printf("X: %f, Y: %f, Theta: %f\n", Cpose.x, Cpose.y, Cpose.theta);
		}

					else if (controlla.get_digital(pros::E_CONTROLLER_DIGITAL_R2))	{
				LemLibChassis.resetLocalPosition();
				intertialIMU.tare();
				mainConsole.clear();
			}

		pros::delay(ez::util::DELAY_TIME);                               // Run for 20 ms then update
	}
}