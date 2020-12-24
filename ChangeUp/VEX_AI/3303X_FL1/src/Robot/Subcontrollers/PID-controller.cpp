/*---PID_CONTROLLER_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       PID-controller.cpp                                        */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Subcontrollers/PID-Controller.h"

/*---Configuration-Includes---*/
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

bool PID_Controller::move_loop(int setpoint, void (*move_func)(double speed), void (*stop_func)()){
  bool moveComplete = false;
  int timesGood = 0;
  _integral = 0.0;
  _derivative = 0.0;
  _prevError = 0.0;
  ResetDriveEncoders;
  while(!moveComplete && DriveEncoderRotation <= setpoint){
    _error = setpoint-DriveEncoderRotation;
    _integral = _integral + _error;
    if(_error <= 0 || DriveEncoderRotation > setpoint){
      _integral = 0;
    }
    if(_error > setpoint){
      _integral = 0;
    }
    _derivative = _error - _prevError;
    _prevError = _error;
    _speed = ((_error * _Kp) + (_integral * _Ki) + (_derivative * _Kd));
    vex::task::sleep(_Dt);

    move_func(_speed);//robot.spin(fwd,speed,pct);

    if(_error <= 100){ 
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    vex::task::sleep(1); 
  }
  stop_func();
  return SUCCESS;
}

//PID_Controller(double min, double max, double Kp, double Ki, double Kd, double dt);
// PID_Controller drive(-100.0, 100.0, 0.070, 0.0000600, 0.060, 0.0001);   LAST YEAR BOT
// PID_Controller turn(-100.0, 100.0, 0.750, 0.0000080, 0.200, 0.0001);    LAST YEAR BOT

//PID_Controller drive(-100.0, 100.0, 0.060, 0.0000300, 0.045, 0.0001);
//PID_Controller turn(-100.0, 100.0, 2.500, 0.0000300, 0.050, 0.0001);     //   NEWWWWW

// PID_Controller drive(-100.0, 100.0, 0.07, 0.0003, 0.006, 0);
// PID_Controller turn(-100.0, 100.0, 0.750, 0.0000080, 0.200, 0.0001); LATEST




//PID_Controller drive(-100.0, 100.0, 0.07, 0.000001, 0.081, 0.0001); today test

/*---PID_CONTROLLER_CPP---*/