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
    if(btnX){
      vex::task::sleep(250);
      myBase.useTrueSpeed = !myBase.useTrueSpeed;
    }
    while(btnY){
      baseGyroReset;
      vex::task::sleep(500);
      while(Gyro.isCalibrating()){vex::task::sleep(1);}
      //Intake and drive forward 4 cubes
      myIntake.Spin(100);
      vex::task::sleep(100); 
      //myBase.driveInches_Enc(forwards, 50, 45);
      myBase.drivePID(25, 25, 54);
      vex::task::sleep(250);

      //Turn towards right stack
      //baseGyroReset;
      //vex::task::sleep(500);
      //while(Gyro.isCalibrating()){vex::task::sleep(1);}
      //myBase.turnPID(35,35, 80);
    
      //Drive into stack to intake first cube
      //myBase.drivePID(30, 30, 10);
      vex::task::sleep(1000);

      /*baseGyroReset;
      vex::task::sleep(250);
      while(Gyro.isCalibrating()){vex::task::sleep(1);}
      myBase.turnPID(50,50, -50);
      myBase.drivePID(50, 50, 4);
      vex::task::sleep(1000);
      */
      myIntake.Spin(0);
      while(btnY){
        vex::task::sleep(1000);
      }
      //myBase.turnDegrees_Gyro(300,50);
      //myBase.turnPID(700);
    }
    vex::task::sleep(5); //Sleep the task for a short amount of time to prevent wasted resources. 
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
      if(Brain.Battery.capacity(percentUnits::pct) <= 50){
        Controller1.rumble("-.-.-.-");
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.print("ROBOT BATTERY LOW!");
        vex::task::sleep(1000);
      }
      //printf("gyroVal: %ld\n",Controller1.Axis3.position(percent));
      vex::task::sleep(5);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}