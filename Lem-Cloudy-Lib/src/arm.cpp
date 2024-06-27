#include "devices.hpp"
#include "lemlib/pid.hpp"
#include "main.h"

lemlib::PID armPID(
    5,
    0,
    0
);

void armControl() {
    if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        arm.move_voltage(5000);
    }
    else if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        arm.move_voltage(-5000);
    }
}