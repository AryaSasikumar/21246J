/*---SUBSYSTEM_H---*/
#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H
/*----------------------------------------------------------------------------*/
/*    Module:       Subsystem.h                                               */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      24 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "../../Configuration/general-definitions.h"

class Subsystem{
    public:
        double _default_speed;
        double _velocity_divider;

        Subsystem(){
            _default_speed = 100.0;
            _velocity_divider = 1.0;
            encoder_reset();
        }
        virtual ~Subsystem(){}
        
        virtual int pid_move_func(double velocity) = SUCCESS;
        virtual int pid_stop_func() = SUCCESS;

        virtual int encoder_reset() = SUCCESS;
        virtual double get_encoder_rotation() = SUCCESS;
};

#endif
/*---SUBSYSTEM_H---*/