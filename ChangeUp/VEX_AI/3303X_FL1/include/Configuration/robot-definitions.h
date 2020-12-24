/*---ROBOT_DEFINITIONS_H---*/
#ifndef ROBOT_DEFINITIONS_H
#define ROBOT_DEFINITIONS_H
/*----------------------------------------------------------------------------*/
/*    Module:       robot-definitions.h                                       */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

//---Drive-Dimentions---//
#define WHEEL_DIAMETER 3.25
#define WHEEL_TRAVEL 10.21
#define TRACK_WIDTH 17.5
#define WHEEL_BASE 13.5

//---PID-Control---//
float FWD_KP = 0.05;
float FWD_KI = 0.0011;
float FWD_KD = 0.3;
int FWD_DT = 15;

float BWD_KP = FWD_KP;
float BWD_KI = FWD_KI;
float BWD_KD = FWD_KD;
int BWD_DT = FWD_DT;

float LEFT_KP = 0.7;
float LEFT_KI = 0.0006;
float LEFT_KD = 0.5;
int LEFT_DT = 15;

float RIGHT_KP = LEFT_KP;
float RIGHT_KI = LEFT_KI;
float RIGHT_KD = LEFT_KD;
int RIGHT_DT = LEFT_DT;


//---Default-Units---//
#define DEFAULT_DIST_UNITS vex::distanceUnits::in
#define DEFAULT_ANGL_UNITS vex::rotationUnits::deg
#define DEFAULT_VEL_UNITS vex::velocityUnits::pct

#define DEFAULT_TIME_UNITS vex::timeUnits::msec

#define DEFAULT_DRIVE_STOP_TYPE vex::brakeType::coast

#define DEFAULT_DIRECTION_TYPE vex::directionType::fwd

#define DEFAULT_SPEED 100
#endif
/*---ROBOT_DEFINITIONS_H---*/