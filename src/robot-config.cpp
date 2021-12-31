#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor rightLift = motor(PORT10, ratio36_1, false);
motor leftLift = motor(PORT1, ratio36_1, true);
controller Controller1 = controller(primary);
digital_out hook = digital_out(Brain.ThreeWirePort.A);
motor LeftMotor = motor(PORT11, ratio18_1, false);
motor LeftMotor2 = motor(PORT3, ratio18_1, false);
motor RightMotor = motor(PORT8, ratio18_1, false);
motor RightMotor2 = motor(PORT9, ratio18_1, false);
motor intake = motor(PORT6, ratio18_1, false);
inertial Inertial5 = inertial(PORT5);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}