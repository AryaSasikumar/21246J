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
  heading = local_map->pos.az * 180.0/PI;
  return SUCCESS;
}

int Robot::change_position(double new_x, double new_y, double velocity){
  //double a[] = {cos(heading*PI/180.0),sin(heading*PI/180.0)};
  double b[] = {new_x-position[0],new_y-position[1]};
  double B = sqrt(pow(b[0],2) + pow(b[1],2)) * 1.0;
  //double theta = acos(((a[0]*b[0])+(a[1]*b[1]))/B);
  double theta = (atan2(b[0], b[1])*180.0/PI);
  FILE *fp = fopen("/dev/serial2","wb");
  fprintf(fp, "\nOld: (%.2f,%.2f) | New: (%.2f,%.2f)\n", position[0] , position[1], b[0], b[1]);
  fprintf(fp, "Heading: %.2f | Theta: %.2f\n", heading, theta);
  fclose(fp);
  change_heading(0.0, velocity);
  vex::wait(200, vex::timeUnits::msec);
  base.turn_for(theta/2, velocity, true); 
  vex::wait(200, vex::timeUnits::msec);
  base.drive_for(B*0.06, velocity, true);
  return SUCCESS;
}
int Robot::change_heading(double new_heading, double velocity){
  //FILE *fp = fopen("/dev/serial2","wb");
  double rotate_amount = (new_heading - heading);
  //fprintf(fp, "Selected Heading: %.5f | Old Heading: %.5f | Rot Amnt: %.5f \n", new_heading, heading,rotate_amount);
  base.turn_for(rotate_amount/2, velocity, true); 
  //fprintf(fp, "New Heading: %.5f\n\n", heading);
  //fclose(fp);
  return SUCCESS;
}

// int rc_auto_loop_task() {
//   while (FOREVER){
//     myBase.userControl();
//   }
//   return 0;
// }

/*---ROBOT_CPP---*/

//  2400 u * 1 ft  * 
//  12  ft   12 in 

//  16.6666667 u/in
//  0.06 in/u