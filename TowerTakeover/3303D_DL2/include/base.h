#include "pidController.h"

enum dirType {forwards, backwards};
enum turnType {right, left};

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

  public:
    bool useTrueSpeed = true;
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
    void drivePID(double maxLeftSpeed, double maxRightSpeed, double Distance);
    void driveInches_MotorEnc(dirType mydirection, double travelTargetIN, int speed);
    void turnDegrees_MotorEnc(turnType mydirection, double travelTargetDEG, int speed);
    void driveDegrees_MotorEnc(double degrees, int speed);
    void driveInches_Enc(dirType mydirection, double travelTargetIN, int speed);
    void turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed);
    void turnDegrees_Gyro(double degrees,int speed);
};

base::base(){
  printf("Base created");
}

void base::Spin(int leftSpeed, int rightSpeed){
  this->rightSpeed = rightSpeed;
  this->leftSpeed = leftSpeed;
  rightSpin(rightSpeed);
  leftSpin(leftSpeed);
}

void base::rightSpin(int speed = 0){
  this->rightSpeed = speed;
  if(rightSpeed != 0){
    RB.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
    RF.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
  }else{
    RB.stop(vex::brakeType::coast); 
    RF.stop(vex::brakeType::coast);
  }
}

void base::leftSpin(int speed = 0){
  this->leftSpeed = speed;
  if(leftSpeed != 0){
    LB.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
    LF.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
  }else{
    LB.stop(vex::brakeType::coast);  
    LF.stop(vex::brakeType::coast);  
  }
}

void base::Hold(){
  this->rightSpeed = 0;
  this->leftSpeed = 0;
  LB.stop(vex::brakeType::hold);
  LF.stop(vex::brakeType::hold);
  RB.stop(vex::brakeType::hold);
  RF.stop(vex::brakeType::hold);  
}

