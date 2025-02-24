#pragma once

//declare color soring variables
inline bool passRed = false;
inline bool sign = true;
inline int totalRings = 0;
inline int redRings = 0;
inline int blueRings = 0;

enum allaince{red = 1, blue = -1, red1 = 5, red2 = 25, blue1 = 210, blue2 = 230};
inline int allainceIndex = 1;

//declaring small autos
void nothing();
void drive12();

void autoSkills();

void posRed();
void posBlue();

void safePosRed();
void safePosBlue();

void ringRush(bool isRed);
void ringRushRed();
void ringRushBlue();

void soloAwp(bool isRed);
void soloAwpRed();
void soloAwpBlue();

//declaring 5 ring autos
void pos5Elims(bool isRed);
void pos5ElimsRed();
void pos5ElimsBlue();
void neg5(bool isRed);
void neg5Red();
void neg5Blue();

//declaring 2 ring autos
void pos2(bool isRed);
void pos2Red();
void pos2Blue();
void neg2(bool isRed);
void neg2Red();
void neg2Blue();

//declaring example autos
void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void motion_chaining();
void combining_movements();
void interfered_example();
void odom_drive_example();
void odom_pure_pursuit_example();
void odom_pure_pursuit_wait_until_example();
void odom_boomerang_example();
void odom_boomerang_injected_pure_pursuit_example();
void measure_offsets();