#include "vex.h"

int auton_index = 0;

// update LCD display
static void update_display(void) {
  Brain.Screen.setFont(propXL);
  Brain.Screen.setPenColor(autons[auton_index].red ? red : blue);
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(80, 100, autons[auton_index].name);
}

// Callback for LCD press
static void autonMenuCallBack(void) {
  auton_index += 1;
  auton_index %= AUTONCOUNT;
  update_display();
}

// Call selected auton
void myAuton(void) {
  LeftMotor.setReversed(true);
  LeftMotor2.setReversed(true);
  if (autons[auton_index].prog)
    (*autons[auton_index].prog)();
}

// PreAuton routine which displays the Auton menuing system
void myPreAuton(void) {
  update_display();
  Brain.Screen.pressed(autonMenuCallBack);
  Inertial5.startCalibration();
  while(1) {
    //This ensures that the gyroscope has enough time to calibrate before running 
    if(Inertial5.isCalibrating() == false) {
      Controller1.Screen.clearLine();
      Controller1.Screen.print("Begin");
      Controller1.Screen.clearScreen();
    }
  }
}