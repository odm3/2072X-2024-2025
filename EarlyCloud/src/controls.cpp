#include "controls.hpp"
#include "EZ-Template/util.hpp"
#include "devices.hpp"
#include "main.h"// IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

bool toggleRingStopper =  false;
bool toggleIntakeLift = false;
bool toggleClamp = false;
bool toggleDoinker = false;

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

void ringStopperActivate() {
    ring_stopper.set_value(true);
}

void ringStopperRetract() {
    ring_stopper.set_value(false);
}

void clampActivate() {
    // clamp_left.set_value(true);
    // clamp_right.set_value(true);
    clamp_left.set_value(true);
    clamp_right.set_value(true);
}

void clampRetract() {
    // clamp_left.set_value(false);
    // clamp_right.set_value(false);
    clamp_left.set_value(false);
    clamp_right.set_value(false);
}

void doinkerActivate() {
    doinker.set_value(true);
}

void doinkerRetract() {
    doinker.set_value(true);
}

double conveyorStuckCurrent = 10000000; //placeholder

void intakeVoltage(int voltage) {
    intake.move_voltage(voltage);
    conveyor.move_voltage(voltage);

    if (conveyor.get_current_draw() > conveyorStuckCurrent) {
        conveyor.move_voltage(-12000);
    }
    else {
        return;
    }
}


void armVoltage(int Voltage) {
    arm.move_voltage(Voltage);
}

void armToZero() {
    while (armRotation.get_position() != 0) {
     armVoltage(-12000);
    }
}

void armToIntakeLifted() {
    while (armRotation.get_position() != 60) {
    armVoltage(12000);
    }
}

void armToScoreUp() {
    while (armRotation.get_position() != 180) {
     armVoltage(12000);
    }
}

void armToScoreDown() {
    while (armRotation.get_position() != 60) {
        armVoltage(-12000);
    }
}

void armControlSpecific(double targetPos) {
    
    double currentPos = armRotation.get_position();
    double error = targetPos - currentPos;
    int armPower = error * arm_kp;

    while (error > 5) {
        arm.move(armPower);
    }

    armVoltage(0);

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
else if (conveyor.get_current_draw() > conveyorStuckCurrent) {
    conveyor.move_voltage(-12000);
}
else {
	intake.move_voltage(0);
	conveyor.move_voltage(0);
    }
}

void intakeLiftControl() {

if (controlla.get_digital_new_press(intakeLifTButton)) {
		toggleIntakeLift = !toggleIntakeLift;
	}
    // intake_lift_left.set_value(toggleIntakeLift);
    // intake_lift_right.set_value(toggleIntakeLift);
	intake_lift.set_value(toggleIntakeLift);
}

void ringStopperControl() {
    if (controlla.get_digital_new_press(ringStopperButton)) {
        toggleRingStopper = !toggleRingStopper;
    }
    ring_stopper.set_value(toggleRingStopper);
}

void clampControl() {
    if (controlla.get_digital_new_press(clampButton)) {
    toggleClamp = !toggleClamp;
    }
    // clamp_left.set_value(toggleClamp);
    // clamp_right.set_value(toggleClamp);
    clamp_left.set_value(toggleClamp);
    clamp_right.set_value(toggleClamp);
}

void doinkerControl() {
    if (controlla.get_digital_new_press(doinkerButton)) {
        toggleDoinker = !toggleDoinker;
    }
    doinker.set_value(toggleDoinker);
}

void armControl() {
    if (controlla.get_digital(ArmUpButton)) {
        arm.move_voltage(12000);
        
    }
    else if (controlla.get_digital(ArmDownButton)) {
        arm.move_voltage(-12000);
    }
    else {
        arm.move_voltage(0);
    }
}

void wallStakeLoad() {
	intakeVoltage(12000);
	if ((toggleRingStopper == true) + conveyor.get_actual_velocity() < 15) {
		intake.move_voltage(12000);
		conveyor.move_voltage(-12000);
		pros::delay(500);
		return;
	}
}