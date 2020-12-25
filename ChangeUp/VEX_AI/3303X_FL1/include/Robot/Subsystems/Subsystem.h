/*---SUBSYSTEM_H---*/
#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H
/*----------------------------------------------------------------------------*/
/*    Module:       Subsystem.h                                               */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      24 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

class Subsystem{
    private:
    public:
        Subsystem(){

        }
        virtual ~Subsystem(){

        }
        virtual int move_func(double velocity) = 0;
        virtual int stop_func() = 0;
};

#endif
/*---SUBSYSTEM_H---*/