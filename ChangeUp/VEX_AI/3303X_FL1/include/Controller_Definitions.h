//***---Controller Definitions---***//
 
//---Y Definitions---//
#define Y_leftJoy Controller.Axis3.value()
#define Y_rightJoy Controller.Axis2.value()
 
//---X Definitions---//
#define X_leftJoy Controller.Axis4.value()
#define X_rightJoy Controller.Axis1.value()
 
//---Button Definitions---//
#define macroDriveBtn Controller.ButtonLeft.pressing()
#define driveToggleBtn Controller.ButtonA.pressing()
#define slowDriveBackBtn Controller.ButtonY.pressing()

#define autonTestButton Controller.ButtonDown.pressing()
bool enableAutonTestButton = true;

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
#define mainBaseEnc ((LeftDrive.rotation(rotationUnits::deg)+RightDrive.rotation(rotationUnits::deg))/2)
#define mainBaseLeftEncReset LeftDrive.resetRotation()
#define mainBaseRightEncReset RightDrive.resetRotation()

#define colorSensor colorChecker.reflectivity();

const double wheelDiameterIN  = 4;
const double BaseDiameterIN  = 16.5;