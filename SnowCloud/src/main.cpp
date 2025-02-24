#include "main.h"
#include "EZ-Template/auton.hpp"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "constants.hpp"
#include "controls.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

// declares the color sort variables
bool doColorSort = true;
bool isRedAllinace;

// declares the function for the color sorting
void colorSortTask()    {
    pros::delay(1000);
    while (true) {
        if (doColorSort) {
            if ((isRedAllinace && OPTICAL_COLOR.get_hue() >= 90 && OPTICAL_COLOR.get_hue() <= 115)  ||
                (!isRedAllinace && OPTICAL_COLOR.get_hue() >= 10 && OPTICAL_COLOR.get_hue() <= 30)) {
                    // activateDoinker();
                    pros::delay(300);
                    moveIntake(-12000);
                    pros::delay(100);
                    moveIntake(12000);
            }

        }
    }
}

// toggles the color sort function
void controlColorSort() {
    if (controlla.get_digital_new_press(BUTTON_COLOR_SORT)) {
        doColorSort = !doColorSort;
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  EZ_CHASSIS.opcontrol_curve_buttons_toggle(false);  // Enables modifying the controller curve with buttons on the joysticks
  EZ_CHASSIS.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  EZ_CHASSIS.opcontrol_curve_default_set(1, 10);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("Red neg 5 rings", redNeg5rings),
    Auton("Blue neg 5 rings", blueNeg5rings),
    Auton("Solo AWP Left 4 rings", soloAWPLeft4rings),
      // Auton("SoloAwpRedNeg", SoloAwpRedNeg),
      // Auton("Neg Red 2 ring", redNeg2),
      // Auton("Neg Red 3 ring", redNeg3),  
      // Auton("Neg Red 4 ring", redNeg4),
      // Auton("Neg Red 5 ring", redNeg5),
      // Auton("Red goal elims", SoloAwpRedPos),
      // Auton("Blue goal elims", elims),
      // Auton("Neg Blue 2 ring", blueNeg2),
      // Auton("Neg Blue 3 ring", blueNeg3), 
      // Auton("Neg Blue 4 ring", blueNeg4),
      // Auton("Neg Blue 5 ring", blueNeg5),
      // Auton("Goal Rush", goalRush),
      Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      Auton("Example Turn\n\nTurn 3 times.", turn_example),
      // Auton("Skills", skills),
      Auton("LB TESTING", ladyBrownTesting),
      // Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
      // Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
      // Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      // Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      // Auton("Combine all 3 movements", combining_movements),
      // Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  EZ_CHASSIS.initialize();
  LL_CHASSIS.calibrate();
  ez::as::initialize();
  // sets the subsystem motors to their brake modes
  MOTOR_INTAKE.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MOTOR_ARM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  //ROTATION_ARM.reset_position();
  armPID.target_set(ROTATION_ARM.get_position()); // Sets the target to the current position
  // starts all of the tasks
  pros::Task lbTask(controlArmTask);
  pros::Task clampTask(autoClamp_task);
  pros::Task detectTask(detectClamp);
  pros::Task colorSort(colorSortTask);
  // MOTORGROUP_ARM.tare_position();
  master.rumble("_"); // Rumble the controller to let the driver know that the robot is ready
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

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
  EZ_CHASSIS.pid_targets_reset();                // Resets PID targets to 0
  EZ_CHASSIS.drive_imu_reset();                  // Reset gyro position to 0
  EZ_CHASSIS.drive_sensor_reset();               // Reset drive sensors to 0
  EZ_CHASSIS.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  LL_CHASSIS.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);


  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
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
  // Sets the drive motors to coast
  EZ_CHASSIS.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);
  LL_CHASSIS.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);


  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) { // Only run PID Tuner if not in competition
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_LEFT))
        EZ_CHASSIS.pid_tuner_toggle();

      // Trigger the selected autonomous routine
      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)/* && master.get_digital(DIGITAL_UP)*/) {
        autonomous();
          EZ_CHASSIS.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);
          LL_CHASSIS.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
      }

      EZ_CHASSIS.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    // EZ_CHASSIS.opcontrol_tank();  // Tank control
    EZ_CHASSIS.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    //runs the control functions in this infinite loop
    controlIntake();
    controlArm();
    // controlArmManual();
    controlClamp();
    controlDoinker();
    controlLift();
    controlArmPrime();
    controlArmScore();
    //prints various values to the brain screen for debugging
    pros::lcd::print(6, "Rotation Value: %d", ROTATION_ARM.get_position());
    pros::lcd::print(7, "PID target get: %d",armPID.target_get());
    pros::lcd::print(8, "Lady Brown State: %d Value: %d", lbArray[lbDriverIndex], lbDriverIndex);
    // pros::lcd::print(4, "Clamp State: %d", toggleClampInt);

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}