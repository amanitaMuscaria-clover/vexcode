#include "vex.h"

double linearfudge = (48.0 / 50.0);
static void mobile_balanceB();
static void test();
static void mobile_balanceR();
static void allygoalR();
static void allygoalB();

auton_t autons[] = {
  {
      .name = "Ally Goal",
      .red = false,
      .prog = allygoalB,
    },
  {
      .name = "Mobile Balance Blue",
      .red = false,
      .prog = mobile_balanceB,
    },
    {
      .name = "Alliance Goal Red",
      .red = true,
      .prog = allygoalR,
    },
    
    {
      .name = "Mobile Balance Red",
      .red = true,
      .prog = mobile_balanceR,
    },

    {
      .name = "test", 
      .red = false, 
      .prog = test,
    },
    {
        .name = "NONE",
        .red = true,
        .prog = NULL,
    },
};

const int AUTONCOUNT(sizeof(autons) / sizeof(autons[0]));

//-------------------------------------------------------------

double power = 100;
double WHEELDIAMETER_CM = 10.16;

// travelTarget will define how far we want the robot to move in centimeters.

// Calculate wheel circumference: circumference = (wheelDiameter)(PI)
const double CIRCUMFERENCE = WHEELDIAMETER_CM * 3.141592;

// THIS IS A GLOBAL VARIABLE

double tiles_to_cm(double tiles) { return tiles * 24.0 * 2.54 * linearfudge; }

double cm_to_degree(double cm) { return (360 * cm) / CIRCUMFERENCE; }

// These are the speed setting/stopping functions
// Function for setting tilter speed (percentage)

// These are the turning and moving functions
// define your global instances of motors and other devices here
// Turns are in pi radians, 1 makes a 180 degree turn, 0.5 for 90 degrees

void myright(double travelTargetTiles) {
  double degreesToRotate = cm_to_degree(tiles_to_cm(travelTargetTiles));
  LeftMotor2.rotateFor(-degreesToRotate, deg, false);
  LeftMotor.rotateFor(-degreesToRotate, deg, false);
  RightMotor2.rotateFor(degreesToRotate, deg, false);
  RightMotor.rotateFor(degreesToRotate, deg);
}

// 1 makes a 180 degree turn, use 0.5 for 90 degrees
void myleft(double travelTargetTiles) {
  double degreesToRotate = cm_to_degree(tiles_to_cm(travelTargetTiles));
  LeftMotor2.rotateFor(degreesToRotate, deg, false);
  LeftMotor.rotateFor(degreesToRotate, deg, false);
  RightMotor2.rotateFor(-degreesToRotate, deg, false);
  RightMotor.rotateFor(-degreesToRotate, deg);
}

void setSpeed(double speed) {
  LeftMotor.setVelocity(speed, pct);
  LeftMotor2.setVelocity(speed, pct);
  RightMotor.setVelocity(speed, pct);
  RightMotor2.setVelocity(speed, pct);
}

void gyroLeft(double degrees) {
  double target = Inertial5.yaw(deg);
  setSpeed(30);
  while(Inertial5.yaw() < target) {
    LeftMotor.spin(fwd);
    LeftMotor2.spin(fwd);
    RightMotor.spin(reverse);
    RightMotor2.spin(reverse);
  }
}

void gyroRight(double degrees) {
  double target = Inertial5.yaw(deg);
  setSpeed(30);
  while(Inertial5.yaw() < target) {
    LeftMotor.spin(reverse);
    LeftMotor2.spin(reverse);
    RightMotor.spin(fwd);
    RightMotor2.spin(fwd);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print(Inertial5.yaw(deg));
  }
}

