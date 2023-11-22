#include "main.h"
bool togglebalance = false;
bool toggleblocker = false;

int fire() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    catapult.move(90);
  }
  else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
    catapult.move(0);
    catapult.set_brake_mode(MOTOR_BRAKE_COAST);
    catapult.brake();
  }
  else {
    catapult.move(0);
    catapult.set_brake_mode(MOTOR_BRAKE_HOLD);
    catapult.brake();
  }

  pros::delay(20);

  return 1;

}

int intaking() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    intake.move(127);
  }
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    intake.move(-127);
  }
  else {
    intake.move(0);
    intake.set_brake_mode(MOTOR_BRAKE_HOLD);
    intake.brake();
  }


  pros::delay(20);

  return 1;

}


int blockerControl() {
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    toggleblocker = !toggleblocker;
    leftBlocker.set_value(toggleblocker);
    rightBlocker.set_value(toggleblocker);
  } 

  pros::delay(20);

  return 1;

}


int leftblockerControl() {
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
    toggleblocker = !toggleblocker;
    leftBlocker.set_value(toggleblocker);
  } 

  pros::delay(20);

  return 1;

}

int rightblockerControl() {
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
    toggleblocker = !toggleblocker;
    rightBlocker.set_value(toggleblocker);
  } 

  pros::delay(20);

  return 1;

}


int balanceControl() {
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
    togglebalance = !togglebalance;
    balance.set_value(togglebalance);  
  } 

  pros::delay(20);

  return 1;

}