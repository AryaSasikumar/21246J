/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       Dublin Robotics Club                                      */
/*    Created:      Tue Jul 30 2019                                           */
/*    Description:  V5 project                                                */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::controller Controller = vex::controller();

vex::motor leftFrontDrive  = vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,false);
vex::motor leftBackDrive   = vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,false);
vex::motor rightFrontDrive = vex::motor(vex::PORT10,vex::gearSetting::ratio18_1,true);
vex::motor rightBackDrive  = vex::motor(vex::PORT9,vex::gearSetting::ratio18_1,true);

vex::motor liftOne = vex::motor(vex::PORT6,vex::gearSetting::ratio18_1,true);
vex::motor liftTwo = vex::motor(vex::PORT7,vex::gearSetting::ratio18_1,true);

vex::motor rightIntake = vex::motor(vex::PORT8,vex::gearSetting::ratio18_1,false);
vex::motor leftIntake  = vex::motor(vex::PORT18,vex::gearSetting::ratio18_1,true);

//---GENERAL_MOTOR_CONTROL_FUNCTIONS---//
//Note: If changing motor names, edit motor control functions only
void leftBaseSpin(int speed){ //For turning on left side of base. NOTE: No sensors used, just on/off.
  if(speed!=0){
    leftFrontDrive.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
    leftBackDrive.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
  }else{
    leftFrontDrive.stop(vex::brakeType::coast);
    leftBackDrive.stop(vex::brakeType::coast);
  }
}
void rightBaseSpin(int speed){ //For turning on right side of base. NOTE: No sensors used, just on/off.
  if(speed!=0){
    rightFrontDrive.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
    rightBackDrive.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
  }else{
    rightFrontDrive.stop(vex::brakeType::coast);
    rightBackDrive.stop(vex::brakeType::coast);
  }
}
void liftSpin(int speedOne, int speedTwo){
  if(speedOne!=0 && speedTwo!=0){
    liftOne.spin(vex::directionType::fwd, speedOne, vex::velocityUnits::pct);
    liftTwo.spin(vex::directionType::fwd, speedTwo, vex::velocityUnits::pct);
  }else{
    liftOne.stop(vex::brakeType::hold);  
    liftTwo.stop(vex::brakeType::hold);    
  }
}
void intakeSpin(int speed){
  if(speed!=0){
    rightIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    leftIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    rightIntake.stop(vex::brakeType::hold);  
    leftIntake.stop(vex::brakeType::hold);      
  }
}



void driveUserControl(int leftSpeed, int rightSpeed){ //User control base, parameters are joysticks.
  leftBaseSpin(leftSpeed);
  rightBaseSpin(rightSpeed);
}
void liftUserControl(int speed, bool upBtn, bool downBtn, bool angleUpBtn, bool angleDownBtn){
  if(upBtn){
    liftSpin(speed, speed);
  }else if(downBtn){
    liftSpin(-speed, -speed);
  }else if(angleUpBtn){
    liftSpin(speed, -speed);
  }else if(angleDownBtn){
    liftSpin(-speed, speed);
  }else{
    liftSpin(0, 0);
  }
}
void intakeUserControl(int intakeSpeed, bool inBtn, bool outBtn){
  if(inBtn){
    intakeSpin(intakeSpeed);
  }else if(outBtn){
    intakeSpin(-intakeSpeed);
  }else{
    intakeSpin(0);    
  }
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/
void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
  // Insert autonomous user code here.
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/
void usercontrol(void){
  while (true){
    driveUserControl(Controller.Axis3.value(), Controller.Axis2.value());
    liftUserControl(100, Controller.ButtonL1.pressing(), Controller.ButtonL2.pressing(), Controller.ButtonUp.pressing(), Controller.ButtonDown.pressing());
    intakeUserControl(100, Controller.ButtonR1.pressing(), Controller.ButtonR2.pressing());
    vex::task::sleep(20);
  }
}

// Main will set up the competition functions and callbacks.
int main(){
  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  //Run the pre-autonomous function. 
  pre_auton();
      
  //Prevent main from exiting with an infinite loop.                        
  while(true){
    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }     
}