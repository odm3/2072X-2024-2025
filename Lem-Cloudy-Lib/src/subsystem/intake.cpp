#include "main.h" // IWYU pragma: keep
#include "devices.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/adi.h" // IWYU pragma: keep
#include "pros/rtos.h"
#include "pros/rtos.hpp"

// creates intake variables
bool toggleRingStopper =  LOW;
bool toggleIntakeLift = false;

// sets intake to move at a desiered voltage
void intakeVoltage(int voltage) {
    intake.move_voltage(voltage);
    conveyor.move_voltage(voltage);
}

// moves intake in driver control
void intakeControl() {

if (controlla.get_digital(intakeButton)) {	// if the intake button is pressed, the intake and conveyor button will move forward
	intake.move_voltage(12000);
	conveyor.move_voltage(12000);
    }
else if (controlla.get_digital(intakeReverseButton)) {	// if the intake reverse button is pressed, the intake and conveyor will move backwards
	intake.move_voltage(-12000);
	conveyor.move_voltage(-12000);
    }
else {	// if no buttons are pressed, the intake and conveyor will stop
	intake.move_voltage(0);
	conveyor.move_voltage(0);
    }
}

// sets the intake lift to move up
void intakeLiftUp() {
// intake_lift_left.set_value(true);
// intake_lift_right.set_value(true);
intake_lift.set_value(true);
}

// sets the intake lift to move down
void intakeLiftDown() {
// intake_lift_left.set_value(false);
// intake_lift_right.set_value(false);
intake_lift.set_value(false);
}

// moves the intake lift in driver control
void intakeLiftControl() {

if (controlla.get_digital_new_press(intakeLifTButton)) {
		toggleIntakeLift = !toggleIntakeLift;
	}
    // intake_lift_left.set_value(toggleIntakeLift);
    // intake_lift_right.set_value(toggleIntakeLift);
	intake_lift.set_value(toggleIntakeLift);
}

// sets the ring stopper to up
void ringStopperActivate() {
    ring_stopper.set_value(true);
}

// sets the ring stopper to down
void ringStopperRetract() {
    ring_stopper.set_value(false);
}

// moves the ring stopper in driver control
void ringStopperControl() {
    if (controlla.get_digital_new_press(ringStopperButton)) {
        toggleRingStopper = !toggleRingStopper;
    }
    ring_stopper.set_value(toggleRingStopper);
}

// automation for wall stake loading
void wallStakeLoad() {
	ringStopperControl();
	intakeVoltage(12000);
	if ((toggleRingStopper == HIGH) + conveyor.get_actual_velocity() < 15) {
		intake.move_voltage(12000);
		conveyor.move_voltage(-12000);
		pros::delay(500);
		return;
	}
}