/*---ROBOT_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       Robot.cpp                                                 */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Robot.h"


Robot::Robot(){}
Robot::~Robot(){}


int rc_auto_loop_task() {
  while (FOREVER){
    myBase.userControl();
  }
  return 0;
}

/*---ROBOT_CPP---*/