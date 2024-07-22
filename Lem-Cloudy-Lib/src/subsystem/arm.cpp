#include "main.h" // IWYU pragma: keep
#include "devices.hpp"
// #include "lemlib/pid.hpp"
// #include "pros/motors.h"

void armVoltage(int Voltage) {
    arm.move_voltage(Voltage);
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

void armControlSpecific(double targetPos) {
    
    double currentPos = armRotation.get_position();
    double error = targetPos - currentPos;
    int armPower = error * arm_kp;

    while (error > 5) {
        arm.move(armPower);
    }

    armVoltage(0);

}