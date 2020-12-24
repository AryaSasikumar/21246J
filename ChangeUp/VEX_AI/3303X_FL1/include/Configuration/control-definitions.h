/*---CONTROL_DEFINITIONS_H---*/
#ifndef CONTROL_DEFINITIONS_H
#define CONTROL_DEFINITIONS_H
/*----------------------------------------------------------------------------*/
/*    Module:       control-definitions.h                                     */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

/*              V5 CONTROLLER LAYOUT              */
/*                                                */
/*        //----------------------------\\        */
/*      //  ------               ------   \\      */
/*     //   | L2 |               | R2 |    \\     */
/*    ||    ------               ------     ||    */
/*    ||    | L1 |               | R1 |     ||    */
/*    ||------------------------------------||    */
/*    ||  Axis 3                    Axis 2  ||    */
/*    ||  /--↑--\                  /--↑--\  ||    */
/*    || |←     →|Axis 4    Axis 1|←     →| ||    */
/*    ||  \--↓--/                  \--↓--/  ||    */
/*    ||       |↑|                |X|       ||    */
/*    ||    |←|   |→|          |Y|   |A|    ||    */
/*    ||       |↓|                |B|       ||    */
/*     \\           //---------\\           //    */
/*      \\         //           \\         //     */
/*        \\_____//               \\_____//       */
/*                                                */
/*              V5 CONTROLLER LAYOUT              */

//---Joystick-Buffer-Definitions---//
#define X_LEFT_JOY_BUFFER 20
#define Y_LEFT_JOY_BUFFER 20
#define X_RIGHT_JOY_BUFFER X_LEFT_JOY_BUFFER
#define Y_RIGHT_JOY_BUFFER Y_LEFT_JOY_BUFFER

//---Left-Joystick-Definitions---//
#define X_LEFT_JOY Controller.Axis4.position()           /*  Axis4  */
#define Y_LEFT_JOY Controller.Axis3.position()           /*  Axis3  */
//---Right-Joystick-Definitions---//
#define X_RIGHT_JOY Controller.Axis1.position()          /*  Axis1  */
#define Y_RIGHT_JOY Controller.Axis2.position()          /*  Axis2  */

//---Button-Definitions---//
//#define NOT_ASSIGNED Controller.ButtonL1.pressing()    /*  L1  */
#define filterUpBtn Controller.ButtonL2.pressing()       /*  L2  */

#define shootBtn Controller.ButtonR1.pressing()          /*  R1  */
#define allUpBtn Controller.ButtonR2.pressing()          /*  R2  */

#define filterOutBtn Controller.ButtonUp.pressing()      /*  ↑  */
#define autonTestButton Controller.ButtonDown.pressing() /*  ↓  */
#define macroDriveBtn Controller.ButtonLeft.pressing()   /*  ←  */
#define angleSlowBtn Controller.ButtonRight.pressing()   /*  →  */

#define intakeMacro Controller.ButtonX.pressing()        /*  X  */
//#define NOT_ASSIGNED Controller.ButtonB.pressing()     /*  B  */
#define slowDriveBackBtn Controller.ButtonY.pressing()   /*  Y  */
#define driveToggleBtn Controller.ButtonA.pressing()     /*  A  */

//---Sensor Definitions---//
#define DriveEncoderRotation ((LeftDrive.rotation(DEFAULT_ANGL_UNITS)+RightDrive.rotation(DEFAULT_ANGL_UNITS))/2)
#define ResetDriveEncoders \
  LeftDrive.resetRotation(); \
  RightDrive.resetRotation()

#endif
/*---CONTROL_DEFINITIONS_H---*/