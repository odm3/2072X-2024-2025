#include "main.h" // IWYU pragma: keep
#include "devices.hpp"
#include "lemlib/pid.hpp"
#include "pros/motors.h"

using namespace devices;

lemlib::PID armPID(
    5,
    0,
    0
);

void armVoltage(int Voltage) {
    arm.move_voltage(Voltage);
}

void armControl() {
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

