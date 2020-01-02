/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>

#include "v5.h"
#include "v5_vcs.h"
#include "vex_global.h"

vex::brain       Brain;// A global instance of vex::brain used for printing to the V5 brain screen
vex::competition Competition; // A global instance of vex::competition
vex::controller  Controller = vex::controller(); // define your global instances of motors and other devices here

//***---Motor and Sensor Setup---***//

//---Base Motor Setup---//
vex::motor LF  = vex::motor(vex::PORT16,vex::gearSetting::ratio18_1,false);
vex::motor LB   = vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,false);
vex::motor RF = vex::motor(vex::PORT10,vex::gearSetting::ratio18_1,true);
vex::motor RB  = vex::motor(vex::PORT9,vex::gearSetting::ratio18_1,true);

//---Lift Motor Setup---//
vex::motor liftOne = vex::motor(vex::PORT6,vex::gearSetting::ratio18_1,true);
vex::motor liftTwo = vex::motor(vex::PORT7,vex::gearSetting::ratio18_1,true);

//---Intake Motor Setup---//
vex::motor rightIntake = vex::motor(vex::PORT3,vex::gearSetting::ratio18_1,false);
vex::motor leftIntake  = vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,true);

//---Sensor Setup---//
vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.C);
//vex::encoder leftEncoder  = vex::encoder(Brain.ThreeWirePort.C);
vex::encoder baseEncoder = vex::encoder(Brain.ThreeWirePort.G);
vex::bumper Bumper = vex::bumper(Brain.ThreeWirePort.B);
vex::pot liftPot = vex::pot(Brain.ThreeWirePort.A);

//***---Controller Definitions---***//

//---Y Definitions---//
#define Y_leftJoy      Controller.Axis3.value()
#define Y_rightJoy     Controller.Axis2.value()

//---X Definitions---//
#define X_leftJoy      Controller.Axis4.value()
#define X_rightJoy     Controller.Axis1.value()

//---Button Definitions---//
#define autoScoreBtn   Controller.ButtonA.pressing()
#define baseLockBtn    Controller.ButtonB.pressing()
#define tiltMacroBtn   Controller.ButtonX.pressing()
//#define buttonY Controller.ButtonY.pressing()

#define liftUpBtn      Controller.ButtonL1.pressing()
#define liftDownBtn    Controller.ButtonL2.pressing()
#define angleUpBtn     Controller.ButtonUp.pressing()
#define angleDownBtn   Controller.ButtonDown.pressing()
#define angleSlowBtn   Controller.ButtonRight.pressing()
#define macroDriveBtn  Controller.ButtonLeft.pressing()

#define intakeBtn      Controller.ButtonR1.pressing()
#define outtakeBtn     Controller.ButtonR2.pressing()

//---Sensor Definitions---//
#define baseGyro (-Gyro.value(vex::analogUnits::mV))
#define baseGyroReset Gyro.startCalibration(1000)
#define mainBaseEnc baseEncoder.rotation(vex::rotationUnits::deg)
#define mainBaseEncReset baseEncoder.resetRotation()
#define tiltBumpBtn Bumper.pressing()
#define liftSensor ((liftOne.rotation(vex::rotationUnits::deg)+liftTwo.rotation(vex::rotationUnits::deg))/2)
#define tiltSensor liftPot.value(vex::rotationUnits::deg)

//#define baseGyro Gyro.value(vex::rotationUnits::deg) //---OLD
//driveUserControl(Controller.Axis3.value(), Controller.Axis2.value());
//liftUserControl(100, Controller.ButtonL1.pressing(), Controller.ButtonL2.pressing(), Controller.ButtonUp.pressing(), Controller.ButtonDown.pressing(), Controller.ButtonRight.pressing());
//intakeUserControl(100, Controller.ButtonR1.pressing(), Controller.ButtonR2.pressing());

//---Constants---//
const double wheelDiameterIN  = 4; 
const double baseDiameterIN  = 16.5;