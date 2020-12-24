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
const double FWD_KP = 0.05;
const double FWD_KI = 0.0011;
const double FWD_KD = 0.3;
const int FWD_DT = 15;

const double BWD_KP = FWD_KP;
const double BWD_KI = FWD_KI;
const double BWD_KD = FWD_KD;
const int BWD_DT = FWD_DT;

const double LEFT_KP = 0.7;
const double LEFT_KI = 0.0006;
const double LEFT_KD = 0.5;
const int LEFT_DT = 15;

const double RIGHT_KP = LEFT_KP;
const double RIGHT_KI = LEFT_KI;
const double RIGHT_KD = LEFT_KD;
const int RIGHT_DT = LEFT_DT;


//---Default-Units---//
#define DEFAULT_DIST_UNITS vex::distanceUnits::in
#define DEFAULT_ROT_UNITS vex::rotationUnits::deg
#define DEFAULT_VEL_UNITS vex::velocityUnits::pct

#define DEFAULT_TIME_UNITS vex::timeUnits::msec

#define DEFAULT_DRIVE_STOP_TYPE vex::brakeType::coast

#define DEFAULT_DIRECTION_TYPE vex::directionType::fwd

#define DEFAULT_SPEED 100.0
#endif
/*---ROBOT_DEFINITIONS_H---*/