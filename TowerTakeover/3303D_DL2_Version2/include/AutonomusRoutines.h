#include "lift.h"

class AutonomusRoutines{
  private:
    bool testEnableTog = false;
  public:
    void currentTestAuton();
    void userControl();
    void blueFront8CubePID();
    void redFront8CubePID();
    void blueBack7CubePID();
    void redBack7CubePID();
    void blueFrontAuton();
    void blueBackAuton();
    void redFrontAuton();
    void redBackAuton();
    void simpleAuton();
    void score();
    void skills();
};


//--//--//----CURRENT TEST AUTON---//--//--//
void AutonomusRoutines::currentTestAuton(){
  //redFront8CubePID();
  //skills();
  //blueBack7CubePID();
  blueFront8CubePID();
  // myIntake.Spin(-100);
  // task::sleep(400);
  // myIntake.Spin(100);
  // myBase.smartDrive(43, 44, true);
  // task::sleep(50);
  // myBase.smartTurn(100, -32, true);
  // task::sleep(50);
  // myBase.smartDrive(-90, -42, true);
  // task::sleep(100); 
  // myBase.smartTurn(90, 31, true);
  // task::sleep(50);
  // myBase.smartDrive(45, 36, true);
  // myIntake.Spin(30);
  // myBase.smartTurn(90, -136, true);
  // task::sleep(50);
  // myIntake.Spin(100);
  // myBase.smartDrive(95, 46, true);
  // task::sleep(250); 
  // myIntake.Spin(-5);
  // while(tiltSensor>=90){
  //   myLift.Spin(100, -100);
  // }
  // myIntake.Spin(-5);
  // while(tiltSensor>=44){
  //   myLift.Spin(20, -20);
  // }
  // myIntake.Stop();
  // myLift.Stop(false);
  // myBase.smartDrive(30, 3,false);
  // myBase.smartDrive(-30, -12, true);
  // while(tiltSensor<=180){
  //   myLift.Spin(-100, 100);
  // }
}
//--//--//----CURRENT TEST AUTON---//--//--//

void AutonomusRoutines::userControl(){
  if(enableAutonTestButton && autonTestButton){
    testEnableTog = !testEnableTog;
    wait(300, msec); 
  }
  if(testEnableTog){
    mainBaseEncReset;
    baseHeadingReset;
    baseRotationReset;
    while(testEnableTog){
      currentTestAuton();
      wait(300, msec); 
      testEnableTog = false;
    }
  }
}

