/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>

#include "v5.h"
#include "v5_vcs.h"

vex::brain       Brain;
// A global instance of vex::competition

// define your global instances of motors and other devices here
vex::motor LF = vex::motor( vex::PORT2 );
vex::motor LB = vex::motor( vex::PORT3 );
vex::motor RF = vex::motor( vex::PORT8, true );
vex::motor RB = vex::motor( vex::PORT9, true );

vex::motor leftIntake  = vex::motor( vex::PORT1, true );
vex::motor rightIntake = vex::motor( vex::PORT10 );

vex::motor tilt1  = vex::motor( vex::PORT7, true );
vex::motor tilt2  = vex::motor( vex::PORT4 );

vex::controller Controller1 = vex::controller();

vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.F);
vex::encoder leftEncoder  = vex::encoder(Brain.ThreeWirePort.C) ;
vex::encoder rightEncoder = vex::encoder(Brain.ThreeWirePort.G) ;
vex::bumper Bumper = vex::bumper(Brain.ThreeWirePort.B);

const double wheelDiameterIN  = 4; 
const double baseDiameterIN  = 16.5;

#define Y_leftJoy Controller1.Axis3.value()
#define Y_rightJoy Controller1.Axis2.value()

#define X_leftJoy Controller1.Axis4.value()
#define X_rightJoy Controller1.Axis1.value()

#define autoScoreBtn Controller1.ButtonA.pressing()
#define baseLockBtn Controller1.ButtonB.pressing()

#define tiltOutBtn Controller1.ButtonL1.pressing()
#define tiltInBtn  Controller1.ButtonL2.pressing()

#define intakeBtn Controller1.ButtonR1.pressing()
#define outtakeBtn Controller1.ButtonR2.pressing()

//Sensors:
#define baseGyro Gyro.value(vex::rotationUnits::deg)
#define leftBaseEnc leftEncoder.rotation(vex::rotationUnits::deg)
#define rightBaseEnc rightEncoder.rotation(vex::rotationUnits::deg)
#define tiltBumpBtn Bumper.pressing()