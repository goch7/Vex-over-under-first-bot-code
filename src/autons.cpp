#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 90; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 30;
const int SWING_SPEED = 90;





///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}




///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

void firstauton(){
//move              (distance, speed, slew)
chassis.set_drive_pid(2, 90, false);
chassis.wait_drive();
pros::delay(100);
//turn code        (angle, speed)
chassis.set_turn_pid(45, 90);
chassis.wait_drive();
pros::delay(100);
// fire cata
catapult.move(90);
pros::delay(100);
//intake
intake.move(-127);
// 0 means stop intake
intake.move(0);
// blocker on
leftBlocker.set_value(true);
rightBlocker.set_value(true);
// blocker off
leftBlocker.set_value(false);
rightBlocker.set_value(false);
// balance on
balance.set_value(true);
// balance off
balance.set_value(false);
//swing
chassis.set_swing_pid(ez::RIGHT_SWING, -45, 127);
chassis.wait_drive();

}

void hello(){
//intake
intake.move(-127);
//move foward little
chassis.set_drive_pid(4, 90, false);
chassis.wait_drive();
pros::delay(100);
//move back
chassis.set_drive_pid(-33, 127, false);
chassis.wait_drive();
pros::delay(100);
//turn
chassis.set_turn_pid(-45, 127);
chassis.wait_drive();
pros::delay(100);

//slow intake
intake.move(-60);
// blocker on
leftBlocker.set_value(true);
//go back
chassis.set_drive_pid(-12, 90, false);
chassis.wait_drive();
pros::delay(100);

//turn
chassis.set_turn_pid(-90, 127);
chassis.wait_drive();
pros::delay(100);
//go back
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();
pros::delay(100);
// close blocker
leftBlocker.set_value(false);
// move foward little
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();
pros::delay(100);
//turn
chassis.set_turn_pid(90, 127);
chassis.wait_drive();
pros::delay(100);
//outtake
intake.move(127);
//move foward little
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();
pros::delay(100);
//move back
chassis.set_drive_pid(-10, 127, false);
chassis.wait_drive();
pros::delay(100);
//turn
chassis.set_turn_pid(-45, 127);
chassis.wait_drive();
//move back
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();
pros::delay(100);
//turn
chassis.set_turn_pid(-90, 127);
chassis.wait_drive();
pros::delay(100);
//move back to score
chassis.set_drive_pid(-10, 127, false);
chassis.wait_drive();
pros::delay(100);
//turn
chassis.set_turn_pid(-90, 127);
chassis.wait_drive();
pros::delay(100);
//move foward
chassis.set_drive_pid(7, 127, false);
chassis.wait_drive();
pros::delay(100);
//repeat move back to score
chassis.set_drive_pid(-7, 127, false);
chassis.wait_drive();
pros::delay(100);
//turn
chassis.set_turn_pid(-90, 127);
chassis.wait_drive();
pros::delay(100);

}

void awpleftside(){

/*

// blocker on
rightBlocker.set_value(true);
//go back
chassis.set_drive_pid(-12, 90, false);
chassis.wait_drive();
pros::delay(100);
//blocker off
rightBlocker.set_value(false);
//move foward
chassis.set_drive_pid(12, 127, false);
chassis.wait_drive();
pros::delay(100);
//intake
intake.move(-127);

//turn
chassis.set_turn_pid(-100, 127);
chassis.wait_drive();
pros::delay(100);
//intake slowly
intake.move(-60);
//long move foward
chassis.set_drive_pid(48, 127, false);
chassis.wait_drive();
pros::delay(100);
//turn
chassis.set_turn_pid(-220, 90);
chassis.wait_drive();
pros::delay(100);
//move foward
chassis.set_drive_pid(18, 127, false);
chassis.wait_drive();
pros::delay(100);

//outtake
intake.move(127);

//move foward
chassis.set_drive_pid(5, 127, false);
chassis.wait_drive();
pros::delay(100);

//move back little
chassis.set_drive_pid(-9, 127, false);
chassis.wait_drive();
pros::delay(100);

//turn to score
chassis.set_turn_pid(-40, 127);
chassis.wait_drive();
pros::delay(100);

//move back to score
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();


//stop outake
intake.move(0);

//move foward after score
chassis.set_drive_pid(11, 127, false);
chassis.wait_drive();
pros::delay(100);

//turn left
chassis.set_turn_pid(50, 90);
chassis.wait_drive();
pros::delay(100);

//move foward
chassis.set_drive_pid(45, 127, true);
chassis.wait_drive();

//turn to horizontal bar
chassis.set_turn_pid(130, 127);
chassis.wait_drive();
pros::delay(100);
//move foward to touch horizontal bar
chassis.set_drive_pid(-35, 90, false);
chassis.wait_drive();

*/

//small intake to keep it in
intake.move(-30);

//go forward
chassis.set_drive_pid(12, 127, false);
chassis.wait_drive();

//open wings
leftBlocker.set_value(true);

//go back to push the corner triball out of the corner
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();

//close wings
leftBlocker.set_value(false);

//intake
intake.move(-30);

//go forwards
chassis.set_drive_pid(18, 127, false);
chassis.wait_drive();

//turn the bot
chassis.set_turn_pid(45, 127);
chassis.wait_drive();
pros::delay(100);

//move foward
chassis.set_drive_pid(2, 90, false);
chassis.wait_drive();

//outake
intake.move(127);
pros::delay(100);

//move foward
chassis.set_drive_pid(9, 90, false);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-11, 127, false);
chassis.wait_drive();
pros::delay(100);

