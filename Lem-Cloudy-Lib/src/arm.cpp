#include "devices.hpp"
#include "main.h"

void armControl() {
    if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        arm.move_absolute(100, 100);
    }
    else if (controlla.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        arm.move_absolute(-100, 100);
    }
}