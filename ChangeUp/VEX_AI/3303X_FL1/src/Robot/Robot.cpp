/*---ROBOT_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       Robot.cpp                                                 */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Robot.h"

Robot::Robot(){}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
Robot::Robot(){}
>>>>>>> parent of edac948... Now Compiling In VEXcode
=======
Robot::Robot(){}
>>>>>>> parent of edac948... Now Compiling In VEXcode
=======
Robot::Robot(){}
>>>>>>> parent of edac948... Now Compiling In VEXcode
Robot::~Robot(){}

double Robot::get_x(){ return position[0]; };
double Robot::get_y(){ return position[1]; };
double Robot::get_heading(){ return heading; };

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
int Robot::refresh_position(){
  return SUCCESS;
}

int Robot::refresh_heading(){
  return SUCCESS;
}

int Robot::set_position(double new_x, double new_y){
  return SUCCESS;
}
int Robot::set_heading(double new_heading){
  return SUCCESS;
=======
=======
>>>>>>> parent of edac948... Now Compiling In VEXcode
=======
>>>>>>> parent of edac948... Now Compiling In VEXcode
int rc_auto_loop_task() {
  while (FOREVER){
    myBase.userControl();
  }
  return 0;
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of edac948... Now Compiling In VEXcode
=======
>>>>>>> parent of edac948... Now Compiling In VEXcode
=======
>>>>>>> parent of edac948... Now Compiling In VEXcode
}

/*---ROBOT_CPP---*/