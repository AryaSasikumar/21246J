#include "intake.h"

class AutonomusRoutines{
  private:
    bool testEnableTog = false;
  public:
    void currentTestAuton();
    void userControl();
    void turnTest();
    void skills();
    void ramBoi();
};


//--//--//----CURRENT TEST AUTON---//--//--//
void AutonomusRoutines::currentTestAuton(){
  
}
//--//--//----CURRENT TEST AUTON---//--//--//

void AutonomusRoutines::userControl(){
  if(enableAutonTestButton && autonTestButton){
    testEnableTog = !testEnableTog;
    wait(300, msec); 
  }
  if(testEnableTog){
    mainBaseLeftEncReset;
    mainBaseRightEncReset;
    baseHeadingReset;
    baseRotationReset;
    while(testEnableTog){
      currentTestAuton();
      wait(300, msec); 
      testEnableTog = false;
    }
  }
}

void AutonomusRoutines::turnTest(){
  myPID.pidTurnRightLoop(49);
}

void AutonomusRoutines::ramBoi(){
  rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//hood release
  leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  vex::task::sleep(300);
  rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm); //intake
  leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  myPID.pidDriveLoop(1390);
  vex::task::sleep(500);
  myPID.pidTurnLeftLoop(48);
  myPID.pidDriveLoop(990); //towards goal 
  //myBase.Spin(10,10);
  rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//shoot
  leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  vex::task::sleep(2500);
  myBase.Spin(0,0);
  rightIntake.stop();
  leftIntake.stop();
  myPID.pidDriveBackLoop(1540);
  myPID.pidTurnRightLoop(71);
  rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm); //filter
  leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  vex::task::sleep(1500);
  rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm); //intake
  leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  vex::task::sleep(500);
  myPID.pidDriveLoop(1000); //towards middle ball
  vex::task::sleep(100);
  myBase.moveFor(800, 800, 30);
  myPID.pidTurnLeftLoop(45);
  vex::task::sleep(100);
  myPID.pidDriveLoop(310); // towards goal 
  rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//shoot
  leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  vex::task::sleep(1300);
  myPID.pidDriveBackLoop(1350);
  rightIntake.stop();
  leftIntake.stop();
  myPID.pidTurnRightLoop(39);//39
  vex::task::sleep(100);
  rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm); //filter
  leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  vex::task::sleep(2000);
  rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm); //intake
  leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  vex::task::sleep(500);
  myPID.pidDriveLoop(1820); //towards middle ball
  vex::task::sleep(100);
  myBase.moveFor(800, 800, 30);
  myPID.pidTurnLeftLoop(28);
  myPID.pidDriveLoop(1000); //towards goal 
  myBase.Spin(10,10);
  rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//shoot
  leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);


  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(2700);
  // vex::task::sleep(500);
  // rightIntake.stop();
  // leftIntake.stop();  
  // myPID.pidTurnLeftLoop(25);
  // vex::task::sleep(100);
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//vision sensor
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(1200);
  //  vex::task::sleep(2500);
  // myPID.pidDriveBackLoop();
  // myPID.pidTurnRightLoop(int setpoint);
  // vex::task::sleep(100);
  // myPID.pidDriveLoop(int setpoint);
  // myPID.pidTurnLeftLoop(int setpoint);
  // vex::task::sleep(100);
  // myPID.pidDriveLoop(int setpoint);
  //  vex::task::sleep(2500);
  // myPID.pidDriveBackLoop(int setpoint);
  // myPID.pidTurnRightLoop(int setpoint);
  // vex::task::sleep(100);
  // myPID.pidDriveLoop(int setpoint);
  // myPID.pidTurnRightLoop();
  // vex::task::sleep(100);
  // myPID.pidDriveLoop(int setpoint);
  //  vex::task::sleep(2500);
  // myPID.pidDriveBackLoop(int setpoint);
  // myPID.pidTurnRightLoop(int setpoint);
  // vex::task::sleep(100);
  // myPID.pidDriveLoop(int setpoint);
  // myPID.pidTurnLeftLoop(int setpoint);
  // vex::task::sleep(100);
  // myPID.pidDriveLoop(int setpoint);
  //  vex::task::sleep(2500);
  // myPID.pidDriveBackLoop(int setpoint);
  // myPID.pidTurnRightLoop(int setpoint);
  // vex::task::sleep(100);
  // myPID.pidDriveLoop(int setpoint);
  // vex::task::sleep(2500);






}

