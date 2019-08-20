/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       aryasasikumar                                             */
/*    Created:      Mon Jul 22 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "tilter.h"

using namespace vex;


// A global instance of vex::brain used for printing to the V5 brain screen

// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  baseGyroReset;
  while(Gyro.isCalibrating()){}
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  myBase.turnDegrees_Gyro(600,100);
  //myBase.turnPID(658.0);
  //myBase.turnPID(180.0);
  //myTilter.robotDeploy();
  //myIntake.Spin(100);
  //myBase.drivePID(48);
  //vex::task::sleep(1000);
  //myIntake.Spin(0);
  //myBase.drivePID(-46);
  //blueAuton();
  //redAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  tilt1.resetRotation();
  baseGyroReset;
  while(Gyro.isCalibrating()){}
  while(true){
    myBase.userControl();
    myTilter.userControl();
    myIntake.userControl();
    if(Controller1.ButtonY.pressing()){
      
      //myBase.driveInches_Enc(forwards, 40, 100);
      //----------------------------------------
      //myTilter.robotDeploy();  
      //vex::task::sleep(5000);        
      //myIntake.Spin(100);
      //myBase.drivePID(60,45);
      //vex::task::sleep(500);
      //myBase.turnPID(100);
      //myIntake.Spin(0);
      //----------------------------------------
      //myBase.drivePID(-46);
      myBase.turnDegrees_Gyro(300,50);
      //myBase.turnPID(700);
    }
    vex::task::sleep(1); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(true) {
      printf("gyroVal: %li\n",baseGyro);
      vex::task::sleep(1);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}