/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       aryasasikumar      yuh                                    */
/*    Created:      Mon Jul 22 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "tilter.h"


using namespace vex;


// A global instance of vex::brain used for printing to the V5 brain screen

// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  baseGyroReset;
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autoScore(){
  myBase.Spin(-30, -30);
  myTilter.Spin(-60);
  myIntake.Spin(-50);
}

void score(){
  tilt1.resetRotation() ;
  tilt1.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
  tilt2.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);    

  while(tilt1.rotation(vex::rotationUnits::deg)<525 ){
    if(tilt1.rotation(vex::rotationUnits::deg)>200){
    tilt1.spin(vex::directionType::fwd,30,vex::velocityUnits::pct);
    tilt2.spin(vex::directionType::fwd,30,vex::velocityUnits::pct);  
    }
    vex::task::sleep(1) ;
  }
  vex::task::sleep(2000) ;
  autoScore();
  vex::task::sleep(2000) ;
}

void blueAuton(){
//Intake and drive forward 4 cubes
  myTilter.robotDeploy();
  vex::task::sleep(100);  
  myBase.Spin(-100, -100);
  myIntake.Spin(80);
  vex::task::sleep(300); 
  myBase.Spin(0, 0);
  //myBase.driveInches_Enc(forwards, 50, 45);
  myBase.drivePID(44, 44, 51);//55
  vex::task::sleep(100);
  //myBase.drivePID(-45, -45, -10);
  myBase.driveInches_Enc(backwards, -29.5, 45);
  //myBase.drivePID(-40, -40, -20);

  //Turn towards right stack
  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(40,40, -850);  //450 Gyro units is about 90 degrees 

  //myBase.turnPID(50,50, 450);  //450 Gyro units is about 90 degrees
    
  //Drive into stack to intake first cube
  myBase.drivePID(60, 60, 13);
  vex::task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct);  
  leftIntake.rotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct); 
  vex::task::sleep(120);  
  score();  
}

void redAuton(){
  //Intake and drive forward 4 cubes
  myTilter.robotDeploy();
  vex::task::sleep(100);  
  myBase.Spin(-100, -100);
  myIntake.Spin(80);
  vex::task::sleep(200); 
  myBase.Spin(0, 0);
  //myBase.driveInches_Enc(forwards, 50, 45);
  myBase.drivePID(45, 45, 50);//55
  vex::task::sleep(100);
  //myBase.drivePID(-45, -45, -10);
  myBase.driveInches_Enc(backwards, -29, 45);
  //myBase.drivePID(-40, -40, -20);

  //Turn towards right stack
  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(40,40, 890);  //450 Gyro units is about 90 degrees 

  //myBase.turnPID(50,50, 450);  //450 Gyro units is about 90 degrees
    
  //Drive into stack to intake first cube
  myBase.drivePID(50, 50, 13.5);
  vex::task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct);  
  leftIntake.rotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct); 
  vex::task::sleep(120);  
  score();  
}

void supportBasicAuton(){
  //Intake and drive forward 4 cubes
  myTilter.robotDeploy();
  myIntake.Spin(-100);  
  myBase.drivePID(70, 70, 20);//55
  myIntake.Stop();
  myBase.driveInches_Enc(backwards, -10, 80);

  /*vex::task::sleep(100);  
  myBase.Spin(-100, -100);
  myIntake.Spin(100);
  vex::task::sleep(250); 
  myBase.Spin(0, 0);
  //myBase.driveInches_Enc(forwards, 50, 45);
  myBase.drivePID(50, 50, 47);//55
  vex::task::sleep(100);
  //myBase.drivePID(-45, -45, -10);
  myBase.driveInches_Enc(backwards, -7, 80);
  //myBase.drivePID(-40, -40, -20);

  //Turn towards right stack
  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(50,50, -62);  //450 Gyro units is about 90 degrees 

  //myBase.turnPID(50,50, 450);  //450 Gyro units is about 90 degrees
    
  //Drive into stack to intake first cube
  myBase.drivePID(60, 60, 12);
  vex::task::sleep(250);
  myBase.driveInches_Enc(backwards, -30, 80);      

  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(50,50, 1030);  //450 Gyro units is about 90 degrees
  myBase.drivePID(70, 70, 15);
  myIntake.Stop();
  rightIntake.startRotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct);  
  leftIntake.rotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct); 
  vex::task::sleep(250);  
  score();  */
}

