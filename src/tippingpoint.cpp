/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       user                                                      */
/*    Created:      Sun Oct 06 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

#define TASKTIME   10
#define UPCOUNT     (500/TASKTIME)
//-------------------------------------------------------------
static void updateCtlDsp(void) {
  static int cnt = 0;

  cnt += 1;
  cnt %= UPCOUNT;
  if (cnt) return;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Arm temp: %d", (int) leftLift.temperature());  
}

static void initCallBacks(void) {
  Controller1.Axis1.changed(driveTrainCallBack);
  Controller1.Axis3.changed(driveTrainCallBack);
  Controller1.ButtonUp.pressed(normalCallBack);
  Controller1.ButtonDown.pressed(holdCallBack);
  Controller1.ButtonX.pressed(hookon);
  Controller1.ButtonB.pressed(unhook);
  Controller1.ButtonR1.pressed(takein);
  Controller1.ButtonR2.pressed(takeout);

  //Switches robot direction for backwards driving
  Controller1.ButtonA.pressed(dirSwitch);
}

//-------------------------------------------------------------

void mydrivercontrol(void) {
  // Display that the program has started to the screen.
  //initDrvMotorDirections();
  LeftMotor.setReversed(false);
  LeftMotor2.setReversed(false);
  initCallBacks();

  // Create an infinite loop so that the program can pull remote control values
  // every iteration. This loop causes the program to run forever.
  while (1) {
    liftTask();
    updateCtlDsp();
    // Sleep the task for a short amount of time to prevent wasted resources.
    wait(TASKTIME, msec);
  }
}