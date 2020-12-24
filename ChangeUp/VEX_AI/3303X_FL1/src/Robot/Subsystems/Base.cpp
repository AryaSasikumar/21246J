/*---BASE_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       Base.cpp                                                  */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*    Description:  This class is meant to be a flexible way to control any   */
/*                  robot base with maximum ease.                             */
/*----------------------------------------------------------------------------*/
#include "Robot/Subsystems/Base.h"

#include "vex.h"

Base::Base(){ 
  _wheel_diameter = WHEEL_DIAMETER;
  _wheel_travel = _wheel_diameter * PI;
  _track_width = TRACK_WIDTH;
  _wheel_base = WHEEL_BASE;
  _default_speed = DEFAULT_SPEED;

  PID_forward.set_constants(FWD_KP, FWD_KI, FWD_KD, FWD_DT);
  PID_backward.set_constants(BWD_KP, BWD_KI, BWD_KD, BWD_DT);
  PID_left.set_constants(LEFT_KP, LEFT_KI, LEFT_KD, LEFT_DT);
  PID_right.set_constants(RIGHT_KP, RIGHT_KI, RIGHT_KD, RIGHT_DT);
}

/*---User-Control-Loop---*/
void Base::user_control(){
  double velocity_divider = 1; 
  if(toggle == true){ velocity_divider = 2; }
  if(abs(Y_RIGHT_JOY) > Y_RIGHT_JOY_BUFFER){ right_spin(Y_RIGHT_JOY/velocity_divider); }
  else{ right_spin(0); } 
  if(abs(Y_LEFT_JOY) > Y_LEFT_JOY_BUFFER){ left_spin(Y_LEFT_JOY/velocity_divider); }
  else{ left_spin(0); } 
}

//---------------------------------------------------------------//
//↓↓↓↓↓---------ULTRA-SMART-DRIVE-CONTROL-FUNCTIONS---------↓↓↓↓↓//

//TODO: Absolute-Field-Position-Movement
/*---Absolute-Field-Position-Movement---*/
void Base::turnToPoint(float x, float y){
  float place[3]; 
  //link.get_local_location(place[0], place[1], place[2]);
  float diff[] = {x - place[0], y - place[1]};

  float distance = sqrt(pow(diff[0],2) + pow(diff[1],2) * 1.0);
  float heading = (atan2(diff[1], diff[0])*180.0/3.14159265);
  //turnDegrees_MotorEnc
}

//↑↑↑↑↑---------ULTRA-SMART-DRIVE-CONTROL-FUNCTIONS---------↑↑↑↑↑//
//---------------------------------------------------------------//
//↓↓↓↓↓------------SMART-DRIVE-CONTROL-FUNCTIONS------------↓↓↓↓↓//

//TODO: PID

//↑↑↑↑↑------------SMART-DRIVE-CONTROL-FUNCTIONS------------↑↑↑↑↑//
//---------------------------------------------------------------//
//↓↓↓↓↓---------SEMI-SMART-DRIVE-CONTROL-FUNCTIONS----------↓↓↓↓↓//

/*---Full-Drive-Movement---*/
void Base::drive_for(double distance, double velocity, bool do_finish = true){
  Drive.driveFor(distance,DEFAULT_DIST_UNITS,velocity,DEFAULT_VEL_UNITS,do_finish);
}
void Base::turn_for(double angle, double velocity, bool do_finish = true){
  Drive.turnFor(angle,DEFAULT_ROT_UNITS,velocity,DEFAULT_VEL_UNITS,do_finish);
}

//↑↑↑↑↑---------SEMI-SMART-DRIVE-CONTROL-FUNCTIONS----------↑↑↑↑↑//
//---------------------------------------------------------------//
//↓↓↓↓↓----------SEMI-DUMB-DRIVE-CONTROL-FUNCTIONS----------↓↓↓↓↓//

/*---Raw-Motor-Movement---*/
void Base::rotate_motors_for(double left_value, double right_value, double velocity, bool do_finish = true){
  LeftDrive.rotateFor(left_value,DEFAULT_ROT_UNITS,velocity,DEFAULT_VEL_UNITS, false); //TODO: Test to make sure works. Might need startRotateFor
  RightDrive.rotateFor(right_value,DEFAULT_ROT_UNITS,velocity,DEFAULT_VEL_UNITS, do_finish);
}

//↑↑↑↑↑----------SEMI-DUMB-DRIVE-CONTROL-FUNCTIONS----------↑↑↑↑↑//
//---------------------------------------------------------------//
//↓↓↓↓↓-------------DUMB-DRIVE-CONTROL-FUNCTIONS------------↓↓↓↓↓//

/*---Left-Drive-Spin---*/
void Base::left_spin(double velocity = 0.0){ left_spin(velocity, DEFAULT_DRIVE_STOP_TYPE); }
void Base::left_spin(double velocity, vex::breakType break_type){
  if(velocity != 0.0){ LeftDrive.spin(DEFAULT_DIRECTION_TYPE, velocity, DEFAULT_VEL_UNITS); } 
  else{ LeftDrive.stop(break_type); }
}
/*---Right-Drive-Spin---*/
void Base::right_spin(double velocity = 0.0){ right_spin(velocity, DEFAULT_DRIVE_STOP_TYPE); }
void Base::right_spin(double velocity, vex::breakType break_type){
  if(velocity != 0.0){ RightDrive.spin(DEFAULT_DIRECTION_TYPE, velocity, DEFAULT_VEL_UNITS); }
  else{ RightDrive.stop(break_type); }
}
/*---Full-Drive-Spin---*/
void Base::drive_spin(double velocity){ drive_spin(velocity); }
void Base::drive_spin(double left_velocity, double right_velocity){
  left_spin(left_velocity);
  right_spin(right_velocity);
}
void Base::drive_stop(vex::breakType break_type = DEFAULT_STOP_TYPE){
  LeftDrive.stop(break_type);
  RightDrive.stop(break_type);
}

//↑↑↑↑↑-------------DUMB-DRIVE-CONTROL-FUNCTIONS------------↑↑↑↑↑//
//---------------------------------------------------------------//
//↓↓↓↓↓--------------UNIT-CONVERSION-FUNCTIONS--------------↓↓↓↓↓//

/*---Unit-Conversion---*/
// float Base::inches_to_ticks(float inchesGiven){ //TODO: MAKE WORK
//   int wheelRadIN = 2; //TODO: CHANGE
//   float floatDiv = (float)95.0/36.0;
//   float Distance = ((inchesGiven/(M_PI*wheelRadIN))*(360*floatDiv))/4;
//   return Distance; //Distance in ticks    
// }

//↑↑↑↑↑--------------UNIT-CONVERSION-FUNCTIONS--------------↑↑↑↑↑//


/*---BASE_CPP---*/