void basicBlueAuton(){
//Intake and drive forward 4 cubes
  myTilter.robotDeploy();
  vex::task::sleep(100);  
  myBase.Spin(-100, -100);
  myIntake.Spin(100);
  vex::task::sleep(250); 
  myBase.Spin(0, 0);
  //myBase.driveInches_Enc(forwards, 50, 45);
  myBase.drivePID(45, 45, 50);//55
  vex::task::sleep(400);
  //myBase.drivePID(-45, -45, -10);
  myBase.driveInches_Enc(backwards, -25, 80);
  //myBase.drivePID(-40, -40, -20);

  //Turn towards right stack
  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(50,50, 485);  //450 Gyro units is about 90 degrees 

  //myBase.turnPID(50,50, 450);  //450 Gyro units is about 90 degrees
    
  //Drive into stack to intake first cube
  myBase.drivePID(60, 60, 22);
  //vex::task::sleep(400);
  //myBase.driveInches_Enc(backwards, -30, 80);      

  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(50,50, 195);  //450 Gyro units is about 90 degrees
  myBase.drivePID(70, 70, 7.5);
  myIntake.Stop();
  rightIntake.startRotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct);  
  leftIntake.rotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct); 
  vex::task::sleep(250);  
  score();  
}

void basicRedAuton(){
//Intake and drive forward 4 cubes
  myTilter.robotDeploy();
  vex::task::sleep(100);  
  myBase.Spin(-100, -100);
  myIntake.Spin(100);
  vex::task::sleep(250); 
  myBase.Spin(0, 0);
  //myBase.driveInches_Enc(forwards, 50, 45);
  myBase.drivePID(45, 45, 50);//55
  vex::task::sleep(400);
  //myBase.drivePID(-45, -45, -10);
  myBase.driveInches_Enc(backwards, -25, 80);
  //myBase.drivePID(-40, -40, -20);

  //Turn towards right stack
  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(50,50, -459);  //450 Gyro units is about 90 degrees 

  //myBase.turnPID(50,50, 450);  //450 Gyro units is about 90 degrees
    
  //Drive into stack to intake first cube
  myBase.drivePID(60, 60, 22);
  //vex::task::sleep(400);
  //myBase.driveInches_Enc(backwards, -30, 80);      

  baseGyroReset;
  vex::task::sleep(500);
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  myBase.turnPID(50,50, -103);  //450 Gyro units is about 90 degrees
  myBase.drivePID(80, 80, 7.3);
  myIntake.Stop();
  rightIntake.startRotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct);  
  leftIntake.rotateFor(-380,vex::rotationUnits::deg,80,vex::velocityUnits::pct); 
  vex::task::sleep(250);  
  score();  
}

void autonomous( void ) {
  //myBase.turnDegrees_Gyro(600,100);
  //myBase.turnPID(658.0);
  //myBase.turnPID(180.0);
  //myTilter.robotDeploy();
  //myIntake.Spin(100);
  //myBase.drivePID(48);
  //vex::task::sleep(1000);
  //myIntake.Spin(0);
  //myBase.drivePID(-46);
  tilt1.resetRotation();
  baseGyroReset;
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  //supportBasicAuton();
  //blueAuton();
  //redAuton();
  basicBlueAuton();
  //basicRedAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  tilt1.resetRotation();
  baseGyroReset;
  while(Gyro.isCalibrating()){vex::task::sleep(1);}
  while(true){
    myBase.userControl();
    myTilter.userControl();
    myIntake.userControl();
    if(btnX){
      vex::task::sleep(250);
      myBase.useTrueSpeed = !myBase.useTrueSpeed;
    }
    while(btnY){
      
      while(btnY){
        vex::task::sleep(1000);
      }
      //myBase.turnDegrees_Gyro(300,50);
      //myBase.turnPID(700);
    }
    vex::task::sleep(5); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(true) {
      if(Brain.Battery.capacity(percentUnits::pct) <= 50){
        Controller1.rumble("-.-.-.-");
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.print("BATTERY LOW!");
        vex::task::sleep(1000);
      }
      //printf("gyroVal: %ld\n",baseGyro);
      vex::task::sleep(5);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}