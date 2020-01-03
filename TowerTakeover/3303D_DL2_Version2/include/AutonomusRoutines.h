#include "lift.h"

// class AutonomusRoutines{
//   private:
    
//   public:
//     void blueFrontAuton();
//     void blueBackAuton();
//     void redFrontAuton();
//     void redBackAuton();
//     void simpleAuton();
//     void score();
// };

// void AutonomusRoutines::blueFrontAuton(){
//   myIntake.Spin(100);     //BLUEEEEEEEEE
//   vex::task::sleep(750);
//   myBase.drivePID(45, 45, 24.5);
//   vex::task::sleep(650); 
//   myBase.driveInches_Enc(backwards, -15, 80);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, 690);//left

//   myBase.drivePID(80, 80, 5);    
//   vex::task::sleep(150);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-195,vex::rotationUnits::deg,30,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-195,vex::rotationUnits::deg,30,vex::velocityUnits::pct); 
//   //vex::task::sleep(120);  
//   myLift.tiltForward(95, 60, 0);
//   myLift.tiltForward(49, 30, 0);
//   vex::task::sleep(500);  
//   myBase.driveInches_Enc(backwards, -10, 100);
// }
// void AutonomusRoutines::blueBackAuton(){
//   myIntake.Spin(100);         
//   vex::task::sleep(200);
//   myBase.drivePID(45, 45, 24.5);
  
//   //myBase.driveInches_Enc(backwards, -10, 95);
//   myBase.turnPID(-70,-70, 125);//left
//   myBase.driveBackPID(-100, -100, -20);
  
//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-70,-70, -105);//right
//   vex::task::sleep(100);  
//   myBase.drivePID(45, 45, 15);  

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, 667);//left
//   vex::task::sleep(100);
//   myBase.drivePID(85, 85, 24);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-140,vex::rotationUnits::deg,30,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-140,vex::rotationUnits::deg,30,vex::velocityUnits::pct); 
//   //vex::task::sleep(120);  
//   myLift.tiltForward(95, 75, 0);
//   myLift.tiltForward(49, 25, 0);
//   vex::task::sleep(100);  
//   myBase.driveInches_Enc(backwards, -10, 100);

//   /*myIntake.Stop();
//   rightIntake.startRotateFor(-140,vex::rotationUnits::deg,60,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-140,vex::rotationUnits::deg,60,vex::velocityUnits::pct); 
//   //vex::task::sleep(120);  
//   myLift.tiltForward(105, 65, 0);
//   myLift.tiltForward(54, 30, 0);
//   vex::task::sleep(500);  
//   myBase.driveInches_Enc(backwards, -10, 70);*/
// }
// void AutonomusRoutines::redFrontAuton(){
  
// }
// void AutonomusRoutines::redBackAuton(){
//   myIntake.Spin(100);         
//   vex::task::sleep(200);
//   myBase.drivePID(45, 45, 24.5);
  
//   //myBase.driveInches_Enc(backwards, -10, 95);
//   myBase.turnPID(-70,-70, -85);//right
//   myBase.driveBackPID(-70, -70, -21);
  
//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-70,-70, 145);//left
//   vex::task::sleep(200);  
//   myBase.drivePID(45, 45, 16);  

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, -613);//right
//   vex::task::sleep(300);
//   myBase.drivePID(100, 100, 23);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-140,vex::rotationUnits::deg,30,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-140,vex::rotationUnits::deg,30,vex::velocityUnits::pct); 
//   //vex::task::sleep(120);  
//   myLift.tiltForward(95, 75, 0);
//   myLift.tiltForward(49, 28, 0);
//   //vex::task::sleep(500);  
//   myBase.driveInches_Enc(backwards, -10, 100);
// }
// void AutonomusRoutines::simpleAuton(){
//   myIntake.Spin(100);     //BLUE
//   vex::task::sleep(250);
//   myBase.drivePID(45, 45, 24.5);
//   vex::task::sleep(200); 
//   myBase.driveInches_Enc(backwards, -12, 80);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, -355);//right

//   myBase.drivePID(80, 80, 12.5);    

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, -140);//right

//   myBase.drivePID(80, 80, 4);    
//   vex::task::sleep(50);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-195,vex::rotationUnits::deg,30,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-195,vex::rotationUnits::deg,30,vex::velocityUnits::pct); 
//   //vex::task::sleep(120);  
//   myLift.tiltForward(95, 60, 0);
//   myLift.tiltForward(49, 30, 0);
//   vex::task::sleep(200);  
//   myBase.driveInches_Enc(backwards, -10, 100);
  
  
  
//   /*myIntake.Spin(100);     //RED
//   vex::task::sleep(750);
//   myBase.drivePID(45, 45, 24.5);
//   vex::task::sleep(650); 
//   myBase.driveInches_Enc(backwards, -12, 80);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, 422);//left

//   myBase.drivePID(80, 80, 12.5);    
//   vex::task::sleep(150);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, 240);//left

