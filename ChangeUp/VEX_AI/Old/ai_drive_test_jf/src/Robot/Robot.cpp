#include "vex.h"

Robot::Robot(){
  refresh_place();
}

Place Robot::get_place(){ return place; }

void Robot::refresh_place(){ 
  link.get_local_location(place.point.x, place.point.y, place.heading);
}

int Robot::go_to_place(float x_new, float y_new, float heading_new){
  refresh_place();
  Place place_new = {{x_new, y_new}, heading_new};
  Move_Vector move_instruction= calc_move_vector(place_new);
  Drive.turnFor(right, move_instruction.heading , degrees); //TODO-----------------------
  //Drivetrain.driveFor(forward, move_instruction.distance, inches);
  return 1;
}

Move_Vector Robot::calc_move_vector(Place place_new){
  Move_Vector result_vector;
  float x_diff = place_new.point.x - place.point.x;
  float y_diff = place_new.point.y - place.point.y;

  result_vector.distance = sqrt(pow(x_diff,2) + pow(y_diff,2) * 1.0);
  result_vector.heading = (atan2(y_diff, x_diff)*180.0/PI);
  return result_vector;
}
