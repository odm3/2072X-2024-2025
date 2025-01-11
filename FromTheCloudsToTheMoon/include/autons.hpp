#pragma once

inline bool isRed = true;
enum allaince{red = 1, blue = -1, red1 = 10, red2 = 45, blue1 = 70, blue2 = 115};
inline int allainceIndex = 1;
inline int allianceArray [2] = {red, blue};

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