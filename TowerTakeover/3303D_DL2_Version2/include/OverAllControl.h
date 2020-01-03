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
      myLift.userControl();
      if (Y_leftJoy < 5 && Y_leftJoy > -5) {
        if (leftDriveStop) {
          LeftDriveSmart.stop();
          leftDriveStop = false;
        }
      } else {
        leftDriveStop = true;
      }
      if (Y_rightJoy < 5 && Y_rightJoy > -5) {
        if (rightDriveStop) {
          RightDriveSmart.stop();
          rightDriveStop = false;
        }
      } else {
        rightDriveStop = true;
      }
      if (leftDriveStop) {
        LeftDriveSmart.setVelocity(Y_leftJoy, percent);
        LeftDriveSmart.spin(forward);
      }
      if (rightDriveStop) {
        RightDriveSmart.setVelocity(Y_rightJoy, percent);
        RightDriveSmart.spin(forward);
      }

      if (intakeBtn) {
        IntakeSmart.spin(forward, 100, percent);
      } else if (outtakeBtn) {
        IntakeSmart.spin(reverse, 100, percent);
      } else {
        IntakeSmart.stop(hold);
      }
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