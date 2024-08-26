#include "main.h"

// a universal speed for the EzTempChassis to follow. These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

//nothing happens during auto, last ditch effort if no autos work
//(0 stakes, 0 rings, no lader, 0pts.)
void noAuto() {

}