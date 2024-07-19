#include "main.h" // IWYU pragma: keep
#include "devices.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/adi.h" // IWYU pragma: keep

using namespace devices;

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

bool toggleIntakeLift = false;

void intakeLiftControl() {

if (controlla.get_digital_new_press(intakeLifTButton)) {
		toggleIntakeLift = !toggleIntakeLift;
	}
    // intake_lift_left.set_value(toggleIntakeLift);
    // intake_lift_right.set_value(toggleIntakeLift);
	intake_lift.set_value(toggleIntakeLift);
}