#include "main.h"

pros::Imu gyro(2);

pros::Motor intake(9, MOTOR_GEARSET_06, true, MOTOR_ENCODER_DEGREES);
pros::Motor catapult(10, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut leftBlocker('G', false);
pros::ADIDigitalOut rightBlocker('H', false);
pros::ADIDigitalOut balance('A', false);