void AutonomusRoutines::skills(){
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(1360);
  // vex::task::sleep(500);
  // myPID.pidTurnLeftLoop(49);
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveLoop(850);  
  // myBase.Spin(60,60);
  // vex::task::sleep(100);
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//vision sensor
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // vex::task::sleep(2420);
  // rightIntake.stop();
  // leftIntake.stop();
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//shoot out blue balls
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveBackLoop(1490);
  // vex::task::sleep(500);
  // rightIntake.stop();
  // leftIntake.stop();  

  // myPID.pidTurnRightLoop(83);
  // vex::task::sleep(500);

  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);//INTAKE BALL AGINST WALL
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(1600);
  // vex::task::sleep(500);
  // myPID.pidTurnLeftLoop(30);
  // rightIntake.stop();
  // leftIntake.stop();
  // myBase.Spin(60,60);
  // vex::task::sleep(500);
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//vision sensor
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // vex::task::sleep(2000);
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveBackLoop(1000);
  
  
  
  // myPID.pidTurnRightLoop(28);
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);//INTAKE BALL AGINST WALL
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // vex::task::sleep(1000);
  // myPID.pidDriveLoop(1100);
  // myBase.Spin(60, 60);
  // vex::task::sleep(700);
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveBackLoop(550);

  // myPID.pidTurnRightLoop(50);      
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(1350);  
  // myBase.lineStraighten();
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveLoop(100);
  // myPID.pidTurnLeftLoop(50);
  // vex::task::sleep(750);
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//shoot out blue balls
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myBase.Spin(50,50);
  // vex::task::sleep(2000);
  // leftIntake.stop();
  // myPID.pidDriveBackLoop(600);
  // rightIntake.stop();
  // myBase.Spin(0,0);
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // myPID.pidTurnRightLoop(84);
  // rightIntake.stop();
  // leftIntake.stop();
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(2500);  
}



AutonomusRoutines myAuton;

//myPID.pidTurnLoop(90);






  // while(rightLineTracker.reflectivity()<75 && leftLineTracker.reflectivity()<75){
  //   myBase.Spin(10,10);
  //   if(rightLineTracker.reflectivity()>75){
  //     rightFirst=true;
  //   }
  //   else if(leftLineTracker.reflectivity()>75){
  //     leftFirst=true;
  //   }
  // }
  // myBase.Brake();


  // vex::task::sleep(1000);
  // if(rightFirst){
  //   while(leftLineTracker.reflectivity()<92){
  //     myBase.Spin(10,0);
  //   }


    
  //   while(rightLineTracker.reflectivity()<92){
  //     myBase.Spin(0,-10);
  //   }
  //   while(leftLineTracker.reflectivity()<92){
  //     myBase.Spin(10,0);
  //   }
  //   myBase.Spin(10,0);
  //   vex::task::sleep(200);
  //   myBase.Brake();
  // }
  // else if(leftFirst){
  //   while(rightLineTracker.reflectivity()<92){
  //     myBase.Spin(0,10);
  //   }
  //   while(leftLineTracker.reflectivity()<92){
  //     myBase.Spin(-10,0);
  //   }
  //   while(rightLineTracker.reflectivity()<92){
  //     myBase.Spin(0,10);
  //   }
  //   myBase.Spin(0,10);
  //   vex::task::sleep(200);
  //   myBase.Brake();
  // }




  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(1360);
  // myPID.pidTurnLeftLoop(49);
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveLoop(850);  
  // myBase.Spin(60,60);
  // vex::task::sleep(100);
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//vision sensor
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // vex::task::sleep(2420);
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveBackLoop(1490);
  // myPID.pidTurnRightLoop(28);
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);//INTAKE BALL AGINST WALL
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // vex::task::sleep(1000);
  // myPID.pidDriveLoop(1100);
  // myBase.Spin(60, 60);
  // vex::task::sleep(700);
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveBackLoop(550);
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//shoot out blue balls
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // vex::task::sleep(1500);
  // rightIntake.stop();
  // leftIntake.stop();  
  // myPID.pidTurnRightLoop(50);      
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(1350);  
  // myBase.lineStraighten();
  // rightIntake.stop();
  // leftIntake.stop();
  // myPID.pidDriveLoop(100);
  // myPID.pidTurnLeftLoop(50);
  // vex::task::sleep(750);
  // rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);//shoot out blue balls
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myBase.Spin(50,50);
  // vex::task::sleep(2000);
  // leftIntake.stop();
  // myPID.pidDriveBackLoop(600);
  // rightIntake.stop();
  // myBase.Spin(0,0);
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // myPID.pidTurnRightLoop(84);
  // rightIntake.stop();
  // leftIntake.stop();
  // rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
  // leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  // myPID.pidDriveLoop(2500);  