void AutonomusRoutines::redBack7CubePID(){
  
  
  /*myIntake.Spin(-100);
  task::sleep(500);
  myIntake.Spin(100);
  myBase.drivePID(40, 40, 19);
  task::sleep(50);
  myLift.liftUp(157, 75, 0);
  task::sleep(20); 
  myBase.drivePID(35, 35, 13);
  task::sleep(50); 
  myBase.Spin(-2, -2);
  myLift.liftDown(83, 30, 50); 
  myBase.Spin(0,0);
  myBase.drivePID(70, 70, 4);
  mainBaseEncReset;
  myBase.driveBackPID(-90, -90, -24);
  task::sleep(100);   
  myBase.turnPID(90, 90, -62); 
  task::sleep(50);    
  myBase.drivePID(90, 90, 25); 
  //myBase.turnPID(90, 90, -25);   
  //myBase.drivePID(90, 90, 10.75); 
  task::sleep(100);    
  myIntake.Spin(-5);
  while(tiltSensor>=93){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=50){
    myLift.Spin(25, -25);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.driveBackPID(-100, -100, -50);
  //myBase.smartDrive(30, 3, false);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }*/
  
  myIntake.Spin(-100);
  task::sleep(500);
  myIntake.Spin(100);
  myBase.drivePID(40, 40, 19);
  task::sleep(50);
  myLift.liftUp(157, 70, 50);
  task::sleep(20); 
  myBase.drivePID(35, 35, 12.5);
  task::sleep(50); 
  myBase.Spin(-2, -2);
  myLift.liftDown(83, 30, 50); 
  myBase.Spin(0,0);
  myBase.drivePID(40, 40, 3);
  mainBaseEncReset;
  myBase.driveBackPID(-80, -80, -18.5);
  task::sleep(50);   
  myBase.turnPID(-90, -90, -39); 
  task::sleep(50);    
  myBase.drivePID(90, 90, 23); 
  //myBase.turnPID(90, 90, -25);   
  //myBase.drivePID(90, 90, 10.75); 
  task::sleep(100);    
  myIntake.Spin(-5);
  while(tiltSensor>=95){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=55){
    myLift.Spin(25, -25);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.driveBackPID(-100, -100, -50);
  //myBase.smartDrive(30, 3, false);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
}

void AutonomusRoutines::blueBack7CubePID(){
  myIntake.Spin(-100);
  task::sleep(500);
  myIntake.Spin(100);
  myBase.drivePID(40, 40, 19);
  task::sleep(50);
  myLift.liftUp(157, 70, 50);
  task::sleep(20); 
  myBase.drivePID(35, 35, 13.75);
  task::sleep(50); 
  myBase.Spin(-2, -2);
  myLift.liftDown(83, 30, 50); 
  myBase.Spin(0,0);
  myBase.drivePID(40, 40, 3);
  mainBaseEncReset;
  myBase.driveBackPID(-55, -55, -12);
  task::sleep(100); 
  //myBase.smartTurn(50, 90, true);
  
  myBase.turnPID(90, 90, 62); 
  task::sleep(50);    
  myBase.drivePID(90, 90, 24.5); 
  //myBase.turnPID(90, 90, -25);   
  //myBase.drivePID(90, 90, 10.75); 
  task::sleep(100);    
  myIntake.Spin(-5);
  while(tiltSensor>=95){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(25, -25);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.driveBackPID(-100, -100, -50);
  //myBase.smartDrive(30, 3, false);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
  

}

void AutonomusRoutines::skills(){
  myIntake.Spin(-100);
  task::sleep(400);
  myIntake.Spin(100);
  myBase.drivePID(45, 45, 44);
  task::sleep(50);
  myBase.turnPID(100, 100, -32);
  task::sleep(50);
  myBase.driveBackPID(-90, -90, -41);
  task::sleep(100); 
  myBase.turnPID(90, 90, 37.5);
  task::sleep(50);
  myBase.drivePID(45, 45, 36);
  myIntake.Spin(30);
  myBase.turnPID(90, 90, -133);
  task::sleep(50);
  myIntake.Spin(100);
  myBase.drivePID(95, 95, 46);
  task::sleep(250); 
  myIntake.Spin(-5);
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.smartDrive(30, 3, false);
  myBase.driveBackPID(-30, -30, -8.5);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
  task::sleep(100);
  myBase.turnPID(50, 50, -132);
  task::sleep(50);
  myIntake.Spin(100);
  myBase.drivePID(45, 45, 28);  
  task::sleep(50);
  myBase.driveBackPID(-30, -30, -5);
  task::sleep(50);
  myLift.liftUp(168, 60, 50);
  myBase.drivePID(30, 30, 16);  
  myIntake.Spin(-60);
  task::sleep(1000);
  myBase.driveBackPID(-30, -30, -10);  
  myLift.liftDown(83, -100, 50);
}

void AutonomusRoutines::redFront8CubePID(){ //By Jeffrey
  myIntake.Spin(-100);
  task::sleep(400);
  myIntake.Spin(100);
  myBase.drivePID(45, 45, 46);
  task::sleep(50);
  myBase.turnPID(100, 100, 32);
  task::sleep(50);
  myBase.driveBackPID(-90, -90, -42);
  task::sleep(100); 
  myBase.turnPID(90, 90, -35);
  task::sleep(50);
  myBase.drivePID(45, 45, 36);
  myIntake.Spin(30);
  myBase.turnPID(88, 88, 124);
  task::sleep(50);
  myIntake.Spin(100);
  myBase.drivePID(95, 95, 45);
  task::sleep(250); 
  myIntake.Spin(-5);
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.smartDrive(30, 3, false);
  myBase.driveBackPID(-30, -30, -12);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
}

void AutonomusRoutines::blueFront8CubePID(){ //By Jeffrey
  myIntake.Spin(-100);
  task::sleep(400);
  myIntake.Spin(100);
  myBase.drivePID(45, 45, 46);
  task::sleep(50);
  myBase.turnPID(100, 100, -32);
  task::sleep(50);
  myBase.driveBackPID(-90, -90, -42);
  task::sleep(100); 
  myBase.turnPID(90, 90, 31);
  task::sleep(50);
  myBase.drivePID(45, 45, 36);
  myIntake.Spin(30);
  myBase.turnPID(88, 88, -129);
  task::sleep(50);
  myIntake.Spin(100);
  myBase.drivePID(95, 95, 45);
  task::sleep(250); 
  myIntake.Spin(-5);
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.smartDrive(30, 3, false);
  myBase.driveBackPID(-30, -30, -12);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
}

void AutonomusRoutines::blueFrontAuton(){
  myIntake.Spin(100);     //BLUEEEEEEEEE
  task::sleep(750);
  myBase.drivePID(45, 45, 24.5);
  task::sleep(650); 
  myBase.driveInches_Enc(backwards, -15, 80);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, 690);//left

  myBase.drivePID(80, 80, 5);    
  task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-195,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-195,rotationUnits::deg,30,velocityUnits::pct); 
  //task::sleep(120);  
  myLift.tiltForward(95, 60, 0);
  myLift.tiltForward(49, 30, 0);
  task::sleep(500);  
  myBase.driveInches_Enc(backwards, -10, 100);
}
void AutonomusRoutines::blueBackAuton(){
  /*myIntake.Spin(100);         
  task::sleep(200);
  myBase.drivePID(45, 45, 24.5);
  
  //myBase.driveInches_Enc(backwards, -10, 95);
  myBase.turnPID(-70,-70, 125);//left
  myBase.driveBackPID(-100, -100, -20);
  
  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-70,-70, -105);//right
  task::sleep(100);  
  myBase.drivePID(45, 45, 15);  

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, 667);//left
  task::sleep(100);
  myBase.drivePID(85, 85, 24);

  myIntake.Stop();
  rightIntake.startRotateFor(-140,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-140,rotationUnits::deg,30,velocityUnits::pct); 
  //task::sleep(120);  
  myLift.tiltForward(95, 75, 0);
  myLift.tiltForward(49, 25, 0);
  task::sleep(100);  
  myBase.driveInches_Enc(backwards, -10, 100);*/

  myIntake.Spin(-100);
  task::sleep(600);
  myIntake.Spin(100);
  myBase.drivePID(35, 35, 40.5);
  task::sleep(250);
  myBase.driveBackPID(-60, -60, -22);
  task::sleep(100); 
  myBase.turnPID(90, 90, 128.5);
  task::sleep(50);
  myBase.drivePID(45, 45, 12);
  task::sleep(250); 
  myIntake.Spin(-5);
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false);
  myBase.smartDrive(30, 3, false);
  myBase.driveBackPID(-30, -30, -12);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }

  /*myIntake.Stop();
  rightIntake.startRotateFor(-140,rotationUnits::deg,60,velocityUnits::pct);  
  leftIntake.rotateFor(-140,rotationUnits::deg,60,velocityUnits::pct); 
  //task::sleep(120);  
  myLift.tiltForward(105, 65, 0);
  myLift.tiltForward(54, 30, 0);
  task::sleep(500);  
  myBase.driveInches_Enc(backwards, -10, 70);*/
}
void AutonomusRoutines::redFrontAuton(){
  
}
void AutonomusRoutines::redBackAuton(){
  myIntake.Spin(100);         
  task::sleep(200);
  myBase.drivePID(45, 45, 24.5);
  
  //myBase.driveInches_Enc(backwards, -10, 95);
  myBase.turnPID(-70,-70, -85);//right
  myBase.driveBackPID(-70, -70, -21);
  
  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-70,-70, 145);//left
  task::sleep(200);  
  myBase.drivePID(45, 45, 16);  

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, -613);//right
  task::sleep(300);
  myBase.drivePID(100, 100, 23);

  myIntake.Stop();
  rightIntake.startRotateFor(-140,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-140,rotationUnits::deg,30,velocityUnits::pct); 
  //task::sleep(120);  
  myLift.tiltForward(95, 75, 0);
  myLift.tiltForward(49, 28, 0);
  //task::sleep(500);  
  myBase.driveInches_Enc(backwards, -10, 100);
}
void AutonomusRoutines::simpleAuton(){
  myIntake.Spin(100);     //BLUE
  task::sleep(250);
  myBase.drivePID(45, 45, 24.5);
  task::sleep(200); 
  myBase.driveInches_Enc(backwards, -12, 80);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, -355);//right

  myBase.drivePID(80, 80, 12.5);    

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, -140);//right

  myBase.drivePID(80, 80, 4);    
  task::sleep(50);

  myIntake.Stop();
  rightIntake.startRotateFor(-195,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-195,rotationUnits::deg,30,velocityUnits::pct); 
  //task::sleep(120);  
  myLift.tiltForward(95, 60, 0);
  myLift.tiltForward(49, 30, 0);
  task::sleep(200);  
  myBase.driveInches_Enc(backwards, -10, 100);
  
  
  
  /*myIntake.Spin(100);     //RED
  task::sleep(750);
  myBase.drivePID(45, 45, 24.5);
  task::sleep(650); 
  myBase.driveInches_Enc(backwards, -12, 80);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, 422);//left

  myBase.drivePID(80, 80, 12.5);    
  task::sleep(150);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, 240);//left

  myBase.drivePID(80, 80, 4);    
  task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-195,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-195,rotationUnits::deg,30,velocityUnits::pct); 
  //task::sleep(120);  
  myLift.tiltForward(95, 60, 0);
  myLift.tiltForward(49, 30, 0);
  task::sleep(500);  
  myBase.driveInches_Enc(backwards, -10, 100);*/
}



