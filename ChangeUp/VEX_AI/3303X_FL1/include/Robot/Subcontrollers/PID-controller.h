/*---PID_CONTROLLER_H---*/
#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
/*----------------------------------------------------------------------------*/
/*    Module:       PID-controller.h                                          */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

class PID_Controller{
  private:
    double _Kp, _Ki, _Kd;
    double _error, _prevError;
    double _integral, _derivative;
    double _velocity;
    int _Dt;
  public:
    PID_Controller();
    PID_Controller(double Kp, double Ki, double Kd, int Dt);
    void set_constants(double Kp, double Ki, double Kd, int Dt);
    int base_move_loop(double setpoint, double max_velocity, double timeout_ms, void (Base::*move_func)(double), void (Base::*stop_func)());
};

#endif
/*---PID_CONTROLLER_H---*/