/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

typedef struct {
  char name[40];      // auton name
  bool red;           // red or not blue routine
  void (*prog)(void); // auton method
} auton_t;

extern auton_t autons[];
extern const int AUTONCOUNT;
extern int brakesum;
extern void myPreAuton(void);
extern void myAuton(void);

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)


#define INTAKEPOWER 75
#define OUTTAKEPOWER 40
#define LIFTPOWER 50
#define TURNFRACTION 0.3
#define DEADZONE 10

// intake
void takein(void);
void takeout(void);

// lift
void lift(int power);
void liftTask(void);
void liftCallback(void);

// callbacks
void initCallbacks();

// drivercontrol 
void mydrivercontrol();
void driveTrainCallBack();
void normalCallBack();
void holdCallBack();

// pneumatic hook
void hookon();
void unhook();

//switches direction of robot so Jazzy can drive backwards
void dirSwitch();