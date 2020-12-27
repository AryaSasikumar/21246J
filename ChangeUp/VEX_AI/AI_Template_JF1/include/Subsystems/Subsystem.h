/*---SUBSYSTEM_H---*/
#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H
/*----------------------------------------------------------------------------*/
/*    Module:       Subsystem.h                                               */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      24 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

class Subsystem{
  public:
    double _default_speed;
    double _velocity_divider;

    Subsystem(){
      _default_speed = 100.0;
      _velocity_divider = 1.0;
    }
    virtual ~Subsystem(){}
    
    virtual int pid_move_func(double velocity) = 0;
    virtual int pid_stop_func() = 0;

    virtual int encoder_reset() = 0;
    virtual double get_encoder_rotation() = 0;
};

#endif
/*---SUBSYSTEM_H---*/