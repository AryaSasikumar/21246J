/*---PID_CONTROLLER_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       PID-controller.cpp                                        */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Subcontrollers/PID-Controller.h"

/*---Configuration-Includes---*/
#include <vex_timer.h>
#include "vex.h"


PID_Controller::PID_Controller(){ 
  set_constants(0.0, 0.0, 0.0, 0);
}

PID_Controller::PID_Controller(double Kp, double Ki, double Kd, int Dt){
  set_constants(Kp,Ki,Kd,Dt);
}

void PID_Controller::set_constants(double Kp, double Ki, double Kd, int Dt){
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
  _Dt = Dt;
}

int PID_Controller::base_move_loop(double setpoint, double max_velocity, double timeout_ms, void (Base::*move_func)(double), void (Base::*stop_func)()){
  bool move_complete = false;
  int times_good = 0;
  _integral = 0.0;
  _derivative = 0.0;
  _prevError = 0.0;
  stop_func();
  vex::task::sleep(5);
  ResetDriveEncoders;
  vex::timer::clear();	
  while(!move_complete && DriveEncoderRotation <= setpoint){
    _error = setpoint - DriveEncoderRotation;
    _integral = _integral + _error;
    if(_error <= 0.0 || DriveEncoderRotation > setpoint){
      _integral = 0.0;
    }
    if(_error > setpoint){
      _integral = 0.0;
    }
    _derivative = _error - _prevError;
    _prevError = _error;
    _velocity = ((_error * _Kp) + (_integral * _Ki) + (_derivative * _Kd));
    vex::task::sleep(_Dt);
    if(_velocity > max_velocity){
      _velocity = max_velocity;
    }
    move_func(_velocity);
    if(_error <= 100.0){ 
      times_good++;
    }
    if(times_good >= 100){
      move_complete = true;
    }
    vex::task::sleep(1); 
    if(vex::timer::time(vex::timeUnits::msec) > timeout_ms){
      return FAILURE;
    }
  }
  stop_func();
  return SUCCESS;
}

/*---PID_CONTROLLER_CPP---*/