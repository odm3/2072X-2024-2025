#include "main.h" // IWYU pragma: keep
#include "devices.hpp"
// #include "lemlib/pid.hpp"
// #include "pros/motors.h"

//moves the arm at a desired voltage
void armVoltage(int Voltage) {
    arm.move_voltage(Voltage);
}

//moves the arm in driver control
void armControl() {
    if (controlla.get_digital(ArmUpButton)) {   // if the arm up button is pressed, the arm will move up
        arm.move_voltage(12000);
        
    }
    else if (controlla.get_digital(ArmDownButton)) {    // if the arm down button is pressed, the arm will move down
        arm.move_voltage(-12000);
    }
    else {  // if no buttons are pressed, the arm will stop
        arm.move_voltage(0);
    }
}

//moves the arm to a specific position
void armControlSpecific(double targetPos) {

    double currentPos = armRotation.get_position(); // gets the current position of the arm
    double error = targetPos - currentPos;  // calculates the error
    int armPower = error * arm_kp;  // calculates the power to move the arm

    while (error > 5) { // while the error is greater than 5, the arm will move
        arm.move(armPower);
    }
    armVoltage(0);  // stops the arm
}