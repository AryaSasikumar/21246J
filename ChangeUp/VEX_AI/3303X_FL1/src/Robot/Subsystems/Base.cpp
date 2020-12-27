/*---BASE_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       Base.cpp                                                  */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Subsystems/Base.h"

<<<<<<< HEAD
=======
#include "vex.h"

>>>>>>> parent of edac948... Now Compiling In VEXcode
Base::Base(){ 
  _wheel_diameter = WHEEL_DIAMETER;
  _wheel_travel = _wheel_diameter * PI;
  _track_width = TRACK_WIDTH;
  _wheel_base = WHEEL_BASE;
  _external_gear_ratio = EXTERAL_GEAR_RATIO;
  _robot_radius = (sqrt(pow((_track_width/2),2)+pow((_wheel_base/2),2)));

  _default_speed = DEFAULT_SPEED;
  
  PID_forward.set_constants(FWD_KP, FWD_KI, FWD_KD, FWD_DT);
  PID_backward.set_constants(BWD_KP, BWD_KI, BWD_KD, BWD_DT);
  PID_left.set_constants(LEFT_KP, LEFT_KI, LEFT_KD, LEFT_DT);
  PID_right.set_constants(RIGHT_KP, RIGHT_KI, RIGHT_KD, RIGHT_DT);
}

Base::~Base(){}

/*---User-Control-Loop---*/
void Base::user_control_tank_drive(){ 
<<<<<<< HEAD
  if(abs(Y_RIGHT_JOY) > Y_RIGHT_JOY_BUFFER){ 
    right_spin(Y_RIGHT_JOY/_velocity_divider); 
  }else{ 
    right_spin(0); 
  } 
  if(abs(Y_LEFT_JOY) > Y_LEFT_JOY_BUFFER){ 
    left_spin(Y_LEFT_JOY/_velocity_divider); 
  }
  else{ 
    left_spin(0.0); 
  } 
=======
  if(abs(Y_RIGHT_JOY) > Y_RIGHT_JOY_BUFFER){ right_spin(Y_RIGHT_JOY/_velocity_divider); }
  else{ right_spin(0); } 
  if(abs(Y_LEFT_JOY) > Y_LEFT_JOY_BUFFER){ left_spin(Y_LEFT_JOY/_velocity_divider); }
  else{ left_spin(0); } 
>>>>>>> parent of edac948... Now Compiling In VEXcode
}
//TODO: ADD OTHER USER CONTROL TYPES AS NEEDED HERE!
//  EX) XDRIVE, HDRIVE, etc

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

void Base::turn_spin(double velocity){ drive_spin(velocity, -velocity); }

int Base::pid_move_func(double velocity){
<<<<<<< HEAD
  if(pid_mode == PID_TURN){ drive_spin(velocity); }
  else{ turn_spin(velocity); }
  return SUCCESS;
=======
  if(pid_mode == PID_TURN){
    drive_spin(velocity);
  }else{
    turn_spin(velocity);
  }
>>>>>>> parent of edac948... Now Compiling In VEXcode
}

int Base::pid_stop_func(){
  drive_brake();
}

int encoder_reset(){
  LeftDrive.resetRotation();
  RightDrive.resetRotation();
  return SUCCESS;
}

double get_encoder_rotation(){
  return ((LeftDrive.rotation(DEFAULT_ROT_UNITS)+RightDrive.rotation(DEFAULT_ROT_UNITS))/2);
}

/*---PID-Drive-Movement---*/
void Base::pid_drive_for(double distance, double timeout_ms){
  pid_drive_for(distance, _default_speed, timeout_ms);
}
void Base::pid_drive_for(double distance, double max_velocity, double timeout_ms){
  pid_mode = PID_DRIVE;
  double setpoint = travel_distance_to_motor_degrees(distance);
  if(distance > 0.0){
    PID_forward.base_move_loop(setpoint, max_velocity, timeout_ms, this);
  }else if(distance < 0.0){
    PID_backward.base_move_loop(setpoint, max_velocity, timeout_ms, this);
  }
}
void Base::pid_turn_for(double angle, double timeout_ms){
  pid_turn_for(angle, _default_speed, timeout_ms);
}
void Base::pid_turn_for(double angle, double max_velocity, double timeout_ms){
  pid_mode = PID_TURN;
  double setpoint = travel_angle_to_motor_degrees(angle);
  if(angle > 0.0){
    PID_right.base_move_loop(setpoint, max_velocity, timeout_ms, this);
  }else if(angle < 0.0){
    PID_left.base_move_loop(setpoint, max_velocity, timeout_ms, this);
  }
}

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
void Base::turn_spin(double velocity){ drive_spin(velocity, -velocity); }
void Base::drive_spin(double left_velocity, double right_velocity){
  left_spin(left_velocity);
  right_spin(right_velocity);
}
void Base::drive_stop(vex::breakType break_type = DEFAULT_STOP_TYPE){
  LeftDrive.stop(break_type);
  RightDrive.stop(break_type);
}
void Base::drive_coast(){ drive_stop(vex::brakeType::coast); }
void Base::drive_brake(){ drive_stop(vex::brakeType::brake); }
void Base::drive_hold(){ drive_stop(vex::brakeType::hold); }

//↑↑↑↑↑-------------DUMB-DRIVE-CONTROL-FUNCTIONS------------↑↑↑↑↑//
//---------------------------------------------------------------//
//↓↓↓↓↓--------------UNIT-CONVERSION-FUNCTIONS--------------↓↓↓↓↓//

/*---Unit-Conversion---*/
double Base::travel_distance_to_motor_degrees(double distance){
  return (distance*_wheel_travel)/(360.0*_external_gear_ratio);   
}
double Base::travel_angle_to_motor_degrees(double angle){
  return travel_distance_to_motor_degrees(PI*_robot_radius*angle/180.0);
}

//↑↑↑↑↑--------------UNIT-CONVERSION-FUNCTIONS--------------↑↑↑↑↑//

/*---BASE_CPP---*/