using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller;

extern motor_group LeftDrive;
extern motor_group RightDrive;
extern drivetrain Drive;



//***---Controller Definitions---***//
 
//---Y Definitions---//
#define Y_Left_Joy Controller.Axis3.value()
#define Y_Right_Joy Controller.Axis2.value()
 
//---X Definitions---//
#define X_Left_Joy Controller.Axis4.value()
#define X_Right_Joy Controller.Axis1.value()
 
//---Button Definitions---//
#define macroDriveBtn Controller.ButtonLeft.pressing()
#define driveToggleBtn Controller.ButtonA.pressing()
#define slowDriveBackBtn Controller.ButtonY.pressing()

#define autonTestButton Controller.ButtonDown.pressing()
//bool enableAutonTestButton = true;

#define shootBtn Controller.ButtonR1.pressing() 
#define allUpBtn Controller.ButtonR2.pressing()
#define filterUpBtn Controller.ButtonL2.pressing()
#define filterOutBtn Controller.ButtonUp.pressing()
#define autoSortBtn Controller.ButtonY.pressing()
#define intakeMacro Controller.ButtonX.pressing()
#define angleSlowBtn Controller.ButtonRight.pressing()
#define macroDriveBtn Controller.ButtonLeft.pressing()
#define driveToggleBtn Controller.ButtonA.pressing()
 
//---Sensor Definitions---//
//........



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );