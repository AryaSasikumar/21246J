/*---PID_CONTROLLER_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       PID-controller.cpp                                        */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Subcontrollers/PID-Controller.h"

/*---Configuration-Includes---*/

#include "vex.h"

//include <vex_timer.h>

PID_Controller::PID_Controller(){ 
  set_constants(0.0, 0.0, 0.0, 0);
}

PID_Controller::PID_Controller(double Kp, double Ki, double Kd, int Dt){
  set_constants(Kp,Ki,Kd,Dt);
}

PID_Controller::~PID_Controller(){}

void PID_Controller::set_constants(double Kp, double Ki, double Kd, int Dt){
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
  _Dt = Dt;
}

int PID_Controller::base_move_loop(double setpoint, double max_velocity, double timeout_ms,  Subsystem *subsystem){
  bool move_complete = false;
  int times_good = 0;
  _integral = 0.0;
  _derivative = 0.0;
  _prevError = 0.0;
  subsystem->pid_stop_func();
  vex::task::sleep(5);
  subsystem->encoder_reset();
  vex::timer timeout_clock;
  timeout_clock.clear();
  while(!move_complete && subsystem->get_encoder_rotation() <= setpoint){
    _error = setpoint - subsystem->get_encoder_rotation();
    _integral = _integral + _error;
    if(_error <= 0.0 || subsystem->get_encoder_rotation() > setpoint){
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
    subsystem->pid_move_func(_velocity);
    if(_error <= 100.0){ 
      times_good++;
    }
    if(times_good >= 100){
      move_complete = true;
    }
    vex::task::sleep(1); 
    if(timeout_clock.time(vex::timeUnits::msec) > timeout_ms){
      return FAILURE;
    }
  }
  subsystem->pid_stop_func();
  return SUCCESS;
}

/*---PID_CONTROLLER_CPP---*/