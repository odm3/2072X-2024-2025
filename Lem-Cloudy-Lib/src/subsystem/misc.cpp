#include "main.h" // IWYU pragma: keep
#include "misc.hpp"
#include "devices.hpp"

using namespace devices;

bool toggleClamp = LOW;
bool toggleDoinker = LOW;
bool toggleRingStopper =  LOW;

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

void clampControl() {
    if (controlla.get_digital_new_press(clampButton)) {
    toggleClamp = !toggleClamp;
    }
    // clamp_left.set_value(toggleClamp);
    // clamp_right.set_value(toggleClamp);
    clamp_left.set_value(toggleClamp);
    clamp_right.set_value(toggleClamp);
}

void doinkerActivate() {
    doinker.set_value(true);
}

void doinkerRetract() {
    doinker.set_value(true);
}

void doinkerControl() {
    if (controlla.get_digital_new_press(doinkerButton)) {
        toggleDoinker = !toggleDoinker;
    }
    doinker.set_value(toggleDoinker);
}

void ringStopperActivate() {
    ring_stopper.set_value(true);
}

void ringStopperRetract() {
    ring_stopper.set_value(false);
}

void ringStopperControl() {
    if (controlla.get_digital_new_press(ringStopperButton)) {
        toggleRingStopper = !toggleRingStopper;
    }
    ring_stopper.set_value(toggleRingStopper);
}