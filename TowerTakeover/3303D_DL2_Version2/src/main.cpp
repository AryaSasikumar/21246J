/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    16, 19, 9, 10, 12
// liftA                motor         6               
// liftB                motor         7               
// rightIntake          motor         15              
// leftIntake           motor         20              
// baseEncoder          encoder       G, H            
// Gyro                 gyro          C               
// Bumper               bumper        B               
// liftPot              pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----

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
  baseEncoder.resetRotation();
  TurnGyroSmart.resetHeading();
  task::sleep(200);
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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  myIntake.Spin(100);
  myBase.drivePID(45, 45, 42);
  task::sleep(50);
  myBase.turnPID(100, 100, -35);
  task::sleep(50);
  myBase.driveBackPID(-75, -75, -38);
  task::sleep(100);
  myBase.turnPID(85, 85, 39);
  task::sleep(50);
  myBase.drivePID(45, 45, 36);
  myIntake.Spin(30);
  myBase.turnPID(90, 90, -132);
  task::sleep(50);
  myBase.drivePID(80, 80, 48);
  task::sleep(100);
  myIntake.Spin(-5);
  while(tiltSensor>=90){
    myLift.Spin(90, -90);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.drivePID(30, 30, 3);
  myBase.driveBackPID(-30, -30, -24);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
}



/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  enableAutonTestButton = true; //Will enable Y button as an Auton Test Button
  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  while (1) {
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
    //printf("Lift: %f\n",liftSensor);
    //printf("Tilt: %f\n\n",tiltSensor);
    wait(100, msec);
  }
}