//   myBase.drivePID(80, 80, 4);    
//   vex::task::sleep(150);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-195,vex::rotationUnits::deg,30,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-195,vex::rotationUnits::deg,30,vex::velocityUnits::pct); 
//   //vex::task::sleep(120);  
//   myLift.tiltForward(95, 60, 0);
//   myLift.tiltForward(49, 30, 0);
//   vex::task::sleep(500);  
//   myBase.driveInches_Enc(backwards, -10, 100);*/
// }

// AutonomusRoutines myAuton;

// /*

// //8 cube auton sharp turn

//   myIntake.Spin(100);         
//   vex::task::sleep(200);
//   myBase.drivePID(55, 55, 26);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.driveInches_Enc(backwards, -10, 95);
//   myBase.turnPID(-70,-70, -166);//right

//   myBase.driveInches_Enc(backwards, -16, 95);
  
//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, 270);//left

//   myBase.drivePID(50, 50, 26);  
//   vex::task::sleep(100);
//   myBase.driveInches_Enc(backwards, -10, 100);  
  
//   myBase.turnPID(-50,-50, 760);//left
//   myBase.drivePID(80, 80,11);    
//   vex::task::sleep(150);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-60,vex::rotationUnits::deg,60,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-60,vex::rotationUnits::deg,60,vex::velocityUnits::pct); 
//   vex::task::sleep(120);  
  
//   myLift.tiltForward(57, 40, 200);
//   vex::task::sleep(100);  
//   myBase.driveInches_Enc(backwards, -10, 100); */



//   /*myIntake.Spin(100);     //BLUEEEEEEEEE
//   vex::task::sleep(750);
//   myBase.drivePID(45, 45, 26.5);
//   vex::task::sleep(650); 
//   myBase.driveInches_Enc(backwards, -15, 80);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, 700);//left

//   myBase.drivePID(80, 80, 7.5);    
//   vex::task::sleep(150);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-260,vex::rotationUnits::deg,40,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-260,vex::rotationUnits::deg,40,vex::velocityUnits::pct); 
//   vex::task::sleep(120);  
  
//   myLift.tiltForward(60, 30, 200);
//   vex::task::sleep(500);  
//   myBase.driveInches_Enc(backwards, -10, 100);  */



  
  
  
// /*
//   myIntake.Spin(100);    // REDDDDDDDD
//   vex::task::sleep(700);
//   myBase.drivePID(45, 45, 25);
//   vex::task::sleep(650); 
//   myBase.driveInches_Enc(backwards, -14, 80);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, -700);//right

//   myBase.drivePID(80, 80, 7.5);    
//   vex::task::sleep(150);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-260,vex::rotationUnits::deg,40,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-260,vex::rotationUnits::deg,40,vex::velocityUnits::pct); 
//   vex::task::sleep(120);  
  
//   myLift.tiltForward(60, 30, 200);
//   vex::task::sleep(500);  
//   myBase.driveInches_Enc(backwards, -10, 100); */




//   /*baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(50,50, -459);  //450 Gyro units is about 90 degrees 

//   myLift.liftUp(900, 100, 100);
//   myLift.liftDown(500, 60, 100);*/

//   //myLift.tiltForward(50, 100, 200);

// /*
// //8 cube auton one turn

//   myIntake.Spin(100);         
//   vex::task::sleep(200);
//   myBase.drivePID(55, 55, 26);

//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, -76);//right

//   myBase.driveInches_Enc(backwards, -27, 96);
  
//   baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(-50,-50, 100);//left

//   myBase.drivePID(50, 50, 26);  
//   vex::task::sleep(100);
//   myBase.driveInches_Enc(backwards, -10, 100);  
  
//   myBase.turnPID(-50,-50, 760);//left
//   myBase.drivePID(80, 80, 9);    
//   vex::task::sleep(150);

//   myIntake.Stop();
//   rightIntake.startRotateFor(-60,vex::rotationUnits::deg,60,vex::velocityUnits::pct);  
//   leftIntake.rotateFor(-60,vex::rotationUnits::deg,60,vex::velocityUnits::pct); 
//   vex::task::sleep(120);  
  
//   myLift.tiltForward(57, 40, 200);
//   vex::task::sleep(100);  
//   myBase.driveInches_Enc(backwards, -10, 100);  

// */ 




//   /*baseGyroReset;
//   vex::task::sleep(500);
//   while(Gyro.isCalibrating()){vex::task::sleep(1);}
//   myBase.turnPID(50,50, -459);  //450 Gyro units is about 90 degrees 

//   myLift.liftUp(900, 100, 100);
//   myLift.liftDown(500, 60, 100);*/

//   //myLift.tiltForward(50, 100, 200);*/

//   /*void score(){             FIXXXXX FOR NEW BOT
//  tilt1.resetRotation() ;
//  tilt1.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
//  tilt2.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);   
 
//  while(tilt1.rotation(vex::rotationUnits::deg)<525 ){
//    if(tilt1.rotation(vex::rotationUnits::deg)>200){
//    tilt1.spin(vex::directionType::fwd,30,vex::velocityUnits::pct);
//    tilt2.spin(vex::directionType::fwd,30,vex::velocityUnits::pct); 
//    }
//    vex::task::sleep(1) ;
//  }
//  vex::task::sleep(1250) ;
//  autoScore();
//  vex::task::sleep(2000) ;
// }*/