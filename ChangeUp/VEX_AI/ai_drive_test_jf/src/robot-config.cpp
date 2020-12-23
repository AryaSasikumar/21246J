#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
controller Controller = controller(primary);
// VEXcode device constructors
motor LF_Drive = motor(PORT11, ratio18_1, false);
motor LB_Drive = motor(PORT20, ratio18_1, false);
motor_group LeftDrive = motor_group(LF_Drive, LB_Drive);
motor RF_Drive = motor(PORT1, ratio18_1, true);
motor RB_Drive = motor(PORT6, ratio18_1, true);
motor_group RightDrive = motor_group(RF_Drive, RB_Drive);
drivetrain Drive = drivetrain(LeftDrive, RightDrive, 299.24, 444.5, 342.9, mm, 1);



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}