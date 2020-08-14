/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*----------------------------------------------------------------------------*/

//#include "vex.h"
#include "OverAllControl.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  //myAuton.currentTestAuton();

  if(navSensor<=60){
    myAuton.SecureRedFront7CubePID();
  }
  else if(navSensor<=120 && navSensor>=60){
    myAuton.SecureRedBack7CubePID();
  }
  else if(navSensor<=180 && navSensor>=120){
    myAuton.SecureBlueFront7CubePID();
  }
  else if(navSensor<=240 && navSensor>=180){
    myAuton.SecureBlueBack7CubePID();
  }
  else{
    //myAuton.skills();
    myBase.drivePID(100, 100, 24);
    task::sleep(1000); 
    myBase.drivePID(100, 100, 24);
    task::sleep(1000); 
    myBase.drivePID(100, 100, 24);
    task::sleep(1000); 
  }
  while(true){
    wait(20, msec); 
  }
}



/*---------------------------------------h------------------------------------*/
/*                              User Control Task                            */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  enableAutonTestButton = false; //Will enable Y button as an Auton Test Button
  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
  while (true) {
    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.


  while (true) {
    Brain.Screen.setFont(mono40);
    Brain.Screen.clearLine(1, black);
    Brain.Screen.setCursor(Brain.Screen.row(), 1);
    Brain.Screen.setCursor(1, 1);
    if(navSensor<=60){
      Brain.Screen.print("Red Front Secure");
    }
    else if(navSensor<=120 && navSensor>=60){
      Brain.Screen.print("Red Back Secure");
    }
    else if(navSensor<=180 && navSensor>=120){
      Brain.Screen.print("Blue Front Secure");
    }
    else if(navSensor<=240 && navSensor>=180){
      Brain.Screen.print("Blue Back Secure");
    }
    else{
      Brain.Screen.print("Skills");
    }

    //printf("Gyro: %f\n",baseInetrial);
    //printf("Lift: %f\n",liftSensor);
    printf("Tilt: %f\n\n",tiltSensor);
    //printf("Range: %f\n",RangeFinderE.distance(inches));
    vex::task::sleep(100);
  }
}
