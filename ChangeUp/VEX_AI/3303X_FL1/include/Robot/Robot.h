/*---ROBOT_H---*/
#ifndef ROBOT_H
#define ROBOT_H
/*----------------------------------------------------------------------------*/
/*    Module:       Robot.h                                                   */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "../Configuration/general-definitions.h"

#include "Subsystems/Base.h"
#include "Subsystems/Intake.h"

int rc_auto_loop_task();

class Robot{
  private:
    float position[2];
    float heading; 

    float dimensions[3] = {17.5, 17.5, 18.0}; 

    vex::distanceUnits primary_d_unit = vex::inches;
    vex::rotationUnits primary_a_unit = vex::degrees;

    Base base;
    Intake intake;
    
  public: 
    Robot();

    float get_x();
    float get_y();
    float get_heading();

    int refresh_position();
    int refresh_heading();

    float set_position(float new_x, float new_y);
    float set_heading(float new_heading);
};

#endif 
/*---ROBOT_H---*/