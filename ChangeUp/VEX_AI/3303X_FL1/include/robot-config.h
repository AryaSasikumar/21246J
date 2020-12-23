#include "Controller_Definitions.h"

using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor LF;
extern motor LB;
extern motor_group LeftDrive;

extern motor RF;
extern motor RB;
extern motor_group RightDrive;

extern drivetrain Drive;

extern motor rightIntake;
extern motor leftIntake;
extern motor indexer;
extern motor shooter;
extern controller Controller;

extern line colorChecker;
extern signature Vision5__REDBOX;
extern signature Vision5__BLUEBOX;
extern signature Vision5__SIG_3;
extern signature Vision5__SIG_4;
extern signature Vision5__SIG_5;
extern signature Vision5__SIG_6;
extern signature Vision5__SIG_7;
extern vision Vision5;
extern line leftLineTracker;
extern line rightLineTracker;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );