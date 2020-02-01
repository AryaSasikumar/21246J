/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Robolabs                                                  */
/*    Created:      Mon Jan 06 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "base.h"

using namespace vex;

bool RemoteControlCodeEnabled = true;
int rc_auto_loop_callback_Controller1() {
  while (true) {
    if (RemoteControlCodeEnabled) {
      myBase.xDriveControl();
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

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  //vexcodeInit();
  bool lineDetected = true; 
  double leftSpeed = 10.0;
  double rightSpeed = 10.0;

  bool left = false;
  bool mid = true;
  bool right = false;
  while(lineDetected){
    if(leftLine >= 500){
      left = false;
    }else{
      left = true;
    }

    if(midLine >= 500){
      mid = false;
    }else{
      mid = true;
    }

    if(rightLine >= 500){
      right = false;
    }else{
      right = true;
    }
    //myBase.leftSpin(leftLine);
    //myBase.rightSpin(rightLine);
    // if(leftLine>rightLine){
    //   leftSpeed = 10;
    //   rightSpeed = 5;
    // }else if(leftLine<rightLine){
    //   leftSpeed = 5;
    //   rightSpeed = 10;
    // }else{
    //   leftSpeed = 10;
    //   rightSpeed = 10;
    // }
    if(leftLine >= 10 && midLine >= 4 && rightLine >= 10){
      //lineDetected = false;
    }
    // printf("Left Line: %ld\n",leftLine);
    // printf("Middle Line: %ld\n",midLine);
    // printf("Right Line: %ld\n\n",rightLine);
    printf("Left Line: %i\n",left);
    printf("Middle Line: %i\n",mid);
    printf("Right Line: %i\n\n",right);
    task::sleep(20);
  }
}
