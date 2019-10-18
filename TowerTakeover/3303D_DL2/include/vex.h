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


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::controller Controller = vex::controller();

vex::motor LF  = vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,false);
vex::motor LB   = vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,false);
vex::motor RF = vex::motor(vex::PORT10,vex::gearSetting::ratio18_1,true);
vex::motor RB  = vex::motor(vex::PORT9,vex::gearSetting::ratio18_1,true);

vex::motor liftOne = vex::motor(vex::PORT6,vex::gearSetting::ratio18_1,true);
vex::motor liftTwo = vex::motor(vex::PORT7,vex::gearSetting::ratio18_1,true);

vex::motor rightIntake = vex::motor(vex::PORT5,vex::gearSetting::ratio18_1,false);
vex::motor leftIntake  = vex::motor(vex::PORT18,vex::gearSetting::ratio18_1,true);

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

#define liftUpBtn    Controller1.ButtonL1.pressing()
#define liftDownBtn  Controller1.ButtonL2.pressing()
#define angleUpBtn   Controller1.ButtonUp.pressing()
#define angleDownBtn Controller1.ButtonDown.pressing()
#define angleSlowBtn Controller1.ButtonRight.pressing()

#define intakeBtn Controller1.ButtonR1.pressing()
#define outtakeBtn Controller1.ButtonR2.pressing()

//Sensors:
//#define baseGyro Gyro.value(vex::rotationUnits::deg)OLD
#define baseGyro (-Gyro.value(vex::analogUnits::mV))
#define baseGyroReset Gyro.startCalibration(1000)
#define leftBaseEnc leftEncoder.rotation(vex::rotationUnits::deg)
#define rightBaseEnc rightEncoder.rotation(vex::rotationUnits::deg)
#define leftBaseEncReset leftEncoder.resetRotation()
#define rightBaseEncReset rightEncoder.resetRotation()
#define tiltBumpBtn Bumper.pressing()

//driveUserControl(Controller.Axis3.value(), Controller.Axis2.value());
//liftUserControl(100, Controller.ButtonL1.pressing(), Controller.ButtonL2.pressing(), Controller.ButtonUp.pressing(), Controller.ButtonDown.pressing(), Controller.ButtonRight.pressing());
//intakeUserControl(100, Controller.ButtonR1.pressing(), Controller.ButtonR2.pressing());
