/*---BASE_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       Base.cpp                                                  */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Subsystems/Base.h"

#include "vex.h"

#include "Configuration/robot-config.h" 

Base::Base(){
  printf("Base created");
}

void Base::Spin(int leftSpeed, int rightSpeed){
  leftSpin(leftSpeed);
  rightSpin(rightSpeed);
}

void Base::rightSpin(int speed = 0){
  if(speed != 0){
    RightDrive.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    RightDrive.stop(vex::brakeType::coast); 
  }
}

void Base::leftSpin(int speed = 0){
  if(speed != 0){
    LeftDrive.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    LeftDrive.stop(vex::brakeType::coast);  
  }
}

void Base::Hold(){
  LeftDrive.stop(vex::brakeType::hold);
  RightDrive.stop(vex::brakeType::hold);
}

void Base::Brake() {
  LeftDrive.stop(vex::brakeType::brake);
  RightDrive.stop(vex::brakeType::brake);
}

void Base::moveFor(double degToRotate_Left, double degToRotate_Right, int speed){
  LF.startRotateFor(degToRotate_Left,degrees,speed,velocityUnits::pct);
  LB.startRotateFor(degToRotate_Left,degrees,speed,velocityUnits::pct);  
  RF.startRotateFor(degToRotate_Right,degrees,speed,velocityUnits::pct);  
  RB.rotateFor(degToRotate_Right,degrees,speed,velocityUnits::pct); 
}

void Base::userControl(int bufferSize, bool Stop){//driveToggleBtn
   if(toggle==true){
     if(abs(Y_rightJoy)>bufferSize){
       if(Y_rightJoy>0){
         rightSpin(halfSpeed[abs(Y_rightJoy)]);
       }else{
         rightSpin(-halfSpeed[abs(Y_rightJoy)]);
       }
     }else{
        rightSpin(0);
     } 
     if(abs(Y_leftJoy)>bufferSize){
       if(Y_leftJoy>0){
         leftSpin(halfSpeed[abs(Y_leftJoy)]);
       }else{
         leftSpin(-halfSpeed[abs(Y_leftJoy)]);
       }
     }else{
       leftSpin(0);
     } 
   } 
   else {
      if(abs(Y_rightJoy)>bufferSize){
       if(Y_rightJoy>0){
         rightSpin(trueSpeed[abs(Y_rightJoy)]);
       }else{
         rightSpin(-trueSpeed[abs(Y_rightJoy)]);
       }
     }else{
        rightSpin(0);
     } 
     if(abs(Y_leftJoy)>bufferSize){
       if(Y_leftJoy>0){
         leftSpin(trueSpeed[abs(Y_leftJoy)]);
       }else{
         leftSpin(-trueSpeed[abs(Y_leftJoy)]);
       }
     }else{
       leftSpin(0);
     } 
   }
}

double Base::distanceToTravel(double inchesGiven){
  int wheelRadIN = 2;
  float floatDiv = (float)95.0/36.0;
  double Distance = ((inchesGiven/(M_PI*wheelRadIN))*(360*floatDiv))/4;
  return Distance; //Distance in ticks    
}

void Base::driveInches_Enc(direction_t mydirection, double travelTargetIN, int speed){
 double lSpeed = speed;
 double rSpeed = speed;
 double circumference = wheelDiameterIN * M_PI;
 double degreesToRotate = ((360.0 * travelTargetIN) / circumference)*2.5;
 mainBaseLeftEncReset;
 mainBaseRightEncReset;
 if(mydirection == Forwards){
   while(mainBaseEnc<degreesToRotate){  //|| BaseEncoder<degreesToRotate
     Spin(speed,speed);
   }
   Brake();
 }else if(mydirection == backwards){
   while(mainBaseEnc>degreesToRotate){  //|| BaseEncoder<degreesToRotate
     Spin(-speed,-speed);
   }
   Brake();
 }
  wait(50, msec); 
}

void Base::driveInches_MotorEnc(dirType mydirection, double travelTargetIN, int speed){
  double circumference = wheelDiameterIN * M_PI;
  double degreesToRotate = (360 * travelTargetIN) / circumference;
  if(mydirection == forwards){
    moveFor(degreesToRotate,degreesToRotate, speed);
  }else if(mydirection == backwards){
    moveFor(degreesToRotate*-1,degreesToRotate*-1, speed);
  }
}

void Base::turnDegrees_MotorEnc(TurnType mydirection, double travelTargetDEG, int speed){
  double BaseCircumference = BaseDiameterIN * M_PI; //51.81
  double degreesToRotate = ((360 * travelTargetDEG) / BaseCircumference)/2; // 32,400
  if(mydirection == Right){
    moveFor(degreesToRotate,degreesToRotate*-1, speed);
  }
  else if(mydirection == Left){
    moveFor(degreesToRotate*-1,degreesToRotate, speed);
  }
}

void Base::driveDegrees_MotorEnc(double degrees, int speed){
  moveFor(degrees, degrees, speed);
}

void Base::turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed){
  moveFor(leftDegrees, rightDegrees, speed);
}

void Base::turnToPoint(double x, double y){
  double place[3]; 
  //link.get_local_location(place[0], place[1], place[2]);
  double diff[] = {x - place[0], y - place[1]};

  double distance = sqrt(pow(diff[0],2) + pow(diff[1],2) * 1.0);
  double heading = (atan2(diff[1], diff[0])*180.0/3.14159265);
  //turnDegrees_MotorEnc
}

/*---BASE_CPP---*/