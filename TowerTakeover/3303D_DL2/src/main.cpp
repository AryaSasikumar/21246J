/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       Dublin Robotics Club                                      */
/*    Created:      Tue Jul 30 2019                                           */
/*    Description:  V5 project                                                */
/*----------------------------------------------------------------------------*/
#include "AutonomusRoutines.h"

using namespace vex;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/
void pre_auton(void) {
  baseGyroReset;
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
  baseGyroReset;
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myAuton.blueFrontAuton();
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/
void usercontrol(void){
  baseGyroReset;
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  while (true){
    myBase.userControl();
    myIntake.userControl();
    myLift.userControl();
    vex::task::sleep(20);
  }
}

// Main will set up the competition functions and callbacks.
int main(){
  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  //Run the pre-autonomous function. 
  pre_auton();
      
  //Prevent main from exiting with an infinite loop.                        
  while(true){
    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }     
}