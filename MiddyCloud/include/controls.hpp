#pragma once

// declares subsystem functions in auto
void intakeVoltage(int vltg);
void armVoltage(int vltg);
void activateIntakeLift();
void deActivateIntakeLift();
void activateClamp();
void deActivateClamp();
void activateDoinker();
void deActivateDoinker();
void activateHang();
void deActivateHang();

// declares subsystem function in driver control
void controlIntake();
void controlArm();
void controlIntakeLift();
void controlClamp();
void controlDoinker();
void controlHang();
void controlHoodLift();