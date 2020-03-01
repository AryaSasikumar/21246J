#include "lift.h"

class AutonomusRoutines{
  private:
    bool testEnableTog = false;
  public:
    void verticalStackFunction();
    void currentTestAuton();
    void userControl();
    void blueFront8CubePID();
    void redFront8CubePID();
    void SecureBlueFront7CubePID();
    void SecureRedFront7CubePID();
    void SecureBlueBack7CubePID();
    void SecureRedBack7CubePID();    
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
  SecureBlueFront7CubePID();
  //blueFront8CubePID();
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

void AutonomusRoutines::verticalStackFunction(){
  while (RangeFinderE.distance(inches) > 3) {
    myBase.Spin(15, 15);
    //Drivetrain.drive(forward);
    //Brain.Screen.print("%.2f", RangeFinderE.distance(inches));
    //wait(200, msec);
    //Brain.Screen.setCursor(1, 1);
    //Brain.Screen.clearScreen();
    //wait(5, msec);
  }
  myBase.Brake();
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
  task::sleep(500);
  myIntake.Spin(100);
  //first row
  myBase.drivePID(30, 30, 41);
  task::sleep(600);
  myBase.turnPID(-50, -50, -21); //right turn
  task::sleep(50);
  myBase.driveBackPID(-50, -50, -38); //increase speed to -90 once antitip deploys consistently 
  task::sleep(50); 
  myBase.turnPID(50, 50, -42);  //left turn
  task::sleep(50);
  //second row
  myBase.drivePID(35, 35, 17); //reduced from 36 to 17
  myIntake.Spin(30);
  task::sleep(500);   
  myBase.Spin(-50, -50);
  task::sleep(3000);
  myBase.Spin(0, 0);

  myBase.turnPID(-30, -30, -94);
  task::sleep(150);
  myIntake.Spin(100);
  myBase.drivePID(35, 35, 22);
  //task::sleep(250); 
  
  //myIntake.Spin(-5);
  rightIntake.startRotateFor(-240,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-240,rotationUnits::deg,30,velocityUnits::pct); 
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false); //INTEGRATIONNNNNNNNNNNNNN
  //myBase.smartDrive(30, 3, false);
  task::sleep(50);   
  myBase.driveBackPID(-30, -30, -13);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
  task::sleep(100);
  myBase.turnPID(30, 30, -101);
  task::sleep(50);
  myBase.Spin(-50, -50);
  myIntake.Spin(100);
  task::sleep(2000);
  myBase.Spin(0, 0);
  myBase.drivePID(45, 45, 51);  
  task::sleep(50);
  myBase.driveBackPID(-30, -30, -7);
  task::sleep(50);
  myLift.liftUp(145, 60, 50);
  myBase.drivePID(30, 30, 6);
  myIntake.Spin(-60);
  task::sleep(1000);
  myBase.driveBackPID(-30, -30, -25);  
  myLift.liftDown(84, 30, 50); 
  myIntake.Spin(100);
  myBase.Spin(-50, -50);
  task::sleep(3000);
  myBase.drivePID(45, 45, 18);  
  myBase.turnPID(40, 40, -83); //left turn
  myBase.drivePID(45, 45, 18);  
  task::sleep(50);
  myBase.driveBackPID(-30, -30, -5);
  task::sleep(50);
  myLift.liftUp(168, 60, 50);
  myBase.drivePID(30, 30, 14);  
  myIntake.Spin(-60);
  task::sleep(1000);
  mainBaseEncReset;
  myBase.driveBackPID(-30, -30, -10); 
  myLift.liftDown(84, 30, 50); 
  myIntake.Stop();
  myBase.turnPID(-40, -40, -114); //right turn
  myIntake.Spin(100);
  myBase.drivePID(45, 45, 42);  
  myBase.driveBackPID(-30, -30, -22);
  myBase.turnPID(-40, -40, -25); //right turn
  myLift.liftUp(145, 60, 50);
  task::sleep(50);
  myBase.drivePID(45, 45, 14);  
  myIntake.Spin(-60);
  task::sleep(1000);
  myBase.driveBackPID(-30, -30, -25);  
  myLift.liftDown(84, 30, 50); 

