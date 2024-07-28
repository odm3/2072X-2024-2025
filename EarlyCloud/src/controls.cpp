#include "controls.hpp"
#include "EZ-Template/util.hpp"
#include "devices.hpp"
#include "main.h"// IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"


//inits all variables for pistons as false/not activate 
bool toggleRingStopper =  false;
bool toggleIntakeLift = false;
bool toggleClamp = false;
bool toggleDoinker = false;

//lifts the intake up
void intakeLiftUp() {
intake_lift.set_value(true);
}

//lifts the intake down
void intakeLiftDown() {
intake_lift.set_value(false);
}

//activates the ring stopper
void ringStopperActivate() {
    ring_stopper.set_value(true);
}

//retracts the ring stopper
void ringStopperRetract() {
    ring_stopper.set_value(false);
}

//activates the clamp
void clampActivate() {
    clamp_left.set_value(true);
    clamp_right.set_value(true);
}

//retracts the clamp
void clampRetract() {
    clamp_left.set_value(false);
    clamp_right.set_value(false);
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

    if (conveyor.get_current_draw() > conveyorStuckCurrent) {
        conveyor.move_voltage(-12000);
        pros::delay(500);
    }
    else {
        return;
    }
}

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
     armVoltage(-12000);
    }
}

/*WORK IN PROGRESS*/
//moves arm to the alliance stake position with values from the arm rotation sensor
void armToAllianceStake() {
    while (armRotation.get_position() != ARM_POS_ALLIANCE) {
        armVoltage(-12000);
    }
}

/*WORK IN PROGRESS*/
//moves arm to the wall stake position with values from the arm rotation sensor
void armToWallStake() {
    while (armRotation.get_position() != ARM_POS_WALL) {
     armVoltage(12000);
    }
}

/*WORK IN PROGRESS*/
//moves arm to a specific desired position with values from the arm rotation sensor
void armToSpecific(double targetPos) {
    
    double currentPos = armRotation.get_position();
    double error = targetPos - currentPos;
    int armPower = error * arm_kp;

    while (error > 5) {
        arm.move(armPower);
    }

    armVoltage(0);

}

//controls for intake and conveyor during driverControl
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
        arm.move_voltage(12000);
        
    }
    else if (controlla.get_digital(ArmDownButton)) {
        arm.move_voltage(-12000);
    }
    else {
        arm.move_voltage(0);
    }
}