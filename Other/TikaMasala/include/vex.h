/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
// ---- START VEXCODE CONFIGURED DEVICES ----
// VEXcode device constructors
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "v5.h"
#include "v5_vcs.h"
#include "vex_global.h"

#include "robot-config.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

controller Controller1 = controller(primary);
motor LF = motor(PORT12, ratio18_1, false);
motor LB = motor(PORT2, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(LF, LB);

motor RF = motor(PORT21, ratio18_1, true);
motor RB= motor(PORT20, ratio18_1, true);
motor_group RightDriveSmart = motor_group(RF, RB);

inertial TurnGyroSmart = inertial(PORT12);
smartdrive DriveTrainSmart = smartdrive(LeftDriveSmart, RightDriveSmart, TurnGyroSmart, 319.19, 320, 165, mm, 1);

line LineSensorLeft = line(Brain.ThreeWirePort.A);
line LineSensorMiddle = line(Brain.ThreeWirePort.B);
line LineSensorRight = line(Brain.ThreeWirePort.C);

// ---- END VEXCODE CONFIGURED DEVICES ----
//---Y Definitions---//
#define Y_leftJoy Controller1.Axis3.value()
#define Y_rightJoy Controller1.Axis2.value()

//---X Definitions---//
#define X_leftJoy Controller1.Axis4.value()
#define X_rightJoy Controller1.Axis1.value()

//---Button Definitions---//
#define autoScoreBtn Controller1.ButtonA.pressing()
#define baseLockBtn Controller1.ButtonB.pressing()
#define tiltMacroBtn Controller1.ButtonX.pressing()

#define autonTestButton Controller1.ButtonY.pressing()
bool enableAutonTestButton = false;

#define liftUpBtn Controller1.ButtonL1.pressing()
#define liftDownBtn Controller1.ButtonL2.pressing()
#define angleUpBtn Controller1.ButtonUp.pressing()
#define angleDownBtn Controller1.ButtonDown.pressing()
#define angleSlowBtn Controller1.ButtonRight.pressing()
#define macroDriveBtn Controller1.ButtonLeft.pressing()

#define intakeBtn Controller1.ButtonR2.pressing()
#define outtakeBtn Controller1.ButtonR1.pressing()

//---Sensor Definitions---//
#define baseInetrial (TurnGyroSmart.rotation(degrees))
#define baseGyro (-Gyro.value(analogUnits::mV))
#define baseGyroReset Gyro.startCalibration(1000)
#define mainBaseEnc baseEncoder.rotation(rotationUnits::deg)
#define mainBaseEncReset baseEncoder.resetRotation()
#define tiltBumpBtn Bumper.pressing()
//#define liftSensor ((liftA.rotation(rotationUnits::deg) + liftB.rotation(rotationUnits::deg))/2)
#define liftSensor liftPot.value(rotationUnits::deg)
#define tiltSensor tiltPot.value(rotationUnits::deg)
#define leftLine LineSensorLeft.value(pct)
#define midLine LineSensorMiddle.value(pct)
#define rightLine LineSensorRight.value(pct)

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)