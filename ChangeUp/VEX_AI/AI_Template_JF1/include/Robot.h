/*---ROBOT_H---*/
#ifndef ROBOT_H
#define ROBOT_H
/*----------------------------------------------------------------------------*/
/*    Module:       Robot.h                                                   */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Subsystems/Base.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

//int rc_auto_loop_task();



class Robot{
  public: 
    Base base;

    double position[2];
    double heading; 
    
    Robot();
    ~Robot();
    double get_x();
    double get_y();
    double get_heading();

    int refresh_position(MAP_RECORD *local_map);

    int change_position(double new_x, double new_y, double velocity);
    int change_heading(double new_heading, double velocity);
};

#endif 
/*---ROBOT_H---*/