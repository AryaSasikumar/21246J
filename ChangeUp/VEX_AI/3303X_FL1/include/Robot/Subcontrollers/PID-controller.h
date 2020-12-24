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
    float _Kp = 0.05;
    float _Ki = 0.0011;
    float _Kd = 0.3;
    float _turnKp = 0.7;
    float _turnKi = 0.0006;
    float _turnKd = 0.5;
    int _Dt = 15;
    float _error;
    float _speed;
    float _integral;
    float _derivative;
    float _prevError;
  public:
    PID_Controller(float Kp, float Ki, float Kd, int Dt);
    void move_loop(int setpoint, void (*move_func)(float speed), void (*stop_func)());
    //void pidDriveBackLoop(int setpoint);
    //void pidTurnRightLoop(int setpoint);
    //void pidTurnLeftLoop(int setpoint);
    //bool pidRun;
};

#endif
/*---PID_CONTROLLER_H---*/