//intake off
intake.move(0);

//turn 180
chassis.set_turn_pid(180, 127);
chassis.wait_drive();
pros::delay(100);

//move back little
chassis.set_drive_pid(-3, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(225, 127);
chassis.wait_drive();
pros::delay(100);

//move back to score
chassis.set_drive_pid(-15, 127, false);
chassis.wait_drive();
pros::delay(100);

//move foward
chassis.set_drive_pid(8, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(180, 127);
chassis.wait_drive();
pros::delay(100);

//move forward
chassis.set_drive_pid(26, 127, false);
chassis.wait_drive();

//final turn for bar triball
chassis.set_turn_pid(312, 127);
chassis.wait_drive();

//blocker on
balance.set_value(true);

//move back to touch hh
chassis.set_drive_pid(-31, 127, false);
chassis.wait_drive();

}


void awprightside(){
// blocker on
leftBlocker.set_value(true);

//go back
chassis.set_drive_pid(-12, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-45, 127);
chassis.wait_drive();

//go back
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();

// close blocker
leftBlocker.set_value(false);
//turn
chassis.set_turn_pid(0, 127);
chassis.wait_drive();

//move forward
chassis.set_drive_pid(28, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(45, 127);
chassis.wait_drive();

//intake
intake.move(-127);
//move foward
chassis.set_drive_pid(21, 127, false);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-34, 127, false);
chassis.wait_drive();

//slow intake
intake.move(-60);
//turn
chassis.set_turn_pid(180, 127);
chassis.wait_drive();

//move foward
chassis.set_drive_pid(21, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(135, 127);
chassis.wait_drive();

//outtake
intake.move(127);

//move foward
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();

//move back little
chassis.set_drive_pid(-5, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-37.5, 127);
chassis.wait_drive();

//stop outtake
intake.move(0);

//back to score
chassis.set_drive_pid(-15, 127, false);
chassis.wait_drive();

//move foward little
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-135, 127);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-48, 127, false);
chassis.wait_drive();

//expand blocker to touch bar
rightBlocker.set_value(true);


/*
//turn
chassis.set_turn_pid(0, 127);
chassis.wait_drive();

//move foward
chassis.set_drive_pid(22, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-135, 127);
chassis.wait_drive();

//balance
balance.set_value(true);

//move back
chassis.set_drive_pid(-34, 127, false);
chassis.wait_drive();


*/

}

