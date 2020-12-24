/*---BASE_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       Base.cpp                                                  */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Subsystems/Base.h"

#include "vex.h"

#include "Configuration/robot-config.h" 

Base::Base(float wheel_diameter = 3.25, float track_width = 17.5, float wheel_base = 13.5, vex::distanceUnits d_units = vex::distanceUnits::in, int default_speed = 100){
  _wheel_diameter = wheel_diameter;
  _wheel_travel = wheel_diameter * PI;
  _track_width = track_width;
  _wheel_base = wheel_base;
  _distance_units = d_units;
  _default_speed = default_speed;
}

void Base::right_spin(int speed = 0, vex::breakType break_type = vex::brakeType::coast){
  if(speed != 0){
    RightDrive.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    RightDrive.stop(break_type); 
  }
}

void Base::left_spin(int speed = 0, vex::breakType break_type = vex::brakeType::coast){
  if(speed != 0){
    LeftDrive.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    LeftDrive.stop(break_type);  
  }
}

void Base::drive_spin(int left_speed, int right_speed){
  left_spin(left_speed);
  right_spin(right_speed);
}

void Base::drive_stop(vex::breakType break_type = vex::brakeType::coast) {
  LeftDrive.stop(break_type);
  RightDrive.stop(break_type);
}

void Base::move_for_degrees(float left_degrees, float right_degrees, int speed){
  LeftDrive.rotateFor(left_deg,degrees,speed,velocityUnits::percent);
  RightDrive.rotateFor(right_deg,degrees,speed,velocityUnits::percent);
}

void Base::user_control(int buffer_size){
  unsigned int left_speed, right_speed;
  if(toggle == true){
    left_speed = half_speed[abs(Y_Left_Joy)];
    right_speed = half_speed[abs(Y_Right_Joy)];
  }else{
    left_speed = true_speed[abs(Y_Left_Joy)];
    right_speed = true_speed[abs(Y_Right_Joy)];
  }

  if(Y_Right_Joy > buffer_size){ rightSpin(right_speed); }
  else if(Y_Right_Joy < -buffer_size){ rightSpin(-right_speed); }
  else{ rightSpin(0); } 

  if(Y_Left_Joy > buffer_size){ leftSpin(left_speed); }
  else if(Y_Left_Joy < -buffer_size){ leftSpin(-left_speed); }
  else{ leftSpin(0); } 
}

float Base::inches_to_ticks(float inchesGiven){
  int wheelRadIN = 2; //TODO: CHANGE
  float floatDiv = (float)95.0/36.0;
  float Distance = ((inchesGiven/(M_PI*wheelRadIN))*(360*floatDiv))/4;
  return Distance; //Distance in ticks    
}


void Base::drive_inches(direction_t mydirection, float travelTargetIN, int speed){
  float circumference = wheelDiameterIN * M_PI;
  float degreesToRotate = (360 * travelTargetIN) / circumference;
  if(mydirection == forwards){
    moveFor(degreesToRotate,degreesToRotate, speed);
  }else if(mydirection == backwards){
    moveFor(degreesToRotate*-1,degreesToRotate*-1, speed);
  }
}

void Base::turn_degrees(turn_t mydirection, float travelTargetDEG, int speed){
  float BaseCircumference = BaseDiameterIN * M_PI; //51.81
  float degreesToRotate = ((360 * travelTargetDEG) / BaseCircumference)/2; // 32,400
  if(mydirection == Right){
    moveFor(degreesToRotate,degreesToRotate*-1, speed);
  }
  else if(mydirection == Left){
    moveFor(degreesToRotate*-1,degreesToRotate, speed);
  }
}

void Base::drive(float degrees, int speed){
  moveFor(degrees, degrees, speed);
}

void Base::turn(float leftDegrees, float rightDegrees,int speed){
  moveFor(leftDegrees, rightDegrees, speed);
}

void Base::turnToPoint(float x, float y){
  float place[3]; 
  //link.get_local_location(place[0], place[1], place[2]);
  float diff[] = {x - place[0], y - place[1]};

  float distance = sqrt(pow(diff[0],2) + pow(diff[1],2) * 1.0);
  float heading = (atan2(diff[1], diff[0])*180.0/3.14159265);
  //turnDegrees_MotorEnc
}

/*---BASE_CPP---*/