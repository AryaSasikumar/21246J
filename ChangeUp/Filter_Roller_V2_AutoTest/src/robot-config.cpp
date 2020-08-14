#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LF = motor(PORT1, ratio6_1, true);
motor LT = motor(PORT2, ratio6_1, false);
motor LB = motor(PORT11, ratio6_1, true);
motor RF = motor(PORT10, ratio6_1, false);
motor RT = motor(PORT9, ratio6_1, true);
motor RB = motor(PORT20, ratio6_1, false);
motor rightIntake = motor(PORT19, ratio18_1, false);
motor leftIntake = motor(PORT12, ratio18_1, false);
controller Controller1 = controller(primary);
line colorChecker = line(Brain.ThreeWirePort.C);
/*vex-vision-config:begin*/
signature Vision5__REDBOX = signature (1, 5845, 6791, 6318, -1041, -231, -636, 4.2, 0);
signature Vision5__BLUEBOX = signature (2, -3245, -2725, -2985, 7143, 7809, 7476, 7.9, 0);
vision Vision5 = vision (PORT8, 150, Vision5__REDBOX, Vision5__BLUEBOX);
/*vex-vision-config:end*/
line leftLineTracker = line(Brain.ThreeWirePort.B);
line rightLineTracker = line(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}