void base::Brake() {
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

void base::moveFor(double degToRotate_Left, double degToRotate_Right, int speed){
  LB.startRotateFor(degToRotate_Left,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  LF.startRotateFor(degToRotate_Left,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
  RF.startRotateFor(degToRotate_Right,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
  RB.rotateFor(degToRotate_Right,vex::rotationUnits::deg,speed,vex::velocityUnits::pct); 
}

void base::userControl(int bufferSize = 10, bool Stop = false){
 if(autoScoreBtn){
   this->Spin(-30, -30);
 }else{
   if(baseLockBtn){
     vex::task::sleep(200);
     Stop = !Stop;
     if(Stop==true){
       this->Hold();
     }else{
       this->Spin(0,0);
     }
   }
   if(this->useTrueSpeed){
     if(abs(Y_rightJoy)>bufferSize){
       if(Y_rightJoy>0){
         this->rightSpin(trueSpeed[abs(Y_rightJoy)]);
       }else{
         this->rightSpin(-trueSpeed[abs(Y_rightJoy)]);
       }
     }else{
       this->rightSpin(0);
     } 
     if(abs(Y_leftJoy)>bufferSize){
       if(Y_leftJoy>0){
         this->leftSpin(trueSpeed[abs(Y_leftJoy)]);
       }else{
         this->leftSpin(-trueSpeed[abs(Y_leftJoy)]);
       }
     }else{
       this->leftSpin(0);
     } 
    
   }else{
     if(abs(Y_rightJoy)>bufferSize){
       this->rightSpin(Y_rightJoy);
     }else{
       this->rightSpin(0);
     } 
     if(abs(Y_leftJoy)>bufferSize){
       this->leftSpin(Y_leftJoy);
     }else{
       this->leftSpin(0);
     } 
   }
  
 }  
}

/*void base::userControl(int bufferSize = 10, bool Stop = false){
  if(baseLockBtn){
    vex::task::sleep(200);
    Stop = !Stop;
    if(Stop==true){
      this->Hold();
    }else{
      this->Spin(0,0);
    }
  }   
  if(abs(Y_rightJoy)>bufferSize){
    this->rightSpin(Y_rightJoy);
  }else{
    this->rightSpin(0);
  }  
  if(abs(Y_leftJoy)>bufferSize){
    this->leftSpin(Y_leftJoy);
  }else{ 
    this->leftSpin(0);
  }     
}*/


double base::distanceToTravel(double inchesGiven){
  int wheelRadIN = 2;
  float floatDiv = (float)95.0/36.0;
  double Distance = (inchesGiven/(2*M_PI*wheelRadIN))*(360*floatDiv);
  return Distance; //Distance in ticks    
}

void base::driveInches_Enc(dirType mydirection, double travelTargetIN, int speed){
 double lSpeed = speed;
 double rSpeed = speed;
 double circumference = wheelDiameterIN * M_PI;
 double degreesToRotate = ((360.0 * travelTargetIN) / circumference)*2.5;
 mainBaseEncReset;
 if(mydirection == forwards){
   while(baseEncoder<degreesToRotate){  //|| baseEncoder<degreesToRotate
     this->Spin(speed,speed);
   }
   this->Brake();
  
 }else if(mydirection == backwards){
   while(baseEncoder>degreesToRotate){  //|| baseEncoder<degreesToRotate
     this->Spin(-speed,-speed);
   }
   this->Brake();
 }
 vex:: task::sleep(500);
}


/*void base::drivePID(double Distance){
  Distance = distanceToTravel(Distance);
  rightEncoder.resetRotation(); 
  leftEncoder.resetRotation();
  vex::task::sleep(50); 
  drive.dt=0.0001;
  double encoderDeg = (rightEncoder.rotation(vex::rotationUnits::deg) + leftEncoder.rotation(vex::rotationUnits::deg))/2;
  double speed = drive.speed(encoderDeg,Distance);
  drive.pre_error = Distance - encoderDeg;
  drive.error = drive.pre_error;
  int timesGood = 0;
  bool moveComplete = false;
  while(!moveComplete && drive.enabled){ 
    encoderDeg = (rightEncoder.rotation(vex::rotationUnits::deg) + leftEncoder.rotation(vex::rotationUnits::deg))/2;
    speed = drive.speed(encoderDeg,Distance);
    this->rightSpin(speed);
    this->leftSpin(speed);
    if(fabs(drive.error)<=40){
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    vex:: task:: sleep(1);
  }
  this->Brake();
  vex:: task:: sleep(10);
}

void base::turnPID(double Angle){
  Gyro.startCalibration();
  while(Gyro.isCalibrating()){}
  vex::task::sleep(100);    
  turn.dt=0.0001;
  double speed = turn.speed(Gyro.value(vex::rotationUnits::deg),Angle);
  turn.pre_error = Angle - Gyro.value(vex::rotationUnits::deg);
  turn.error = turn.pre_error;
  int timesGood = 0;
  bool moveComplete = false;
  while(!moveComplete && turn.enabled){
    if(Angle>0){
      speed = turn.speed(Gyro.value(vex::rotationUnits::deg),Angle);
      this->Spin(speed,-speed);
    }else{
      speed = turn.speed(-Gyro.value(vex::rotationUnits::deg),-Angle);
      this->Spin(-speed,speed);
    }
    if(fabs(turn.error)<=3){
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    vex:: task:: sleep(1);
  }
  this->Brake();
  vex:: task:: sleep(10);
}*/

void base::drivePID(double maxLeftSpeed, double maxRightSpeed, double Distance){
 Distance = distanceToTravel(Distance);
 baseEncoder.resetRotation();
 vex::task::sleep(50);
 drive.dt=0.0001;
 double encoderDeg = mainBaseEnc; //(rightBaseEnc + leftBaseEnc)/2
 double speed = drive.speed(encoderDeg,Distance);
 drive.pre_error = Distance - encoderDeg;
 drive.error = drive.pre_error;
 int timesGood = 0;
 bool moveComplete = false;
 while(!moveComplete && drive.enabled && encoderDeg <= Distance){
   encoderDeg = mainBaseEnc; //(rightBaseEnc + leftBaseEnc)/2
   speed = drive.speed(encoderDeg,Distance);
   double lSpeed = (speed>=maxLeftSpeed) ? maxLeftSpeed : speed;
   double rSpeed = (speed>=maxRightSpeed) ? maxRightSpeed : speed;
   this->rightSpin(rSpeed);
   this->leftSpin(lSpeed);
   if(fabs(drive.error)<=100){
     timesGood++;
   }
   if(timesGood >= 100){
     moveComplete = true;
   }
   vex:: task:: sleep(1);
 }
 this->Brake();
 vex:: task:: sleep(10);
}
 
void base::turnPID(double maxLeftSpeed, double maxRightSpeed, double Angle){ //450 Gyro units is about 90 degrees
  Angle = baseGyro+Angle;
  turn.dt=0.0001;
  double speed = turn.speed(baseGyro,Angle);
  turn.pre_error = Angle - baseGyro;
  turn.error = turn.pre_error;
  int timesGood = 0;
  bool moveComplete = false;
  while(!moveComplete && turn.enabled && baseGyro <= abs(int(Angle))){
    printf("gyroVal: %ld\n",baseGyro);
    printf("Angle: %f\n",Angle);
    if(Angle>0){
      speed = turn.speed(baseGyro,Angle);
      double lSpeed = (speed>=maxLeftSpeed) ? maxLeftSpeed : speed;
      double rSpeed = (speed>=maxRightSpeed) ? maxRightSpeed : speed;
      this->Spin(lSpeed,-rSpeed);
    }else if(Angle<0){
      speed = turn.speed(-baseGyro,-Angle);
      double lSpeed = (speed>=maxLeftSpeed) ? maxLeftSpeed : speed;
      double rSpeed = (speed>=maxRightSpeed) ? maxRightSpeed : speed;
      this->Spin(-lSpeed,rSpeed);
    }
    if(int(turn.error)<=50){
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    vex:: task:: sleep(1);
  }
  this->Brake();
  vex:: task:: sleep(10);
}


void base::driveInches_MotorEnc(dirType mydirection, double travelTargetIN, int speed){
  double circumference = wheelDiameterIN * M_PI;
  double degreesToRotate = (360 * travelTargetIN) / circumference;
  if(mydirection == forwards){
    this->moveFor(degreesToRotate,degreesToRotate, speed);
  }else if(mydirection == backwards){
    this->moveFor(degreesToRotate*-1,degreesToRotate*-1, speed);
  }
}

void base::turnDegrees_MotorEnc(turnType mydirection, double travelTargetDEG, int speed){
  double baseCircumference = baseDiameterIN * M_PI; //51.81
  double degreesToRotate = ((360 * travelTargetDEG) / baseCircumference)/2; // 32,400
  if(mydirection == right){
    this->moveFor(degreesToRotate,degreesToRotate*-1, speed);
  }
  else if(mydirection == left){
    this->moveFor(degreesToRotate*-1,degreesToRotate, speed);
  }
}

void base::driveDegrees_MotorEnc(double degrees, int speed){
  this->moveFor(degrees, degrees, speed);
}

void base::turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed){
  this->moveFor(leftDegrees, rightDegrees, speed);
}

void base::turnDegrees_Gyro(double degrees,int speed){ //IDK if this works 
  int shift = baseGyro;
  if(degrees < baseGyro){
    degrees = degrees-shift;
  }else{
    degrees = degrees+shift;
  }
  while(baseGyro > degrees){
    this->Spin(speed,speed);
  }
  this->Brake();
}

base myBase;


