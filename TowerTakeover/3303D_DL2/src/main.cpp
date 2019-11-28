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
  /*baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(50,50, -459);  //450 Gyro units is about 90 degrees 

  myLift.liftUp(900, 100, 100);
  myLift.liftDown(500, 60, 100);

  myLift.tiltForward(50, 100, 200); */

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
  pre_auton(); //baseGyro

    /*while(true) {
      if(Brain.Battery.capacity(percentUnits::pct) <= 50){
        Controller1.rumble("-.-.-.-");
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.print("BATTERY LOW!");
        vex::task::sleep(1000);
      }
      //printf("gyroVal: %ld\n",baseGyro);
      vex::task::sleep(5);//Sleep the task for a short amount of time to prevent wasted resources.
    }  */  
       
      
  //Prevent main from exiting with an infinite loop.                        
  while(true){
    printf("gyroVal: %f\n",liftPot.value(vex::rotationUnits::deg));  
    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }   
}


