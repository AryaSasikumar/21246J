#include "AutonomusRoutines.h"

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs

// define a task that will handle monitoring inputs from Controller1

/*int case_no;

void sort(){
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("task running");

  case_no = 0;

  Vision5.takeSnapshot(Vision5__BLUEBOX,1);
  if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
    //blue found
    case_no = 1;
  }

  Vision5.takeSnapshot(Vision5__REDBOX,1);
  if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
    //red found
    case_no = 2;

    if (colorChecker.reflectivity() > 50){
      //red found, top storage taken
      case_no = 3;
    }
  }

  switch(case_no){
  case 1: //blue found
    //filter
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    break;

  case 2: //red found, nothing in top storage
    //intake up, run top roller
    while(colorChecker.reflectivity() < 50){
      rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);
      leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    }
    break;

  case 3: //red found, top storage taken
    //intake up
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    break;

  default:
    //intake normally
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    Brain.Screen.clearLine(1, black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("default");
  }
}*/

int sort(){
  int case_no;
  int looper = true;
  while(true){
  if(autoSortBtn){
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("task running");

  case_no = 0;

  Vision5.takeSnapshot(Vision5__BLUEBOX,1);
  if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
    //blue found
    case_no = 1;
  }

  Vision5.takeSnapshot(Vision5__REDBOX,1);
  if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
    //red found
    case_no = 2;

    if (colorChecker.reflectivity() > 50){
      //red found, top storage taken
      case_no = 3;
    }
  }

  switch(case_no){
  case 1: //blue found
    //filter
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    break;

  case 2: //red found, nothing in top storage
    //intake up, run top roller
    if(looper){
      if(colorChecker.reflectivity() < 50){
        rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);
        leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
      }
      looper = false;
    }
    break;

  case 3: //red found, top storage taken
    //intake up
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    break;

  default:
    //intake normally
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    Brain.Screen.clearLine(1, black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("default");
  }
  }
  }
  return 0;
}

int rc_auto_loop_callback_Controller1() {
  while (true){
    if(RemoteControlCodeEnabled) {
      myBase.userControl();
      myIntake.userControl();
      myAuton.userControl();
      if(autoSortBtn){
        int case_no;
  int looper = true;
  if(autoSortBtn){
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("task running");

  case_no = 0;

  Vision5.takeSnapshot(Vision5__BLUEBOX,1);
  if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
    //blue found
    case_no = 1;
  }

  Vision5.takeSnapshot(Vision5__REDBOX,1);
  if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
    //red found
    case_no = 2;

    if (colorChecker.reflectivity() > 50){
      //red found, top storage taken
      case_no = 3;
    }
  }

  switch(case_no){
  case 1: //blue found
    //filter
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    break;

  case 2: //red found, nothing in top storage
    //intake up, run top roller
    if(looper){
      if(colorChecker.reflectivity() < 50){
        rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);
        leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
      }
      looper = false;
    }
    break;

  case 3: //red found, top storage taken
    //intake up
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    break;

  default:
    //intake normally
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    Brain.Screen.clearLine(1, black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("default");
  }
  }
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
    wait(10, msec);
  }
  mainBaseLeftEncReset;
  mainBaseRightEncReset;
  baseHeadingReset;
  baseRotationReset;
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}