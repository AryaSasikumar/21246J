/*---ROBOT_CONFIG_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       robot-config.cpp                                          */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#import "vex.h"

//---Core-Hardware---//
vex::brain Brain;
vex::controller Controller = vex::controller(vex::primary);

//---Drive-Motors---//
vex::motor LF_Drive = vex::motor(vex::PORT11, vex::ratio18_1, false);
vex::motor LB_Drive = vex::motor(vex::PORT20, vex::ratio18_1, false);
vex::motor RF_Drive = vex::motor(vex::PORT1, vex::ratio18_1, true);
vex::motor RB_Drive = vex::motor(vex::PORT7, vex::ratio18_1, true);
//---Drive-Motor-Groups---//
vex::motor_group LeftDrive = vex::motor_group(LF_Drive, LB_Drive);
vex::motor_group RightDrive = vex::motor_group(RF_Drive, RB_Drive);
vex::drivetrain Drive = vex::drivetrain(LeftDrive, RightDrive, 10.21, 17.5, 14.5, vex::distanceUnits::in, 1);
//(leftDrive, rightDrive, wheel_travel, track_width, wheel_base, distanceUnits::in, external_gear_ratio);

//---Intake-Motors---//-----------TODO
//---Intake-Motor-Groups---//-----TODO
//vex::motor_group Intake = vex::motor_group(intake1, intake2); ???
//vex::motor_group Indexer = vex::motor_group(intake2, intake3); ???

//---Initialize code/tasks/devices. NOTE: Call at the start of int main.*/
void vexcodeInit(void){ 
  Brain.Screen.clearScreen(); 
  //Clear Gyro, Encoders
}

/*---ROBOT_CONFIG_CPP---*/