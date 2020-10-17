 #include "pidController.h"

enum dirType {forwards, backwards};
enum TurnType {Right, Left};

class base{
  private:
    int leftSpeed = 0;
    int rightSpeed = 0;
    double distanceToTravel(double inchesGiven);
    const unsigned int trueSpeed[128] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0 , 21, 21, 21, 22, 22, 22, 23, 24, 24,
     25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
     28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
     33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
     37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
     41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
     46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
     52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
     61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
     71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
     80, 83, 84, 86, 86, 87, 87, 88, 88, 90,
     90, 90, 95, 95, 95,100,100,100};

     const unsigned int halfSpeed[128] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0 , 10, 10, 10, 11, 11, 11, 12, 12, 12,
     13, 13, 13, 13, 13, 13, 14, 14, 14, 14,
     14, 15, 15, 15, 15, 16, 16, 16, 16, 16,
     17, 17, 17, 17, 17, 17, 17, 18, 18, 19,
     19, 19, 19, 19, 19, 20, 20, 20, 20, 20,
     21, 21, 21, 21, 22, 22, 22, 23, 23, 23,
     23, 24, 24, 24, 24, 25, 25, 25, 26, 26,
     26, 27, 27, 27, 28, 29, 29, 29, 30, 30,
     31, 32, 32,32, 33, 33, 34, 34, 34, 35,
     36, 36, 36, 37, 37, 38, 39, 39, 39, 39,
     40, 42, 42, 43, 43, 44, 44, 44, 44, 45,
     45, 45, 48, 48, 48,50,50,50};

  public:
    bool useTrueSpeed = true;
    bool toggle = false;
    bool rightFirst=false;
    bool leftFirst=false;
    base();
    //General Drive Base Functions
    void leftSpin(int speed);
    void rightSpin(int speed);
    void Spin(int leftSpeed, int rightSpeed);
    void Hold();
    void Brake();
    void moveFor(double degToRotate_Left, double degToRotate_Right, int speed);

    //User Control Functions
    void userControl(int bufferSize, bool Stop);

    //Autonomous Functions
    //void turnPID(double Angle);//OLDDD
    //void drivePID(double Distance);
    void turnPID(double maxLeftSpeed, double maxRightSpeed, double Angle); //NEWWWW
    void smartDrive(double maxSpeed, double Distance, bool complete);
    void smartTurn(double maxSpeed, double Angle, bool complete);
    void drivePID(double maxLeftSpeed, double maxRightSpeed, double Distance);
    void driveBackPID(double maxLeftSpeed, double maxRightSpeed, double Distance);
    void driveInches_MotorEnc(dirType mydirection, double travelTargetIN, int speed);
    void turnDegrees_MotorEnc(TurnType mydirection, double travelTargetDEG, int speed);
    void driveDegrees_MotorEnc(double degrees, int speed);
    void driveInches_Enc(dirType mydirection, double travelTargetIN, int speed);
    void turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed);

    void lineStraighten();
};

base::base(){
  printf("Base created");
}

void base::Spin(int leftSpeed, int rightSpeed){
  rightSpeed = rightSpeed;
  leftSpeed = leftSpeed;
  leftSpin(leftSpeed);
  rightSpin(rightSpeed);
}

void base::rightSpin(int speed = 0){
  this->rightSpeed = speed;
  if(rightSpeed != 0){
    RB.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
    RT.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
    RF.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
  }else{
    RB.stop(vex::brakeType::coast); 
    RT.stop(vex::brakeType::coast); 
    RF.stop(vex::brakeType::coast);
  }
}

void base::leftSpin(int speed = 0){
  this->leftSpeed = speed;
  if(leftSpeed != 0){
    LB.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
    LT.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
    LF.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
  }else{
    LB.stop(vex::brakeType::coast);  
    LT.stop(vex::brakeType::coast);  
    LF.stop(vex::brakeType::coast);  
  }
}

void base::Hold(){
  this->rightSpeed = 0;
  this->leftSpeed = 0;
  LB.stop(vex::brakeType::hold);
  LT.stop(vex::brakeType::hold);
  LF.stop(vex::brakeType::hold);
  RB.stop(vex::brakeType::hold);
  RT.stop(vex::brakeType::hold);
  RF.stop(vex::brakeType::hold);  
}

