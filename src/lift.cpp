#include "vex.h"

void lift(int power) {
  static int lastPower;
  leftLift.setStopping(hold);
  rightLift.setStopping(hold);

  if (abs(power) > 10) {
    leftLift.spin(fwd, power, pct);
    rightLift.spin(fwd, power, pct);
  }  else {
    leftLift.stop();
    rightLift.stop();
  }
  lastPower = power;
}

// Arm controls
//    (X) for arm up with HOLD on release
//    (B) arm down
void liftTask(void) {
  int power = 0;

  if (Controller1.ButtonL1.pressing()) // top
    power = LIFTPOWER;
  else if (Controller1.ButtonL2.pressing())
    power = -LIFTPOWER;
  lift(power);
}

void hookon() {
  hook.set(0);
}

void unhook() {
  hook.set(1);
}