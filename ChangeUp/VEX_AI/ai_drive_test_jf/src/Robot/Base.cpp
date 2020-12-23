#include "vex.h"

Base::Base(){
  printf("Base created");
}


void Base::LeftSpin(int speed = 0){
  if(speed != 0){
    LeftDrive.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    LeftDrive.stop(vex::brakeType::coast);  
  }
}

void Base::RightSpin(int speed = 0){
  if(speed != 0){
    RightDrive.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    RightDrive.stop(vex::brakeType::coast); 
  }
}

void Base::Spin(int leftSpeed, int rightSpeed){
  LeftSpin(leftSpeed);
  RightSpin(rightSpeed);
}

void Base::moveFor(double degreesToRotate_Left, double degreesToRotate_Right, int speed){
  RightDrive.rotateFor(degreesToRotate_Right, degrees, speed, velocityUnits::pct);
  LeftDrive.rotateFor(degreesToRotate_Left, degrees, speed, velocityUnits::pct);
}


void Base::Hold(){
  Drive.stop(vex::brakeType::hold);
}

void Base::Brake() {
  Drive.stop(vex::brakeType::brake);
}

double Base::distanceToTravel(double inchesGiven){
  int wheelRadIN = 2;
  float floatDiv = (float)95.0/36.0;
  double Distance = ((inchesGiven/(M_PI*wheelRadIN))*(360*floatDiv))/4;
  return Distance; //Distance in ticks    
}


void Base::driveDegrees_MotorEnc(double degrees, int speed){
  moveFor(degrees, degrees, speed);
}
void Base::turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed){
  moveFor(leftDegrees, rightDegrees, speed);
}

void Base::driveInches_MotorEnc(DirType mydirection, double travelTargetIN, int speed){
  // double circumference = Drive. * M_PI;
  // double degreesToRotate = (360 * travelTargetIN) / circumference;
  // if(mydirection == Forwards){
  //   moveFor(degreesToRotate,degreesToRotate, speed);
  // }else if(mydirection == Backwards){
  //   moveFor(degreesToRotate*-1,degreesToRotate*-1, speed);
  // }
}

void Base::turnDegrees_MotorEnc(TurnType mydirection, double travelTargetDEG, int speed){
  // double BaseCircumference = BaseDiameterIN * M_PI; //51.81
  // double degreesToRotate = ((360 * travelTargetDEG) / BaseCircumference)/2; // 32,400
  // //Drive.turnFor()
  // if(mydirection == Right){
  //   moveFor(degreesToRotate,degreesToRotate*-1, speed);
  // }
  // else if(mydirection == Left){
  //   moveFor(degreesToRotate*-1,degreesToRotate, speed);
  // }
}

Base myBase;

int UsercontrolTask(){//driveToggleBtn
  int bufferSize = 5;
  while(true){
    if(macroDriveBtn){
      myBase.Spin(45, 45);   
    }else if(slowDriveBackBtn){
      myBase.Spin(-30, -30);   
    }
    else if(driveToggleBtn){
      myBase.toggle=!myBase.toggle;
      vex::task::sleep(300);
    }
    else{
      if(myBase.toggle==true){
        if(abs(Y_Right_Joy)>bufferSize){
          if(Y_Right_Joy>0){
            myBase.RightSpin(myBase.halfSpeed[abs(Y_Right_Joy)]);
          }else{
            myBase.RightSpin(-myBase.halfSpeed[abs(Y_Right_Joy)]);
          }
        }else{
          myBase.RightSpin(0);
        } 
        if(abs(Y_Left_Joy)>bufferSize){
          if(Y_Left_Joy>0){
            myBase.LeftSpin(myBase.halfSpeed[abs(Y_Left_Joy)]);
          }else{
            myBase.LeftSpin(-myBase.halfSpeed[abs(Y_Left_Joy)]);
          }
        }else{
          myBase.LeftSpin(0);
        } 
      } 
      else {
          if(abs(Y_Right_Joy)>bufferSize){
          if(Y_Right_Joy>0){
            myBase.RightSpin(myBase.trueSpeed[abs(Y_Right_Joy)]);
          }else{
            myBase.RightSpin(-myBase.trueSpeed[abs(Y_Right_Joy)]);
          }
        }else{
          myBase.RightSpin(0);
        } 
        if(abs(Y_Left_Joy)>bufferSize){
          if(Y_Left_Joy>0){
            myBase.LeftSpin(myBase.trueSpeed[abs(Y_Left_Joy)]);
          }else{
            myBase.LeftSpin(-myBase.trueSpeed[abs(Y_Left_Joy)]);
          }
        }else{
          myBase.LeftSpin(0);
        } 
      }
    }  
  } 
  return 0;
}