/*

//8 cube auton sharp turn

  myIntake.Spin(100);         
  task::sleep(200);
  myBase.drivePID(55, 55, 26);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.driveInches_Enc(backwards, -10, 95);
  myBase.turnPID(-70,-70, -166);//right

  myBase.driveInches_Enc(backwards, -16, 95);
  
  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, 270);//left

  myBase.drivePID(50, 50, 26);  
  task::sleep(100);
  myBase.driveInches_Enc(backwards, -10, 100);  
  
  myBase.turnPID(-50,-50, 760);//left
  myBase.drivePID(80, 80,11);    
  task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-60,rotationUnits::deg,60,velocityUnits::pct);  
  leftIntake.rotateFor(-60,rotationUnits::deg,60,velocityUnits::pct); 
  task::sleep(120);  
  
  myLift.tiltForward(57, 40, 200);
  task::sleep(100);  
  myBase.driveInches_Enc(backwards, -10, 100); */



  /*myIntake.Spin(100);     //BLUEEEEEEEEE
  task::sleep(750);
  myBase.drivePID(45, 45, 26.5);
  task::sleep(650); 
  myBase.driveInches_Enc(backwards, -15, 80);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, 700);//left

  myBase.drivePID(80, 80, 7.5);    
  task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-260,rotationUnits::deg,40,velocityUnits::pct);  
  leftIntake.rotateFor(-260,rotationUnits::deg,40,velocityUnits::pct); 
  task::sleep(120);  
  
  myLift.tiltForward(60, 30, 200);
  task::sleep(500);  
  myBase.driveInches_Enc(backwards, -10, 100);  */



  
  
  
