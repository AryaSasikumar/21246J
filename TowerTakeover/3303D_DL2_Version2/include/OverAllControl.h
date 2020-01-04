#include "AutonomusRoutines.h"

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool leftDriveStop = true;
bool rightDriveStop = true;
bool intakeStop = true;


// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  while (true) {
    if (RemoteControlCodeEnabled) {
      myBase.userControl();
      myLift.userControl();
      myIntake.userControl();
      
      myAuton.userControl();
    }
    wait(20, msec);
  }
  return 0;
}



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}