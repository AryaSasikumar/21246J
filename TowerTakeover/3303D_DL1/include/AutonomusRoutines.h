#include "tilter.h"
/*
void blueAuton(){
  //first part is to calibrate gyro for turning
  Gyro.startCalibration();
  while(Gyro.isCalibrating())
        vex::task::sleep(1); 
    
    //after calibration turn slide on.
  deployslide(90,430) ;
  //after the slide deploys reverse back into the wall to align cubes.and drive train.
  
  
  //turn on the intake motors to prepare scoring cubes
  leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  drivefwd_nopid(85,1520) ;//first paremeter is speed next parameter is distance.
  vex::task::sleep(1000) ; 
  //made to get the green cube to the right of things.
  reversedrive(100,400) ;
  turn_(8.5,false,80) ; //this will turn robot toe right using the gyro sensor.
  vex::task::sleep(100) ;
  drivefwd_nopid(120,420) ;
  vex::task::sleep(300) ;
  
  //turn intake motors to hold.
  //reversed
  
  //drive(180,670) ; //reverse back to the goal
  turn_(165,true,50) ;
  
  vex::task::sleep(50) ; //sleep system after turn for better accuracy
  drivefwd_nopid(160,370) ; //driveto the goal
  outake(300); ///get the last cube to the bottom to score all the cubes.
  score() ;//use the score function when cubes are ready to be delivered.
}

void redAuton(){
  //first part is to calibrate gyro for turning
  Gyro.startCalibration();
  while(Gyro.isCalibrating())
        vex::task::sleep(1); 
    
    //after calibration turn slide on.
  deployslide(90,430) ;
  //after the slide deploys reverse back into the wall to align cubes.and drive train.
  turn_(0.5,true,5) ;
  
  //turn on the intake motors to prepare scoring cubes
  leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  drivefwd_nopid(85,1520) ;
  vex::task::sleep(1000) ; 
  //made to get the green cube to the right of things.
  reversedrive(100,400) ;
  turn_(9,true,80) ; //this will turn robot toe right using the gyro sensor.
  vex::task::sleep(100) ;
  drivefwd_nopid(120,350) ;
  vex::task::sleep(300) ;
  
  //turn intake motors to hold.
  reversedrive(180,650) ; //reverse back to the goal
  turn_(164.5,false,50) ;
  
  vex::task::sleep(50) ; //sleep system after turn for better accuracy
  drivefwd_nopid(160,385) ; //driveto the goal
  outake(300); ///get the last cube to the bottom to score all the cubes.
  score() ;//use the score function when cubes are ready to be delivered.
}
*/