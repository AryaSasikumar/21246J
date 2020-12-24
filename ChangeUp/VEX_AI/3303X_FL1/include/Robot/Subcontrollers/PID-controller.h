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
    float Kp = 0.05;
    float Ki = 0.0011;
    float Kd = 0.3;
    float turnKp = 0.7;
    float turnKi = 0.0006;
    float turnKd = 0.5;
    int Dt=15;
    float error;
    float speed;
    float integral;
    float derivative;
    float prevError;
  public:
    void pidDriveLoop(int setpoint);
    void pidDriveBackLoop(int setpoint);
    void pidTurnRightLoop(int setpoint);
    void pidTurnLeftLoop(int setpoint);
    bool pidRun;
};

#endif
/*---PID_CONTROLLER_H---*/