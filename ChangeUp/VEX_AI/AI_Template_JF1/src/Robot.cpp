/*---ROBOT_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       Robot.cpp                                                 */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "Robot.h"

Robot::Robot(){}

Robot::~Robot(){}

double Robot::get_x(){ return position[0]; };
double Robot::get_y(){ return position[1]; };
double Robot::get_heading(){ return heading; };

int Robot::refresh_position(){
  return SUCCESS;
}

int Robot::refresh_heading(){
  return SUCCESS;
}

int Robot::change_position(double new_x, double new_y){
  return SUCCESS;
}
int Robot::change_heading(double new_heading){
  return SUCCESS;
}

// int rc_auto_loop_task() {
//   while (FOREVER){
//     myBase.userControl();
//   }
//   return 0;
// }

/*---ROBOT_CPP---*/