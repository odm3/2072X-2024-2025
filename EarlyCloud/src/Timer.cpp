#include "main.h"
#include "Timer.h"

Timer::Timer() {
    start = pros::millis();
}

double Timer::getElapsedTimeMS() {
    return (pros::millis() - start);
}

void Timer::reset() {
    start = pros::millis();
}