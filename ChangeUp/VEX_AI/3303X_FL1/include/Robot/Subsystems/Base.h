/*---BASE_H---*/
#ifndef BASE_H
#define BASE_H
/*----------------------------------------------------------------------------*/
/*    Module:       Base.h                                                    */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

#include "vex.h"

#include "Subsystem.h"
#include "../Subcontrollers/PID-controller.h"

class Base : public Subsystem{
  private:
    double _wheel_diameter, _wheel_travel;
    double _track_width, _wheel_base, _robot_radius;
    double _external_gear_ratio;

    PID_Controller PID_forward;
    PID_Controller PID_backward;
    PID_Controller PID_left;
    PID_Controller PID_right;

    PID_BASE_MODE pid_mode = PID_DRIVE;
  public:
    /*---Base-Constructors---*/
    Base(); //Default Constructor
    ~Base();
    /*---User-Control-Loop---*/
    void user_control_tank_drive(); //Tank Drive User Control
    //void user_control_x_drive();  //X Drive User Control
    //void user_control_h_drive();  //H Drive User Control
    //TODO: ADD OTHER USER CONTROL TYPES AS NEEDED HERE!
    /*---Absolute-Field-Position-Movement---*/
<<<<<<< HEAD
    //void turnToPoint(double x, double y);
    virtual int encoder_reset();
    virtual double get_encoder_rotation();
=======
    void turnToPoint(double x, double y);


>>>>>>> parent of edac948... Now Compiling In VEXcode

    /*---PID-Drive-Movement---*/
    virtual int pid_move_func(double velocity);
    virtual int pid_stop_func();

    void pid_drive_for(double distance, double timeout_ms);
    void pid_drive_for(double distance, double max_velocity, double timeout_ms);
    void pid_turn_for(double angle, double timeout_ms);
    void pid_turn_for(double angle, double max_velocity, double timeout_ms);
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
    void turn_spin(double velocity);
    void drive_stop(vex::breakType break_type);
    void drive_coast();
    void drive_brake();
    void drive_hold();
    /*---Unit-Conversion---*/
    double travel_distance_to_motor_degrees(double distance);
    double travel_angle_to_motor_degrees(double angle);
};

#endif
/*---BASE_H---*/