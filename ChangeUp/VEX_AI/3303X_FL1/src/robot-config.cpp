#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller = controller(primary);

motor LF = motor(PORT11, ratio18_1, false);
motor LB = motor(PORT20, ratio18_1, false);
motor_group LeftDrive = motor_group(LF, LB);

motor RF = motor(PORT2, ratio18_1, true);
motor RB = motor(PORT6, ratio18_1, true);
motor_group RightDrive = motor_group(RF, RB);

drivetrain Drive = drivetrain(LeftDrive, RightDrive, 299.24, 444.5, 342.9, mm, 1);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  Brain.Screen.print("Device initialization...");
  mainBaseLeftEncReset;
  mainBaseRightEncReset;
  wait(50, msec);
  Brain.Screen.clearScreen();
}