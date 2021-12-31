#include "vex.h"

int frontswitch = 0;

void leftDrive(int power) {
  LeftMotor.spin(fwd, power*2, pct);
  LeftMotor2.spin(fwd, power*2, pct);

  if (power == 0) {
    LeftMotor.stop();
    LeftMotor2.stop();
    LeftMotor.stop();
    LeftMotor2.stop();
  }
}

void dirSwitch() {
  frontswitch ++;
}

void rightDrive(int power) {
  RightMotor.spin(fwd, power*2, pct);
  RightMotor2.spin(fwd, power*2, pct);
 
  if (power == 0) {
    RightMotor.stop();
    RightMotor2.stop();
    RightMotor.stop();
    RightMotor2.stop();
  }
}

void holdCallBack() {
  RightMotor.setStopping(hold);
  RightMotor2.setStopping(hold);
  RightMotor.setStopping(hold);
  RightMotor2.setStopping(hold);
}

void normalCallBack() {
  RightMotor.setStopping(coast);
  RightMotor2.setStopping(coast);
  RightMotor.setStopping(coast);
  RightMotor2.setStopping(coast);
}

void driveTrainCallBack(void) {
  // Drive Control
  // Set the left and right motor to spin forward using the controller's Axis
  // position as the velocity value. Since we are using a single joystick, we
  // will need to calculate the final volicity for each motor.
  int forward = Controller1.Axis1.position();
  int turn = Controller1.Axis3.position();
  /* reduce turning speed */
  int leftPower;
  int rightPower;
  
  if (frontswitch%2== 0) {
    leftPower = forward + turn;
    rightPower = forward - turn;
  } else{
    leftPower = forward - turn;
    rightPower = forward + turn;
  }

  /* create deadzone around 0 to avoid drift */
  if (abs(leftPower) < DEADZONE)
    leftPower = 0;
  if (abs(rightPower) < DEADZONE)
    rightPower = 0;
    
  leftDrive(leftPower);
  rightDrive(rightPower);
}