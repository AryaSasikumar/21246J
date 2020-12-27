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
#include "AI/AI_Jetson.h"
#include "AI/AI_Robot_Link.h"

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

    int change_position(double new_x, double new_y);
    int change_heading(double new_heading);
};

#endif 
/*---ROBOT_H---*/