#include "devices.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/rotation.hpp"
#include "timer.h"
//includes

//creates controller
pros::Controller controlla (pros::E_CONTROLLER_MASTER);

//creates drive motors with specified ports and gearsets
pros::Motor LF_motor(PORT_LF, pros::MotorGears::blue);
pros::Motor LM_motor(PORT_LM, pros::MotorGears::blue);;
pros::Motor LB_motor(PORT_LB, pros::MotorGears::blue);;
pros::Motor RF_motor(PORT_RF, pros::MotorGears::blue);;
pros::Motor RM_motor(PORT_RM, pros::MotorGears::blue);;
pros::Motor RB_motor(PORT_RB, pros::MotorGears::blue);;

//creates left motor groups with individual motors listed above
pros::MotorGroup left_chassis({ PORT_LF, PORT_LM, PORT_LB }, pros::MotorGearset::blue);
//creates right motor groups with individual motors listed above
pros::MotorGroup right_chassis({ PORT_RF, PORT_RM, PORT_RB }, pros::MotorGearset::blue);

//creates smart wire sensors with their ports
pros::Imu IMU(PORT_IMU);
pros::Rotation armRotation(PORT_ARM_ROTATION);
pros::Rotation conveyorRotation(PORT_CONVEYOR_ROTATION);

//creates motors for mechanisms with specified ports and gearsets
pros::Motor intake(PORT_INTAKE, pros::MotorGears::rpm_200);
pros::Motor conveyor(PORT_CONVEYOR, pros::MotorGears::rpm_200);
// pros::MotorGroup arm({PORT_ARM_LEFT, PORT_ARM_RIGHT}, pros::MotorGears::rpm_200);
pros::Motor arm(PORT_ARM, pros::MotorGearset::rpm_100);

//tw devices (pistons)
pros::adi::DigitalOut intake_lift(PORT_INTAKE_LIFT, LOW);
// pros::adi::DigitalOut intake_lift_left(PORT_INTAKE_LIFT_LEFT, LOW);        /*SCRAPPED*/
// pros::adi::DigitalOut intake_lift_right(PORTS_INTAKE_LIFT_RIGHT, LOW);     /*SCRAPPED*/
// pros::adi::DigitalOut clamp(PORT_CLAMP, LOW);                              /*SCRAPPED*/
pros::adi::DigitalOut clamp_left(PORT_CLAMP_LEFT, LOW);
pros::adi::DigitalOut clamp_right(PORT_CLAMP_RIGHT, LOW);
// pros::adi::DigitalOut claw(PORT_CLAW, LOW);                                /*SCRAPPED*/
// pros::adi::DigitalOut doinker(PORT_DOINKER, LOW);                          /*SCRAPPED*/
// pros::adi::DigitalOut ring_stopper(PORT_RING_STOPPER,LOW);                 /*SCRAPPED*/

//creates drivetrain with certain variables listed below
lemlib::Drivetrain drivetrain(&left_chassis, // left motor group
                              &right_chassis, // right motor group
                              13.5, // 13.5 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" diameter omni wheels
                              450, // drivetrain rpm is 480
                              2 // horizontal drift is 8 since a tracking wheel is used, 2 if all omnis are used
);

//creates rotation sensors for odom with specified ports
pros::Rotation odom_vert_sensor(PORT_ODOM_VERT);
pros::Rotation odom_hozi_sensor(PORT_ODOM_HORI);

//creates odom tracking wheel configuration with specified rotation sensors, wheel sizes, and offsets
lemlib::TrackingWheel odom_vert_wheel(&odom_vert_sensor, lemlib::Omniwheel::NEW_2, VERTICAL_OFFSET);
lemlib::TrackingWheel odom_hori_wheel(&odom_hozi_sensor, lemlib::Omniwheel::NEW_2, HORIZONTAL_OFFSET);


//creates odom sensor group with the sensors crated above
lemlib::OdomSensors odom_sensors(
    &odom_vert_wheel, // vertical tracking wheel
    nullptr, // N/A
    &odom_hori_wheel, //horiztonal tracking wheel
    nullptr, // N/A
    &IMU // inertial sensor
);

//creates lateral drive PID controller 
lemlib::ControllerSettings lateral_controller(
    10, // proportional gain (kP)
    0, // integral gain (kI)
    3, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

//creates angular drive PID controller 
lemlib::ControllerSettings angular_controller(
    2, // proportional gain (kP)
    0, // integral gain (kI)
    10, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

//constants used for functions that the EzTempChassis uses
void default_constants() {
  EzTempChassis.pid_heading_constants_set(11, 0, 20);
//   EzTempChassis.pid_drive_constants_set(4, 0, 3);
  EzTempChassis.pid_drive_constants_set(4, 0, 3);
  EzTempChassis.pid_turn_constants_set(6, 0.05, 75, 15);
  EzTempChassis.pid_swing_constants_set(6, 0, 65);

  EzTempChassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EzTempChassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  EzTempChassis.pid_drive_exit_condition_set(1000_ms, 1_in, 1000_ms, 3_in, 1000_ms, 1000_ms);

  EzTempChassis.pid_turn_chain_constant_set(3_deg);
  EzTempChassis.pid_swing_chain_constant_set(5_deg);
  EzTempChassis.pid_drive_chain_constant_set(3_in);

  EzTempChassis.slew_drive_constants_set(7_in, 80);
}

void no_mogo_constants() {
  EzTempChassis.pid_heading_constants_set(11, 0, 20);
  EzTempChassis.pid_drive_constants_set(20, 0, 100);
  EzTempChassis.pid_turn_constants_set(3, 0.05, 20, 15);
  EzTempChassis.pid_swing_constants_set(6, 0, 65);

}

/*NOT CURRENTLY IN USE*/
//creates an exponential drive curve function variable with specified deadzone, minimum output, and curve.
lemlib::ExpoDriveCurve lateral_curve(
    5,
    10,
    LEMLIB_DRIVE_CURVE
);

//creates LemLib chassis with variables created above
lemlib::Chassis LemLibChassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    odom_sensors
);

//creates chassis for LemLib with listed motor ports and constants
ez::Drive EzTempChassis( 
    {PORT_LF, PORT_LM, PORT_LB},
    {PORT_RF, PORT_RM, PORT_RB}, 
    PORT_IMU,
    2.75,
    480
);


Timer timer;