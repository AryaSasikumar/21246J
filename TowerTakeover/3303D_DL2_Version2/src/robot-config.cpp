#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT16, ratio18_1, false);
motor leftMotorB = motor(PORT19, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

motor rightMotorA = motor(PORT9, ratio18_1, true);
motor rightMotorB = motor(PORT10, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

inertial TurnGyroSmart = inertial(PORT12);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart,
                                   TurnGyroSmart, 319.19, 320, 165, mm, 1);

motor liftA = motor(PORT6, ratio18_1, true);
motor liftB = motor(PORT7, ratio18_1, true);

motor rightIntake = motor(PORT3, ratio18_1, false);
motor leftIntake = motor(PORT15, ratio18_1, true);
motor_group IntakeSmart = motor_group(rightIntake, leftIntake);

encoder baseEncoder = encoder(Brain.ThreeWirePort.G);
gyro Gyro = gyro(Brain.ThreeWirePort.C);
bumper Bumper = bumper(Brain.ThreeWirePort.B);
pot liftPot = pot(Brain.ThreeWirePort.A);

//***---Controller1 Definitions---***//

//---Y Definitions---//
#define Y_leftJoy Controller1.Axis3.value()
#define Y_rightJoy Controller1.Axis2.value()

//---X Definitions---//
#define X_leftJoy Controller1.Axis4.value()
#define X_rightJoy Controller1.Axis1.value()

//---Button Definitions---//
#define autoScoreBtn Controller1.ButtonA.pressing()
#define baseLockBtn Controller1.ButtonB.pressing()
#define tiltMacroBtn Controller1.ButtonX.pressing()
//#define buttonY Controller.ButtonY.pressing()

#define liftUpBtn Controller1.ButtonL1.pressing()
#define liftDownBtn Controller1.ButtonL2.pressing()
#define angleUpBtn Controller1.ButtonUp.pressing()
#define angleDownBtn Controller1.ButtonDown.pressing()
#define angleSlowBtn Controller1.ButtonRight.pressing()
#define macroDriveBtn Controller1.ButtonLeft.pressing()

#define intakeBtn Controller1.ButtonR2.pressing()
#define outtakeBtn Controller1.ButtonR1.pressing()

//---Sensor Definitions---//
#define baseGyro (-Gyro.value(vex::analogUnits::mV))
#define baseGyroReset Gyro.startCalibration(1000)
#define mainBaseEnc baseEncoder.rotation(vex::rotationUnits::deg)
#define mainBaseEncReset baseEncoder.resetRotation()
#define tiltBumpBtn Bumper.pressing()
#define liftSensor                                                             \
  ((liftOne.rotation(vex::rotationUnits::deg) +                                \
    liftTwo.rotation(vex::rotationUnits::deg)) /                               \
   2)
#define tiltSensor liftPot.value(vex::rotationUnits::deg)

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool leftDriveStop = true;
bool rightDriveStop = true;
bool intakeStop = true;


void liftSpin(int speedOne, int speedTwo){
  if(speedOne!=0 && speedTwo!=0){
    liftA.spin(vex::directionType::fwd, speedOne, vex::velocityUnits::pct);
    liftB.spin(vex::directionType::fwd, speedTwo, vex::velocityUnits::pct);
  }else{
    liftA.stop(vex::brakeType::hold);  
    liftB.stop(vex::brakeType::hold);    
  }
}
void liftStop(bool type){
  if(type){
      liftA.stop(vex::brakeType::coast);  
      liftB.stop(vex::brakeType::coast);            
    }else{
      liftA.stop(vex::brakeType::hold);   
      liftB.stop(vex::brakeType::hold);             
    }  
}
int liftSpeed = 100;
int tiltSpeed = 100;
int slowSpeed = 30;
void liftUserControl(){
  if(liftUpBtn){
    liftSpin(90, liftSpeed);
  }else if(liftDownBtn){
    liftSpin(-liftSpeed, -liftSpeed);
  }else if(angleUpBtn){
    liftSpin(tiltSpeed, -tiltSpeed);
  }else if(angleDownBtn){
    liftSpin(-tiltSpeed, tiltSpeed);
  }else if(angleSlowBtn){
    liftSpin(slowSpeed, -slowSpeed);
  }else if(tiltMacroBtn){
    if(tiltSensor>=90){
      liftSpin(tiltSpeed, -tiltSpeed);
    }else if(tiltSensor>=41){
      liftSpin(slowSpeed, -slowSpeed);
    }
    else{
      liftSpin(10, -10);  
    }
  }else{
    liftSpin(0, 0);
  }
}

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  while (true) {
    if (RemoteControlCodeEnabled) {
      liftUserControl();
      if (Y_leftJoy < 5 && Y_leftJoy > -5) {
        if (leftDriveStop) {
          LeftDriveSmart.stop();
          leftDriveStop = false;
        }
      } else {
        leftDriveStop = true;
      }
      if (Y_rightJoy < 5 && Y_rightJoy > -5) {
        if (rightDriveStop) {
          RightDriveSmart.stop();
          rightDriveStop = false;
        }
      } else {
        rightDriveStop = true;
      }
      if (leftDriveStop) {
        LeftDriveSmart.setVelocity(Y_leftJoy, percent);
        LeftDriveSmart.spin(forward);
      }
      if (rightDriveStop) {
        RightDriveSmart.setVelocity(Y_rightJoy, percent);
        RightDriveSmart.spin(forward);
      }

      if (intakeBtn) {
        IntakeSmart.spin(forward, 100, percent);
      } else if (outtakeBtn) {
        IntakeSmart.spin(reverse, 100, percent);
      } else {
        IntakeSmart.stop(hold);
      }
    }
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}