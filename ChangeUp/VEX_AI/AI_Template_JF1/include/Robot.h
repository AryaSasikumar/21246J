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

typedef struct {
	double x, y;
} position;

#ifdef __cplusplus
}
#endif

int rc_auto_loop_task();



class Robot{
  public: 
    Base            base;
    AI::Jetson      jetson_comm; 

    #ifdef MANAGER_ROBOT
    AI::Robot_Link robot_link( vex::PORT12, "robot_32456_1", vex::linkType::manager);
    #else
    AI::Robot_Link robot_link( vex::PORT12, "robot_32456_1", vex::linkType::worker);
    #endif

    double position[2];
    double heading; 
    

    Robot();
    ~Robot();
    double get_x();
    double get_y();
    double get_heading();

    int refresh_position();
    int refresh_heading();

    int change_position(double new_x, double new_y);
    int change_heading(double new_heading);
};

#endif 
/*---ROBOT_H---*/