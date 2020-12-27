/*---ROBOT_CONFIG_H---*/
#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H
/*----------------------------------------------------------------------------*/
/*    Module:       robot-config.h                                            */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

//---Core-Hardware---//
extern vex::brain Brain;
extern vex::controller Controller;
//---Drive-Motors---//
extern vex::motor LF_Drive;
extern vex::motor LB_Drive;
extern vex::motor RF_Drive;
extern vex::motor RB_Drive;
//---Drive-Motor-Groups---//
extern vex::motor_group LeftDrive;
extern vex::motor_group RightDrive;;
extern vex::drivetrain Drive;

//---Initialize code/tasks/devices. NOTE: Call at the start of int main.*/
extern void vexcodeInit(void);

#endif /*---ROBOT_CONFIG_H---*/