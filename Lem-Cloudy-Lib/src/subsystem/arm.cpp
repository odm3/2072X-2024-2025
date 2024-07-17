#include "main.h" // IWYU pragma: keep
#include "devices.hpp"
#include "lemlib/pid.hpp"
#include "pros/motors.h"

using namespace devices;



void armVoltage(int Voltage) {
    arm.move_voltage(Voltage);
}

void armControl() {

    arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    if (controlla.get_digital_new_press(ArmUpButton)) {
        arm.move_voltage(12000);
        
    }
    else if (controlla.get_digital_new_press(ArmDownButton)) {
        arm.move_voltage(-12000);
    }
    else {
        arm.move_voltage(0);
    }
}

void armControlSpecific(double targetPos) {
    
    double currentPos = armRotation.get_position();
    double error = targetPos - currentPos;
    int armPower = error * 0.5;

    while (error > 5) {
        arm.move(armPower);
    }

    armVoltage(0);

}