  // myBase.drivePID(45, 45, 26);  
  // task::sleep(50);
  // myBase.driveBackPID(-30, -30, -5);
  // task::sleep(50);
  // myLift.liftUp(168, 60, 50);
  // myBase.drivePID(30, 30, 9);  
  // myIntake.Spin(-60);
  // task::sleep(1000);
  // mainBaseEncReset;
  // myBase.driveBackPID(-30, -30, -7); 
  // myLift.liftDown(84, 30, 50); 
  // myIntake.Stop();
  // myBase.driveBackPID(-50, -50, -18);  
  // task::sleep(250);
  // myBase.turnPID(-40, -40, -73); //right turn
  // task::sleep(50);
  // myIntake.Spin(100);
  // myBase.drivePID(30, 30, 27);  
  // task::sleep(50);
  // myBase.driveBackPID(-30, -30, -7);
  // task::sleep(50);
  // myLift.liftUp(145, 60, 50);
  // myBase.drivePID(30, 30, 7);
  // myIntake.Spin(-60);
  // task::sleep(1000);
  // myBase.driveBackPID(-30, -30, -25);  
  // myLift.liftDown(84, 30, 50); 
  // myIntake.Spin(100);
  // myBase.turnPID(-50, -50, -20); //right turn
  // myBase.drivePID(30, 30, 37);  
  // task::sleep(150);
  // myBase.driveBackPID(-30, -30, -28);  
  // myBase.turnPID(-50, -50, -29); //right turn
  // myLift.liftUp(145, 60, 50);
  // myBase.drivePID(30, 30, 10); 
  // myIntake.Spin(-60);
  // task::sleep(1000);
  // myBase.driveBackPID(-30, -30, -14);  
  // myLift.liftDown(86, 30, 50); 

//Previous auton
/*
myIntake.Spin(-100);
  task::sleep(500);
  myIntake.Spin(100);
  //first row
  myBase.drivePID(30, 30, 41);
  task::sleep(600);
  myBase.turnPID(-50, -50, -21); //right turn
  task::sleep(50);
  myBase.driveBackPID(-50, -50, -38); //increase speed to -90 once antitip deploys consistently 
  task::sleep(50); 
  myBase.turnPID(50, 50, -42);  //left turn
  task::sleep(50);
  //second row
  myBase.drivePID(35, 35, 17); //reduced from 36 to 17
  myIntake.Spin(30);
  task::sleep(250);   
  myBase.turnPID(-30, -30, -105);
  task::sleep(150);
  myIntake.Spin(100);
  myBase.drivePID(50, 50, 36);
  //task::sleep(250); 
  
  //myIntake.Spin(-5);
  rightIntake.startRotateFor(-240,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-240,rotationUnits::deg,30,velocityUnits::pct); 
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false); //INTEGRATIONNNNNNNNNNNNNN
  //myBase.smartDrive(30, 3, false);
  task::sleep(5000);   
  myBase.driveBackPID(-30, -30, -16);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
  task::sleep(100);
  myBase.turnPID(-30, -30, -132);
  task::sleep(50);
  myIntake.Spin(100);
  myBase.drivePID(45, 45, 26);  
  task::sleep(50);
  myBase.driveBackPID(-30, -30, -5);
  task::sleep(50);
  myLift.liftUp(168, 60, 50);
  myBase.drivePID(30, 30, 9);  
  myIntake.Spin(-60);
  task::sleep(1000);
  mainBaseEncReset;
  myBase.driveBackPID(-30, -30, -7); 
  myLift.liftDown(84, 30, 50); 
  myIntake.Stop();
  myBase.driveBackPID(-50, -50, -18);  
  task::sleep(250);
  myBase.turnPID(-40, -40, -73); //right turn
  task::sleep(50);
  myIntake.Spin(100);
  myBase.drivePID(30, 30, 27);  
  task::sleep(50);
  myBase.driveBackPID(-30, -30, -7);
  task::sleep(50);
  myLift.liftUp(145, 60, 50);
  myBase.drivePID(30, 30, 7);
  myIntake.Spin(-60);
  task::sleep(1000);
  myBase.driveBackPID(-30, -30, -25);  
  myLift.liftDown(84, 30, 50); 
  myIntake.Spin(100);
  myBase.turnPID(-50, -50, -20); //right turn
  myBase.drivePID(30, 30, 37);  
  task::sleep(150);
  myBase.driveBackPID(-30, -30, -28);  
  myBase.turnPID(-50, -50, -29); //right turn
  myLift.liftUp(145, 60, 50);
  myBase.drivePID(30, 30, 10); 
  myIntake.Spin(-60);
  task::sleep(1000);
  myBase.driveBackPID(-30, -30, -14);  
  myLift.liftDown(86, 30, 50); 

*/


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

void AutonomusRoutines::SecureRedBack7CubePID(){ //change turn
  myIntake.Spin(-100);
  task::sleep(600);
  myIntake.Spin(100);
  myBase.drivePID(40, 40, 18);
  task::sleep(50);
  myLift.liftUp(157, 90, 50);
  task::sleep(20); 
  while(RangeFinderE.distance(inches) > 12) {
    myBase.Spin(40, 40);
    //task::sleep(20); 
    //wait(5, msec);
  }
  myBase.Spin(0,0);
  task::sleep(100); 
  myBase.Spin(-3, -3);
  myLift.liftDown(83, 30, 50); 
  myBase.Spin(0,0);
  myBase.drivePID(90, 90, 4);
  mainBaseEncReset;
  myBase.driveBackPID(-90, -90, -18);
  task::sleep(50);   
  myBase.turnPID(90, 90, -80);

  task::sleep(50);    
  myBase.drivePID(100, 100, 23); 

  task::sleep(100);    
  myIntake.Spin(-5);
  while(tiltSensor>=95){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-7);
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

void AutonomusRoutines::SecureBlueBack7CubePID(){ 
  myIntake.Spin(-100);
  task::sleep(500);
  myIntake.Spin(100);
  myBase.drivePID(40, 40, 18);
  task::sleep(50);
  myLift.liftUp(157, 90, 50);
  task::sleep(20); 
  while(RangeFinderE.distance(inches) > 12) {
    myBase.Spin(40, 40);
    //task::sleep(20); 
    //wait(5, msec);
  }
  myBase.Spin(0,0);
  task::sleep(100); 
  myBase.Spin(-3, -3);
  myLift.liftDown(83, 30, 50); 
  myBase.Spin(0,0);
  myBase.drivePID(90, 90, 4);
  mainBaseEncReset;
  myBase.driveBackPID(-90, -90, -18);
  task::sleep(50);   
  myBase.turnPID(-90, -90, -38);

  task::sleep(50);    
  myBase.drivePID(100, 100, 23); 

  task::sleep(100);    
  myIntake.Spin(-5);
  while(tiltSensor>=95){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-7);
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

void AutonomusRoutines::SecureBlueFront7CubePID(){ 
  myIntake.Spin(-100);
  task::sleep(500);
  myIntake.Spin(100);
  //first row
  myBase.drivePID(30, 30, 44);
  task::sleep(50);
  myBase.turnPID(75, 75, -23); //left turn
  task::sleep(50);
  myBase.driveBackPID(-80, -80, -35); //increase speed to -90 once antitip deploys consistently 
  task::sleep(50); 
  myBase.turnPID(-75, -75, -17);  //right turn
  task::sleep(50);
  //second row
  myBase.drivePID(35, 35, 16); //reduced from 36 to 17
  myIntake.Spin(30);
  task::sleep(250);   
  myBase.turnPID(44, 44, -88);
  task::sleep(150);
  myIntake.Spin(100);
  myBase.drivePID(95, 95, 32);
  //task::sleep(250); 
  
  //myIntake.Spin(-5);
  rightIntake.startRotateFor(-240,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-240,rotationUnits::deg,30,velocityUnits::pct); 
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false);
  //myBase.smartDrive(30, 3, false);
  myBase.driveBackPID(-30, -30, -12);
  while(tiltSensor<=180){
    myLift.Spin(-100, 100);
  }
}

void AutonomusRoutines::SecureRedFront7CubePID(){ //By Alex
  myIntake.Spin(-100);
  task::sleep(500);
  myIntake.Spin(100);
  //first row
  myBase.drivePID(30, 30, 44);
  task::sleep(50);
  myBase.turnPID(-75, -75, -7); //right turn
  task::sleep(50);
  myBase.driveBackPID(-80, -80, -39); //increase speed to -90 once antitip deploys consistently 
  task::sleep(50); 
  myBase.turnPID(75, 75, -24);  //left turn
  task::sleep(50);
  //second row
  myBase.drivePID(35, 35, 16); //reduced from 36 to 17
  myIntake.Spin(30);
  task::sleep(250);   
  myBase.turnPID(-44, -44, -59);
  task::sleep(150);
  myIntake.Spin(100);
  myBase.drivePID(95, 95, 36);
  //task::sleep(250); 
  
  //myIntake.Spin(-5);
  rightIntake.startRotateFor(-240,rotationUnits::deg,30,velocityUnits::pct);  
  leftIntake.rotateFor(-240,rotationUnits::deg,30,velocityUnits::pct); 
  while(tiltSensor>=90){
    myLift.Spin(100, -100);
  }
  myIntake.Spin(-5);
  while(tiltSensor>=44){
    myLift.Spin(20, -20);
  }
  myIntake.Stop();
  myLift.Stop(false);
  //myBase.smartDrive(30, 3, false);
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