/*---BASE_H---*/
#ifndef BASE_H
#define BASE_H
/*----------------------------------------------------------------------------*/
/*    Module:       Base.h                                                    */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

#include "../../Configuration/general-definitions.h"

#include "../Subcontrollers/PID-controller.h"

const double wheelDiameterIN  = 4;
const double BaseDiameterIN  = 16.5;

class Base{
  private:
    double _wheel_diameter;
    double _wheel_travel;
    double _track_width;
    double _wheel_base;
    double _default_speed;

    PID_Controller PID_forward;
    PID_Controller PID_backward;
    PID_Controller PID_left;
    PID_Controller PID_right;
  //protected:
    //TODO: Unit Conversion
  public:
    bool toggle = false;

    //Constructors
    Base();
    //User-Control-Loop
    void user_control();

    void turnToPoint(double x, double y);

    //TODO: PID
    //Autonomous Functions
    void drivePID(double max_left_velocity, double max_right_velocity, double distance);
    void turnPID(double max_left_velocity, double max_right_velocity, double angle);

    /*---Full-Drive-Movement---*/
    void drive_for(double distance, double velocity, bool do_finish);
    void turn_for(double angle, double velocity, bool do_finish);

    /*---Raw-Motor-Movement---*/
    void rotate_motors_for(double left_value, double right_value, double velocity, bool do_finish);

    /*---Left-Drive-Spin---*/
    void left_spin(double velocity);
    void left_spin(double velocity, vex::breakType break_type);
    /*---Right-Drive-Spin---*/
    void right_spin(double velocity);
    void right_spin(double velocity, vex::breakType break_type);
    /*---Full-Drive-Spin---*/
    void drive_spin(double velocity);
    void drive_spin(double left_velocity, double right_velocity);
    void drive_stop(vex::breakType break_type);
};

#endif
/*---BASE_H---*/