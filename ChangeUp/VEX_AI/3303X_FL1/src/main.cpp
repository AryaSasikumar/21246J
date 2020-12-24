/*---MAIN_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

/*---Configuration-Includes---*/
#include "vex.h"
/*-------User-Includes-------*/
#include "Robot/Robot.h"


vex::competition Competition;

/*---Pre-Autonomous---*/
void pre_auton(void){ vexcodeInit(); }
/*-----Autonomous-----*/
void autonomous(void){ /*TODO*/ }
/*----User-Control----*/
void usercontrol(void){
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
  ENABLE_AUTON_TEST_BUTTON = false;// ENABLE FOR Y-BUTTON AS AUTON TEST BUTTON!//
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
  vex::task drive_task(rc_auto_loop_task);
  while(FOREVER){ wait(20, vex::msec); }// Sleep to prevent wasted resources.
}

int main(){
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while(FOREVER){
    //Use this loop for printf testing. EX: printf("Sensor Name: %d\n", sensor.value());
    vex::task::sleep(100);
  }
}

/*---MAIN_CPP---*/