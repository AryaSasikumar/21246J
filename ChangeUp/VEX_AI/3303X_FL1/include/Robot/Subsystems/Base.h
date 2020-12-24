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

const float wheelDiameterIN  = 4;
const float BaseDiameterIN  = 16.5;

class Base{
  private:
    float _wheel_diameter = 3.25;
    float _wheel_travel = 10.21;
    float _track_width = 17.5;
    float _wheel_base = 13.5;
    float externa;
    vex::distanceUnits _distance_units;

    int _default_speed = 100;
    const unsigned int true_speed[128] = {
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0 , 21, 21, 21, 22, 22, 22, 23, 24, 24,
      25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
      28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
      33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
      37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
      41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
      46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
      52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
      61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
      71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
      80, 83, 84, 86, 86, 87, 87, 88, 88, 90,
      90, 90, 95, 95, 95,100,100,100};

    const unsigned int half_speed[128] = {
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0 , 10, 10, 10, 11, 11, 11, 12, 12, 12,
      13, 13, 13, 13, 13, 13, 14, 14, 14, 14,
      14, 15, 15, 15, 15, 16, 16, 16, 16, 16,
      17, 17, 17, 17, 17, 17, 17, 18, 18, 19,
      19, 19, 19, 19, 19, 20, 20, 20, 20, 20,
      21, 21, 21, 21, 22, 22, 22, 23, 23, 23,
      23, 24, 24, 24, 24, 25, 25, 25, 26, 26,
      26, 27, 27, 27, 28, 29, 29, 29, 30, 30,
      31, 32, 32, 32, 33, 33, 34, 34, 34, 35,
      36, 36, 36, 37, 37, 38, 39, 39, 39, 39,
      40, 42, 42, 43, 43, 44, 44, 44, 44, 45,
      45, 45, 48, 48, 48, 50, 50, 50};
  protected:
    float inches_to_ticks(float inchesGiven);
  public:
    PID_Controller myPID;
    bool useTrueSpeed = true;
    bool toggle = false;
    bool rightFirst=false;
    bool leftFirst=false;

    //Constructors
    Base(float wheel_diameter, float track_width, float wheel_base, vex::distanceUnits distance_units, int default_speed);

    //General Drive Functions
    void left_spin(int speed, vex::breakType break_type);
    void right_spin(int speed, vex::breakType break_type);
    void drive_spin(int left_speed, int right_speed);
    void drive_stop(vex::breakType break_type);

    void move_for_degrees(float left_deg, float right_deg, int speed);

    //User Control Functions
    void user_control(int buffer_size = 20);

    //Autonomous Functions
    void turnPID(float maxLeftSpeed, float maxRightSpeed, float Angle); //NEWWWW
    void smartDrive(float maxSpeed, float Distance, bool complete);
    void smartTurn(float maxSpeed, float Angle, bool complete);
    void drivePID(float maxLeftSpeed, float maxRightSpeed, float Distance);
    void driveBackPID(float maxLeftSpeed, float maxRightSpeed, float Distance);
    void driveInches_MotorEnc(direction_t direction, float travelTargetIN, int speed);
    void turnDegrees_MotorEnc(turn_t direction, float travelTargetDEG, int speed);
    void driveDegrees_MotorEnc(float degrees, int speed);
    void driveInches_Enc(direction_t direction, float travelTargetIN, int speed);
    void turnDegrees_MotorEnc(float leftDegrees, float rightDegrees,int speed);

    void turnToPoint(float x, float y);
};

#endif
/*---BASE_H---*/