/*
  myIntake.Spin(100);    // REDDDDDDDD
  task::sleep(700);
  myBase.drivePID(45, 45, 25);
  task::sleep(650); 
  myBase.driveInches_Enc(backwards, -14, 80);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, -700);//right

  myBase.drivePID(80, 80, 7.5);    
  task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-260,rotationUnits::deg,40,velocityUnits::pct);  
  leftIntake.rotateFor(-260,rotationUnits::deg,40,velocityUnits::pct); 
  task::sleep(120);  
  
  myLift.tiltForward(60, 30, 200);
  task::sleep(500);  
  myBase.driveInches_Enc(backwards, -10, 100); */




  /*baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(50,50, -459);  //450 Gyro units is about 90 degrees 

  myLift.liftUp(900, 100, 100);
  myLift.liftDown(500, 60, 100);*/

  //myLift.tiltForward(50, 100, 200);

/*
//8 cube auton one turn

  myIntake.Spin(100);         
  task::sleep(200);
  myBase.drivePID(55, 55, 26);

  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, -76);//right

  myBase.driveInches_Enc(backwards, -27, 96);
  
  baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(-50,-50, 100);//left

  myBase.drivePID(50, 50, 26);  
  task::sleep(100);
  myBase.driveInches_Enc(backwards, -10, 100);  
  
  myBase.turnPID(-50,-50, 760);//left
  myBase.drivePID(80, 80, 9);    
  task::sleep(150);

  myIntake.Stop();
  rightIntake.startRotateFor(-60,rotationUnits::deg,60,velocityUnits::pct);  
  leftIntake.rotateFor(-60,rotationUnits::deg,60,velocityUnits::pct); 
  task::sleep(120);  
  
  myLift.tiltForward(57, 40, 200);
  task::sleep(100);  
  myBase.driveInches_Enc(backwards, -10, 100);  

*/ 




  /*baseGyroReset;
  task::sleep(500);
  while(Gyro.isCalibrating()){task::sleep(1);}
  myBase.turnPID(50,50, -459);  //450 Gyro units is about 90 degrees 

  myLift.liftUp(900, 100, 100);
  myLift.liftDown(500, 60, 100);*/

  //myLift.tiltForward(50, 100, 200);*/

  /*void score(){             FIXXXXX FOR NEW BOT
 tilt1.resetRotation() ;
 tilt1.spin(directionType::fwd,100,velocityUnits::pct);
 tilt2.spin(directionType::fwd,100,velocityUnits::pct);   
 
 while(tilt1.rotation(rotationUnits::deg)<525 ){
   if(tilt1.rotation(rotationUnits::deg)>200){
   tilt1.spin(directionType::fwd,30,velocityUnits::pct);
   tilt2.spin(directionType::fwd,30,velocityUnits::pct); 
   }
   task::sleep(1) ;
 }
 task::sleep(1250) ;
 autoScore();
 task::sleep(2000) ;
}*/







AutonomusRoutines myAuton;