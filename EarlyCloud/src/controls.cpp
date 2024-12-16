#include "controls.hpp"
#include "EZ-Template/PID.hpp"
#include "EZ-Template/util.hpp"
#include "devices.hpp"
#include "main.h"// IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "timer.h"
#include <utility>


//inits all variables for pistons as false/not activate 
bool toggleRingStopper =  false;
bool toggleIntakeLift = false;
bool toggleClamp = false;
bool toggleDoinker = false;

//lifts the intake up
void intakeLiftUp() {
intake_lift.set_value(true);
toggleIntakeLift = true;
}

//lifts the intake down
void intakeLiftDown() {
intake_lift.set_value(false);
toggleIntakeLift = false;
}

//activates the ring stopper
void ringStopperActivate() {
    ring_stopper.set_value(true);
    toggleRingStopper = true;
}

//retracts the ring stopper
void ringStopperRetract() {
    ring_stopper.set_value(false);
    toggleRingStopper = false;
}

//activates the clamp
void clampActivate() {
    clamp_left.set_value(true);
    clamp_right.set_value(true);
    toggleClamp = true;
}

//retracts the clamp
void clampRetract() {
    clamp_left.set_value(false);
    clamp_right.set_value(false);
    toggleClamp = false;
}

//activates the doinker
void doinkerActivate() {
    doinker.set_value(true);
}

//retracts the doinker
void doinkerRetract() {
    doinker.set_value(true);
}

/*placeholder current value for conveyor getting stuck, if current is above this value,
the conveyor will reverse for a certain amount of time*/
double conveyorStuckCurrent = 10000000;

//moves the intake and conveyor with a specific desired voltage
void intakeVoltage(int voltage) {
    intake.move_voltage(voltage);
    conveyor.move_voltage(voltage);

    if (conveyor.get_torque() > conveyorStuckCurrent) {
        conveyor.move_voltage(-12000);
        pros::delay(500);
    }
    else {
        return;
    }
}

void intakeVoltage1(int voltage) {
    if (((conveyor.get_torque() > 0.45) && (conveyor.get_direction() == 1))) {
        double et = timer.getElapsedTimeMS();
        while (timer.getElapsedTimeMS() - et < 500) {
            conveyor.move_voltage(-12000);
        }
    }
    else {
    intake.move_voltage(voltage);
    conveyor.move_voltage(voltage);
    }
}

//  || ((conveyor.get_torque() > 0.30) && (conveyor.get_direction() == 1) && (toggleRingStopper == true))

//moves the arm motor using a specific desired voltage
void armVoltage(int Voltage) {
    arm.move_voltage(Voltage);
}

double ARM_POS_ZERO = 0;
double ARM_POS_ALLIANCE = 60;
double ARM_POS_WALL = 180;


/*WORK IN PROGRESS*/
//moves the arm to base position
void armToZero() {
    while (armRotation.get_position() != ARM_POS_ZERO) {
    if (armRotation.get_position() > ARM_POS_ZERO) {
            armVoltage(-12000);
        }
    else if (armRotation.get_position() < ARM_POS_ZERO) {
            armVoltage(12000);
        }
    }
}

/*WORK IN PROGRESS*/
//moves arm to the alliance stake position with values from the arm rotation sensor
void armToAllianceStake() {
    while (armRotation.get_position() != ARM_POS_ALLIANCE) {
        if (armRotation.get_position() > ARM_POS_ALLIANCE) {
            armVoltage(-12000);
        }
        else if (armRotation.get_position() < ARM_POS_ALLIANCE) {
            armVoltage(12000);
        }
    }
}

/*WORK IN PROGRESS*/
//moves arm to the wall stake position with values from the arm rotation sensor
void armToWallStake() {
    while (armRotation.get_position() != ARM_POS_WALL) {
    if (armRotation.get_position() > ARM_POS_WALL) {
            armVoltage(-12000);
        }
    else if (armRotation.get_position() < ARM_POS_WALL) {
            armVoltage(12000);
        }
    }
}

void setArm(double input) {
    arm.move(input);
}

ez::PID armPID{arm_kp, 0, 0, 0, {"armpid"}};

void armWait() {
    while (armPID.exit_condition(arm, true) == ez::RUNNING) {
        pros::delay(ez::util::DELAY_TIME);
    }
}

void arm_task() {
    pros::delay(4000);
    while (true) {
        setArm(armPID.compute(armRotation.get_position()));
    }
}

// pros::Task armTask(arm_task);

//controls for intake and conveyor during driverControl
void intakeControl() {

if (controlla.get_digital(intakeButton)) {
	intakeVoltage(12000);
    }
else if (controlla.get_digital(intakeReverseButton)) {
	intakeVoltage(-12000);
    }
else {
	intakeVoltage(0);
    }
}

//controls for the intake lift during driverControl
void intakeLiftControl() {

if (controlla.get_digital_new_press(intakeLifTButton)) {
		toggleIntakeLift = !toggleIntakeLift;
	}
    // intake_lift_left.set_value(toggleIntakeLift);
    // intake_lift_right.set_value(toggleIntakeLift);
	intake_lift.set_value(toggleIntakeLift);
}

//controls for the ring stopper during driverControl
void ringStopperControl() {
    if (controlla.get_digital_new_press(ringStopperButton)) {
        toggleRingStopper = !toggleRingStopper;
    }
    ring_stopper.set_value(toggleRingStopper);
}

//controls for the clamp during driverControl
void clampControl() {
    if (controlla.get_digital_new_press(clampButton)) {
    toggleClamp = !toggleClamp;
    }
    // clamp_left.set_value(toggleClamp);
    // clamp_right.set_value(toggleClamp);
    clamp_left.set_value(toggleClamp);
    clamp_right.set_value(toggleClamp);
}

//controls for the doinker for driverControl
void doinkerControl() {
    if (controlla.get_digital_new_press(doinkerButton)) {
        toggleDoinker = !toggleDoinker;
    }
    doinker.set_value(toggleDoinker);
}

//current controls for the arm during driverControl
void armControl() {
    if (controlla.get_digital(ArmUpButton)) {
        armVoltage(12000);
        // armPID.target_set(10);
        
    }
    else if (controlla.get_digital(ArmDownButton)) {
            armVoltage(-12000);
        // armPID.target_set(0);
    }
    else {
        armVoltage(0);
    }
}