void myforward(double travelTargetTiles, double tiktok) {
  // Now we know the robot will travel the Circumference per 360 degrees of
  // rotation or (circumference / 360 degrees). We also know that are target
  // distance is defined as travelTargetCM, but we do not know the degrees to of
  // rotation. (traveTargetCM / ?) Using propotional reasoning we know
  // (circumference / 360) = (travelTarget / degreesToRotate). Solving for our
  // unkown (degreesToRotate) we get: degreesToRotate = (360 / travelTargetCM) /
  // circumference
  double degreesToRotate = cm_to_degree(tiles_to_cm(travelTargetTiles));

  LeftMotor2.rotateFor(-degreesToRotate, deg, false);
  LeftMotor.rotateFor(-degreesToRotate, deg, false);
  // This command is blocking so the program will wait here until the right
  // motor is done.
  RightMotor2.rotateFor(-degreesToRotate, deg, false);
  RightMotor.rotateFor(-degreesToRotate, deg);

  LeftMotor2.setTimeout(tiktok, sec);
  RightMotor2.setTimeout(tiktok, sec);
  RightMotor.setTimeout(tiktok, sec);
  LeftMotor.setTimeout(tiktok, sec);
}

void backward(double travelTargetTiles, double tiktok) {
  const double degreesToRotate = cm_to_degree(tiles_to_cm(travelTargetTiles));

  LeftMotor2.rotateFor(degreesToRotate, deg, false);
  LeftMotor.rotateFor(degreesToRotate, deg, false);
  // This command is blocking so the program will wait here until the right
  // motor is done.
  RightMotor2.rotateFor(degreesToRotate, deg, false);
  RightMotor.rotateFor(degreesToRotate, deg);

  LeftMotor.setTimeout(tiktok, sec);
  RightMotor.setTimeout(tiktok, sec);
  LeftMotor2.setTimeout(tiktok, sec);
  RightMotor2.setTimeout(tiktok, sec);
}

void liftUp(int degrees, double tiktok){
  leftLift.rotateFor(forward, degrees, deg);
  rightLift.rotateFor(forward, degrees, deg);
  vex::task::sleep(tiktok*1000);
  leftLift.stop();
  rightLift.stop();
}

void liftDown(int degrees, double tiktok){
  leftLift.rotateFor(reverse, degrees, deg);
  rightLift.rotateFor(reverse, degrees, deg);
  leftLift.stop();
  rightLift.stop();
}

//function for flipout routine
void flipout() {
  leftLift.setVelocity(100, pct);
  rightLift.setVelocity(100, pct);
  liftUp(70, 0.1);
  liftDown(90, 0.1);
}

void hookhook() {
  hook.set(0);
}

void hookoff() {
  hook.set(1);
}

void outtake(int dag) {
  intake.rotateFor(dag, degrees);
}

//Auton for blue mobile balance
void mobile_balanceB() {
  flipout();
  vex::task::sleep(100);
  hookoff();
  setSpeed(70);
  myforward(2.2, 4);
  myright(0.25);
  myforward(0.1, 1);
  vex::task::sleep(100);
  hookhook();
  backward(1.8, 1.5);
  outtake(500);
/*
  setSpeed(30);
  myright(0.35);
  myforward(2.5, 1);
  liftUp(800, 1);

  myleft(0.4);
  liftDown(400, 2);

*/

  //score
  // liftDown(300);
  // hookoff();
  // liftUp(100);
  // backward(0.5, 3);
}

//Auton for Red Mobile Balance
void mobile_balanceR() {
  flipout();
  vex::task::sleep(100);
  hookoff();
  setSpeed(70);
  myforward(2.3, 4);
  myright(0.25);
  myforward(0.1, 1);
  vex::task::sleep(100);
  hookhook();
  backward(1.5, 1.5);
  outtake(500);

  // setSpeed(30);
  // myright(0.35);
  // myforward(2.5, 1);
  //liftUp(800, 1);
  myleft(0.4);
  // liftDown(400, 2);
  //score
  // liftDown(300);
  // hookoff();
  // liftUp(100);
  // backward(0.5, 3);
}

void allygoalB() {
  outtake(500);
  vex::task::sleep(100);
  setSpeed(40);
  backward(0.4, 5);
  myleft(0.15);
  myright(0.15);
  myforward(0.1, 0.5);
  myleft(0.15);
  vex::task::sleep(100);
  myforward(1, 1);
  flipout();
}

void allygoalR() {
  outtake(500);
  vex::task::sleep(100);
  setSpeed(40);
  myforward(1.5, 5);
  myright(0.15);
  myforward(0.1, 0.5);
  vex::task::sleep(100);
  backward(1, 1);
  flipout();
}

//test function
void test() {
  flipout();
  backward(1, 1);
}



