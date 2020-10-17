/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
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

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

motor LF = motor(PORT1, ratio6_1, true);
motor LT = motor(PORT2, ratio6_1, false);
motor LB = motor(PORT11, ratio6_1, true);

motor RF = motor(PORT10, ratio6_1, false);
motor RT = motor(PORT9, ratio6_1, true);
motor RB = motor(PORT20, ratio6_1, false);

inertial TurnGyroSmart = inertial(PORT13);

motor rightIntake = motor(PORT19, ratio18_1, false);
motor leftIntake = motor(PORT12, ratio18_1, false);


line colorChecker = line(Brain.ThreeWirePort.C);
line leftLineTracker = line(Brain.ThreeWirePort.B);
line rightLineTracker = line(Brain.ThreeWirePort.A);

// Vision SIG
signature Vision5__REDBOX = signature (1, 5845, 6791, 6318, -1041, -231, -636, 4.2, 0);
signature Vision5__BLUEBOX = signature (2, -3245, -2725, -2985, 7143, 7809, 7476, 7.9, 0);
vision Vision5 = vision (PORT8, 150, Vision5__REDBOX, Vision5__BLUEBOX);

//***---Controller1 Definitions---***//
 
//---Y Definitions---//
#define Y_leftJoy Controller1.Axis3.value()
#define Y_rightJoy Controller1.Axis2.value()
 
//---X Definitions---//
#define X_leftJoy Controller1.Axis4.value()
#define X_rightJoy Controller1.Axis1.value()
 
//---Button Definitions---//
#define macroDriveBtn Controller1.ButtonLeft.pressing()
#define driveToggleBtn Controller1.ButtonA.pressing()
#define slowDriveBackBtn Controller1.ButtonY.pressing()

#define autonTestButton Controller1.ButtonDown.pressing()
bool enableAutonTestButton = true;

#define shootBtn Controller1.ButtonR1.pressing() 
#define allUpBtn Controller1.ButtonR2.pressing()
#define filterUpBtn Controller1.ButtonL2.pressing()
#define filterOutBtn Controller1.ButtonUp.pressing()
#define autoSortBtn Controller1.ButtonL1.pressing()
#define intakeMacro Controller1.ButtonX.pressing()
#define angleSlowBtn Controller1.ButtonRight.pressing()
#define macroDriveBtn Controller1.ButtonLeft.pressing()
#define driveToggleBtn Controller1.ButtonA.pressing()
 
//---Sensor Definitions---//
#define baseInetrial (TurnGyroSmart.rotation(degrees))
#define baseHeadingReset TurnGyroSmart.resetHeading()
#define baseRotationReset TurnGyroSmart.resetRotation()
#define mainBaseEnc ((LF.rotation(rotationUnits::deg)+LF.rotation(rotationUnits::deg))/2)
#define mainBaseLeftEncReset LF.resetRotation()
#define mainBaseRightEncReset RF.resetRotation()

#define colorSensor colorChecker.reflectivity();

const double wheelDiameterIN  = 4;
const double baseDiameterIN  = 16.5;


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)