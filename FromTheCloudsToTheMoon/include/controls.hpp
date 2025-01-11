#pragma once

void moveIntake(int vltg);

void activate_clamp();
void activate_lift();
void activate_doinker();
void deactivate_clamp();
void deactivate_lift();
void deactivate_doinker();

void armPos(int pos);

void control_intake();
void control_arm();
void control_clamp();
void control_lift();
void control_doinker();

void controlArmTask();
void autoClampTask();
void colorSortTask();