void pointsrightside(){
// blocker on
leftBlocker.set_value(true);

//go back
chassis.set_drive_pid(-12, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-45, 127);
chassis.wait_drive();

//go back
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();

// close blocker
leftBlocker.set_value(false);

//move foward
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(0, 127);
chassis.wait_drive();

//stop outtake
intake.move(0);

//back to score
chassis.set_drive_pid(-15, 127, false);
chassis.wait_drive();

//mvoe foward little
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();

//swing
chassis.set_swing_pid(ez::LEFT_SWING, 60, 127);
chassis.wait_drive();

//intake
intake.move(-127);

//mvoe foward
chassis.set_drive_pid(37, 127, false);
chassis.wait_drive();

//slower intake
intake.move(-90);
//

//turn
chassis.set_turn_pid(190, 127);
chassis.wait_drive();

//stop outtake
intake.move(0);

//move foward
chassis.set_drive_pid(12, 127, false);
chassis.wait_drive();

//outtake to net
intake.move(70);
pros::delay(200);

//turn
chassis.set_turn_pid(90, 127);
chassis.wait_drive();

//intake
intake.move(-127);

//move foward
chassis.set_drive_pid(20, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(225, 50);
chassis.wait_drive();

//intake slow
intake.move(-60);

//move foward to score
chassis.set_drive_pid(18, 127, false);
chassis.wait_drive();

//move back little
chassis.set_drive_pid(-6, 127, false);
chassis.wait_drive();

//outake
intake.move(127);
pros::delay(100);

//turn
chassis.set_turn_pid(45, 127);
chassis.wait_drive();

// blocker on
leftBlocker.set_value(true);

//turn
chassis.set_turn_pid(60, 127);
chassis.wait_drive();

//score with back
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();

// blocker off
leftBlocker.set_value(false);

}

void firstpartrightsideroute(){
//intake
intake.move(-127);

//move foward to get tribal
chassis.set_drive_pid(9, 127, false);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-36.5, 127, false);
chassis.wait_drive();

//turn
intake.move(-127);
chassis.set_turn_pid(-45, 90);
chassis.wait_drive();

//open wings
leftBlocker.set_value(true);

//move back to get out corner tribal
chassis.set_drive_pid(-22, 127, false);
chassis.wait_drive();

//close wing
leftBlocker.set_value(false);

//move back
chassis.set_drive_pid(-2, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(90, 90);
chassis.wait_drive();

//outake
intake.move(127);

//move foward to push tribal
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-7, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-90, 127);
chassis.wait_drive();

//move back to score
chassis.set_drive_pid(-11.5, 127, false);
chassis.wait_drive();

//move foward
chassis.set_drive_pid(12.5, 127, false);
chassis.wait_drive();

//turn to middle tribal
chassis.set_turn_pid(16.75, 100);
chassis.wait_drive();

//intake
intake.move(-127);

//move foward
chassis.set_drive_pid(43.5, 127, false);
chassis.wait_drive();




//slower intake
intake.move(-90);

//turn
chassis.set_turn_pid(135, 127);
chassis.wait_drive();

//stop outtake
intake.move(0);

//move foward
chassis.set_drive_pid(12, 127, false);
chassis.wait_drive();

//outtake to net
intake.move(70);
pros::delay(200);

//turn
chassis.set_turn_pid(45, 127);
chassis.wait_drive();

//intake
intake.move(-127);

//move foward
chassis.set_drive_pid(20, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(180, 50);
chassis.wait_drive();

//intake slow
intake.move(-60);

//move foward to score
chassis.set_drive_pid(18, 127, false);
chassis.wait_drive();

//move back little
chassis.set_drive_pid(-6, 127, false);
chassis.wait_drive();

//outake
intake.move(127);
pros::delay(100);

//turn
chassis.set_turn_pid(0, 127);
chassis.wait_drive();

// blocker on
leftBlocker.set_value(true);

//turn
chassis.set_turn_pid(10, 127);
chassis.wait_drive();

//score with back
chassis.set_drive_pid(-16, 127, false);
chassis.wait_drive();

// blocker off
leftBlocker.set_value(false);

}

void nagahashiauton(){
//move back
chassis.set_drive_pid(-21, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-100, 127);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-23, 127, false);
chassis.wait_drive();

//open right blocker
rightBlocker.set_value(true);


//cata and move back
catapult.move(90);
pros::delay(39000);


//stop cata
catapult.move(0);

//close right blocker
rightBlocker.set_value(false);

//move foward
chassis.set_drive_pid(6, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-45, 127);
chassis.wait_drive();

//move foward
chassis.set_drive_pid(25, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(-90, 127);
chassis.wait_drive();



//outake
intake.move(127);



//move foward
chassis.set_drive_pid(68, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(45, 127);
chassis.wait_drive();

//stop outake
intake.move(0);

//score back
chassis.set_drive_pid(-35, 127, false);
chassis.wait_drive();

//move foward
chassis.set_drive_pid(5, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(90, 127);
chassis.wait_drive();

//move foward
chassis.set_drive_pid(40, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(0, 127);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-23, 90, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(90, 90);
chassis.wait_drive();

//open both blocker
rightBlocker.set_value(true);
leftBlocker.set_value(true);

//move back
chassis.set_drive_pid(-28, 127, false);
chassis.wait_drive();

//close blocker
rightBlocker.set_value(false);
leftBlocker.set_value(false);

//move foward
chassis.set_drive_pid(28, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(0, 127);
chassis.wait_drive();

//move back
chassis.set_drive_pid(-21, 127, false);
chassis.wait_drive();

//turn
chassis.set_turn_pid(90, 127);
chassis.wait_drive();

//open both blocker
rightBlocker.set_value(true);
leftBlocker.set_value(true);

//move back
chassis.set_drive_pid(-28, 127, false);
chassis.wait_drive();

//close blocker
rightBlocker.set_value(false);
leftBlocker.set_value(false);


}
