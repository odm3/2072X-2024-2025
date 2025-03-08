#include "main.h"
#include <type_traits>
#include "autons.hpp"
#include "controls.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"


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

  // Configure your EzChassis controls
  EzChassis.opcontrol_curve_buttons_toggle(false);   // Enables modifying the controller curve with buttons on the joysticks
  EzChassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  EzChassis.opcontrol_curve_default_set(EZ_DRIVE_CURVE_1, EZ_DRIVE_CURVE_2);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // EzChassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // EzChassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    {"Skills", skills},
    {"Awp pos red / neg blue", posAwpRed},
    {"Awp pos blue / neg red", posAwpBlue},
    {"3 pos red / neg blue", pos3red},
    {"3 pos blue / neg red", pos3blue},
    {"4 pos red / neg blue", pos4red},
    {"4 pos blue / neg red", pos4blue},
      // {"Drive\n\nDrive forward and come back", drive_example},
      // {"Turn\n\nTurn 3 times.", turn_example},
      // {"Drive and Turn\n\nDrive forward, turn, come back", drive_and_turn},
      // {"Drive and Turn\n\nSlow down during drive", wait_until_change_speed},
      // {"Swing Turn\n\nSwing in an 'S' curve", swing_example},
      // {"Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining},
      // {"Combine all 3 movements", combining_movements},
      // {"Interference\n\nAfter driving forward, robot performs differently if interfered or not", interfered_example},
      // {"Simple Odom\n\nThis is the same as the drive example, but it uses odom instead!", odom_drive_example},
      // {"Pure Pursuit\n\nGo to (0, 30) and pass through (6, 10) on the way.  Come back to (0, 0)", odom_pure_pursuit_example},
      // {"Pure Pursuit Wait Until\n\nGo to (24, 24) but start running an intake once the robot passes (12, 24)", odom_pure_pursuit_wait_until_example},
      // {"Boomerang\n\nGo to (0, 24, 45) then come back to (0, 0, 0)", odom_boomerang_example},
      // {"Boomerang Pure Pursuit\n\nGo to (0, 24, 45) on the way to (24, 24) then come back to (0, 0, 0)", odom_boomerang_injected_pure_pursuit_example},
      // {"Measure Offsets\n\nThis will turn the robot a bunch of times and calculate your offsets for your tracking wheels.", measure_offsets},
  });

  // Initialize EzChassis and auton selector
  EzChassis.initialize();
  //LLCHASSIS.calibrate(false);
  ez::as::initialize();

  //  
  // if (rotation_arm.get_position() <= -350000) {
  //   rotation_arm.set_position(rotation_arm.get_position() + 360);
  // }
  motor_intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);     //sets intake motor to coast and not resist external movement
  motor_arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);         //sets arm motor to hold to resist against gravity and other robots
  rotation_arm.set_reversed(true);
  optical_clamp.set_integration_time(10);                     // sets the integration time of the optical sensor to 10ms
  optical_sort.set_integration_time(5);                      // sets the integration time of the optical sensor to 10ms
  optical_clamp.set_led_pwm(100);                            // sets the led brightness of the optical sensor to 100%
  optical_sort.set_led_pwm(100);                             // sets the led brightness of the optical sensor to 100%

  pros::Task arm_task(arm_t);                            // starts the arm task
  pros::Task intake_task(intake_t);                      // starts the intake task
  pros::Task piston_task(piston_t);                      // starts the piston task
  // pros::Task temp_task(checkTempAndPorts);                     // starts the temperature task
  pros::Task sort_task(colorSort_t);                    // starts the color sort task
  pros::Task clamp_task(clamp_t);                        // starts the clamp task

  controlla.rumble(EzChassis.drive_imu_calibrated() ? "." : "---");
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
  isAuto = true;
  EzChassis.pid_targets_reset();                // Resets PID targets to 0
  EzChassis.drive_imu_reset();                  // Reset gyro position to 0
  EzChassis.drive_sensor_reset();               // Reset drive sensors to 0
  EzChassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  EzChassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (EzChassis.odom_enabled() && !EzChassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(EzChassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(EzChassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(EzChassis.odom_theta_get()),
                           1);  // Don't override the top Page line

          // Display all trackers that are being used
          screen_print_tracker(EzChassis.odom_tracker_left, "l", 4);
          screen_print_tracker(EzChassis.odom_tracker_right, "r", 5);
          screen_print_tracker(EzChassis.odom_tracker_back, "b", 6);
          screen_print_tracker(EzChassis.odom_tracker_front, "f", 7);
        }
      }
    }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);

/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      EzChassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = EzChassis.drive_brake_get();
      autonomous();
      EzChassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    EzChassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (EzChassis.pid_tuner_enabled())
      EzChassis.pid_tuner_disable();
  }
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
  // Set isAuto to false to allow for user control
  isAuto = false;
  ColorLoopActive = true;
  // Sets the motors to coast when not in autonomous for smoother driving and protecting motors
  EzChassis.drive_brake_set(MOTOR_BRAKE_COAST);

  while (true) {
    // Gives you some extras to make EZ-Template ezier
    //ez_template_extras();

    //EzChassis.opcontrol_tank();  // Activates tank controls
    EzChassis.opcontrol_arcade_standard(ez::SPLIT);   // Activates arcade control


    pros::delay(ez::util::DELAY_TIME);  // Delay to prevent the v5 cortex from being overworked
  }
}
