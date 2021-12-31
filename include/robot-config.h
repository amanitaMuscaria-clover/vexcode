using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor rightLift;
extern motor leftLift;
extern controller Controller1;
extern digital_out hook;
extern motor LeftMotor;
extern motor LeftMotor2;
extern motor RightMotor;
extern motor RightMotor2;
extern motor intake;
extern inertial Inertial5;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );