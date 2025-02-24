#pragma once

//declaring simple intake and arm functions
void moveIntake(int vltg);
void intakeTorque_task();
void armPos(int pos);
void arm_wait();
void controlArm();

//declaring driver control functions
void control_intake();
void control_arm();
void control_clamp();
void control_lift();
void control_doinker_left();
void control_doinker_right();

//declaring tasks
void controlArmTask();
void autoClampTask();
void colorSortTask();