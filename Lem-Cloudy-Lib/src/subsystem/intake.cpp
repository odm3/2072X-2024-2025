#include "main.h" // IWYU pragma: keep
#include "devices.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/adi.h" // IWYU pragma: keep
#include "pros/rtos.h"
#include "pros/rtos.hpp"

bool toggleRingStopper =  LOW;
bool toggleIntakeLift = false;

void intakeVoltage(int voltage) {
    intake.move_voltage(voltage);
    conveyor.move_voltage(voltage);
}

void intakeControl() {

if (controlla.get_digital(intakeButton)) {
	intake.move_voltage(12000);
	conveyor.move_voltage(12000);
    }
else if (controlla.get_digital(intakeReverseButton)) {
	intake.move_voltage(-12000);
	conveyor.move_voltage(-12000);
    }
else {
	intake.move_voltage(0);
	conveyor.move_voltage(0);
    }
}

void intakeLiftUp() {
// intake_lift_left.set_value(true);
// intake_lift_right.set_value(true);
intake_lift.set_value(true);
}

void intakeLiftDown() {
// intake_lift_left.set_value(false);
// intake_lift_right.set_value(false);
intake_lift.set_value(false);
}

void intakeLiftControl() {

if (controlla.get_digital_new_press(intakeLifTButton)) {
		toggleIntakeLift = !toggleIntakeLift;
	}
    // intake_lift_left.set_value(toggleIntakeLift);
    // intake_lift_right.set_value(toggleIntakeLift);
	intake_lift.set_value(toggleIntakeLift);
}

void ringStopperActivate() {
    ring_stopper.set_value(true);
}

void ringStopperRetract() {
    ring_stopper.set_value(false);
}

void ringStopperControl() {
    if (controlla.get_digital_new_press(ringStopperButton)) {
        toggleRingStopper = !toggleRingStopper;
    }
    ring_stopper.set_value(toggleRingStopper);
}


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