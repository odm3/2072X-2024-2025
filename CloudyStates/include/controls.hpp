#pragma once

#include "EZ-Template/PID.hpp"
#include "controls.hpp"
inline bool is_auto = false;

inline int intake_vltg = 0;

void intake_control();
void intake_t();

inline int arm_vltg = 0;

inline int armState = 0;
enum armStates{ARM_DOWN = 0, ARM_PRIME1 = 2000, ARM_PRIME2 = 4000, ARM_SCORE = 12000, ARM_ALLIANCE = 18000};

void armPos(int target);
void arm_control();
void arm_t();
