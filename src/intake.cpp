#include "vex.h"

//-------------------------------------------------------------
void takein() {
  intake.setVelocity(70, pct);
  intake.spinFor(fwd, 600, degrees);
}

void takeout() {
  intake.setVelocity(50, pct);
  intake.spinFor(reverse, 550, degrees);
}