void base::Brake() {
  this->rightSpeed = 0;
  this->leftSpeed = 0;
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LT.stop(vex::brakeType::brake);
  RT.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

void base::moveFor(double degToRotate_Left, double degToRotate_Right, int speed){
  LF.startRotateFor(degToRotate_Left,degrees,speed,velocityUnits::pct);
  LB.startRotateFor(degToRotate_Left,degrees,speed,velocityUnits::pct);  
  LT.startRotateFor(degToRotate_Left,degrees,speed,velocityUnits::pct);  
  RF.startRotateFor(degToRotate_Right,degrees,speed,velocityUnits::pct);  
  RT.startRotateFor(degToRotate_Right,degrees,speed,velocityUnits::pct);  
  RB.rotateFor(degToRotate_Right,degrees,speed,velocityUnits::pct); 
}

void base::userControl(int bufferSize = 5, bool Stop = false){//driveToggleBtn
 if(macroDriveBtn){
    Spin(45, 45);   
 }else if(slowDriveBackBtn){
   Spin(-30, -30);   
 }
 else if(driveToggleBtn){
   toggle=!toggle;
   vex::task::sleep(300);
 }
 else{
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
}

double base::distanceToTravel(double inchesGiven){
  int wheelRadIN = 2;
  float floatDiv = (float)95.0/36.0;
  double Distance = ((inchesGiven/(M_PI*wheelRadIN))*(360*floatDiv))/4;
  return Distance; //Distance in ticks    
}

void base::driveInches_Enc(dirType mydirection, double travelTargetIN, int speed){
 double lSpeed = speed;
 double rSpeed = speed;
 double circumference = wheelDiameterIN * M_PI;
 double degreesToRotate = ((360.0 * travelTargetIN) / circumference)*2.5;
 mainBaseLeftEncReset;
 mainBaseRightEncReset;
 if(mydirection == forwards){
   while(mainBaseEnc<degreesToRotate){  //|| baseEncoder<degreesToRotate
     Spin(speed,speed);
   }
   Brake();
 }else if(mydirection == backwards){
   while(mainBaseEnc>degreesToRotate){  //|| baseEncoder<degreesToRotate
     Spin(-speed,-speed);
   }
   Brake();
 }
  wait(50, msec); 
}

void base::driveInches_MotorEnc(dirType mydirection, double travelTargetIN, int speed){
  double circumference = wheelDiameterIN * M_PI;
  double degreesToRotate = (360 * travelTargetIN) / circumference;
  if(mydirection == forwards){
    moveFor(degreesToRotate,degreesToRotate, speed);
  }else if(mydirection == backwards){
    moveFor(degreesToRotate*-1,degreesToRotate*-1, speed);
  }
}

void base::turnDegrees_MotorEnc(TurnType mydirection, double travelTargetDEG, int speed){
  double baseCircumference = baseDiameterIN * M_PI; //51.81
  double degreesToRotate = ((360 * travelTargetDEG) / baseCircumference)/2; // 32,400
  if(mydirection == Right){
    moveFor(degreesToRotate,degreesToRotate*-1, speed);
  }
  else if(mydirection == Left){
    moveFor(degreesToRotate*-1,degreesToRotate, speed);
  }
}

void base::driveDegrees_MotorEnc(double degrees, int speed){
  moveFor(degrees, degrees, speed);
}

void base::turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed){
  moveFor(leftDegrees, rightDegrees, speed);
}

void base::lineStraighten(){
  while(rightLineTracker.reflectivity()<75 && leftLineTracker.reflectivity()<75){
    Spin(10,10);
    if(rightLineTracker.reflectivity()>75){
      rightFirst=true;
    }
    else if(leftLineTracker.reflectivity()>75){
      leftFirst=true;
    }
  }
  Brake();
  vex::task::sleep(1000);
  if(rightFirst){
    while(leftLineTracker.reflectivity()<92){
      RB.stop(vex::brakeType::hold); 
      RT.stop(vex::brakeType::hold); 
      RF.stop(vex::brakeType::hold);
      LB.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
      LT.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
      LF.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
    }
    Brake();
  }
  if(leftFirst){
    while(rightLineTracker.reflectivity()<92){
      LB.stop(vex::brakeType::hold); 
      LT.stop(vex::brakeType::hold); 
      LF.stop(vex::brakeType::hold);
      RB.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
      RT.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
      RF.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
    }
    Brake();
  }
}

base myBase;