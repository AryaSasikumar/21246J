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

int Robot::refresh_position(MAP_RECORD *local_map){
  position[0] = local_map->pos.x;
  position[1] = local_map->pos.y;
  heading = local_map->pos.az;
  return SUCCESS;
}

int Robot::change_position(double new_x, double new_y, double velocity){
  double diff[] = {new_x - position[0], new_y - position[1]};
  double distance = sqrt(pow(diff[0],2) + pow(diff[1],2) * 1.0);
  double heading = (atan2(diff[1], diff[0])*180.0/3.14159265);
  change_heading(heading, velocity);
  base.drive_for(distance, velocity, true);
  return SUCCESS;
}
int Robot::change_heading(double new_heading, double velocity){
  double rotate_amount = (new_heading - heading)*180.0/3.14159265;
  base.turn_for(rotate_amount, velocity, true);
  return SUCCESS;
}

// int rc_auto_loop_task() {
//   while (FOREVER){
//     myBase.userControl();
//   }
//   return 0;
// }

/*---ROBOT_CPP---*/