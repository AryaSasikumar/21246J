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

// #include "AI/AI_Jetson.h"
// #include "AI/AI_Robot_Link.h"

int rc_auto_loop_task();

class Robot{
  private:
    double position[2];
    double heading; 
    
  public: 
    Base base;
    // AI::Jetson      jetson_comms;
    // AI::Robot_Link  link;


    Robot();
    ~Robot();
    double get_x();
    double get_y();
    double get_heading();

    int refresh_position();
    int refresh_heading();

    int set_position(double new_x, double new_y);
    int set_heading(double new_heading);
};

#endif 
/*---ROBOT_H---*/