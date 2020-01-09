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
    void smartDrive(double maxSpeed, double Distance, bool complete);
    void smartTurn(double maxSpeed, double Angle, bool complete);
    void drivePID(double maxLeftSpeed, double maxRightSpeed, double Distance);
    void driveBackPID(double maxLeftSpeed, double maxRightSpeed, double Distance);
    void driveInches_MotorEnc(dirType mydirection, double travelTargetIN, int speed);
    void turnDegrees_MotorEnc(TurnType mydirection, double travelTargetDEG, int speed);
    void driveDegrees_MotorEnc(double degrees, int speed);
    void driveInches_Enc(dirType mydirection, double travelTargetIN, int speed);
    void turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed);
    void turnDegrees_Gyro(double degrees,int speed);
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
  this->rightSpeed = 0;
  this->leftSpeed = 0;
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

void base::moveFor(double degToRotate_Left, double degToRotate_Right, int speed){
  LF.startRotateFor(degToRotate_Left,degrees,speed,velocityUnits::pct);
  LB.startRotateFor(degToRotate_Left,degrees,speed,velocityUnits::pct);  
  RF.startRotateFor(degToRotate_Right,degrees,speed,velocityUnits::pct);  
  RB.rotateFor(degToRotate_Right,degrees,speed,velocityUnits::pct); 
}


void base::userControl(int bufferSize = 5, bool Stop = false){
 if(macroDriveBtn){
    Spin(45, 45);   
 }else if(slowDriveBackBtn){
   Spin(-30, -30);   
 }
 else{
   if(useTrueSpeed){
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
   }else{
     if(abs(Y_rightJoy)>bufferSize){
       rightSpin(Y_rightJoy);
     }else{
       rightSpin(0);
     } 
     if(abs(Y_leftJoy)>bufferSize){
       leftSpin(Y_leftJoy);
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
 mainBaseEncReset;
 if(mydirection == forwards){
   while(baseEncoder<degreesToRotate){  //|| baseEncoder<degreesToRotate
     Spin(speed,speed);
   }
   Brake();
 }else if(mydirection == backwards){
   while(baseEncoder>degreesToRotate){  //|| baseEncoder<degreesToRotate
     Spin(-speed,-speed);
   }
   Brake();
 }
  wait(50, msec); 
}

void base::smartDrive(double maxSpeed, double Distance, bool complete){
  DriveTrainSmart.setDriveVelocity(maxSpeed, percent);
  DriveTrainSmart.driveFor(Distance, inches, complete);
}
void base::smartTurn(double maxSpeed, double Angle, bool complete){
  DriveTrainSmart.setTurnVelocity(maxSpeed, percent);
  DriveTrainSmart.turnFor(Angle, degrees, complete);
}

void base::drivePID(double maxLeftSpeed, double maxRightSpeed, double Distance){
 mainBaseEncReset;
 Distance = distanceToTravel(Distance);
 wait(10, msec); 
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
   this->leftSpin(lSpeed);
   this->rightSpin(rSpeed);
   if(fabs(drive.error)<=100){ timesGood++; }
   if(timesGood >= 100){ moveComplete = true; }
   task::sleep(1); 
 }
 this->Brake();
}

void base::driveBackPID(double maxLeftSpeed, double maxRightSpeed, double Distance){
 mainBaseEncReset;
 Distance = distanceToTravel(Distance);
 task::sleep(10); 
 drive.dt=0.0001;
 double encoderDeg = mainBaseEnc; //(rightBaseEnc + leftBaseEnc)/2
 double speed = drive.speed(encoderDeg,Distance);
 drive.pre_error = Distance - encoderDeg;
 drive.error = drive.pre_error;
 int timesGood = 0;
 bool moveComplete = false;
 while(!moveComplete && drive.enabled && encoderDeg >= Distance){
   encoderDeg = mainBaseEnc; //(rightBaseEnc + leftBaseEnc)/2
   //printf("Encoder: %f\n",encoderDeg);
   speed = drive.speed(encoderDeg,Distance);
   double lSpeed = (speed>=maxLeftSpeed) ? maxLeftSpeed : speed;
   double rSpeed = (speed>=maxRightSpeed) ? maxRightSpeed : speed;
   leftSpin(lSpeed);
   rightSpin(rSpeed);
   if(fabs(drive.error)<=100){ timesGood++; }
   if(timesGood >= 100){ moveComplete = true; }
   task::sleep(1); 
 }
 Brake();
}
 
void base::turnPID(double maxLeftSpeed, double maxRightSpeed, double Angle){ //450 Gyro units is about 90 degrees
  baseHeadingReset;
  baseRotationReset;
  //Angle = baseInetrial+Angle;
  turn.dt=0.0001;
  double speed = turn.speed(baseInetrial,Angle);
  turn.pre_error = Angle - baseInetrial;
  turn.error = turn.pre_error;
  int timesGood = 0;
  bool moveComplete = false;
  while(!moveComplete && turn.enabled && baseInetrial <= abs(int(Angle))){
    //printf("gyroVal: %lf\n",baseInetrial);
    //printf("Angle: %f\n",Angle);
    if(Angle>0){
      speed = turn.speed(baseInetrial,Angle);
      double lSpeed = (speed>=maxLeftSpeed) ? maxLeftSpeed : speed;
      double rSpeed = (speed>=maxRightSpeed) ? maxRightSpeed : speed;
      Spin(lSpeed,-rSpeed);
    }else if(Angle<0){
      speed = turn.speed(-baseInetrial,-Angle);
      double lSpeed = (speed>=maxLeftSpeed) ? maxLeftSpeed : speed;
      double rSpeed = (speed>=maxRightSpeed) ? maxRightSpeed : speed;
      Spin(-lSpeed,rSpeed);
    }
    if(int(turn.error)<=1.5){ timesGood++; }
    if(timesGood >= 150){ moveComplete = true; }
    task::sleep(1); 
  }
  Brake();
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

void base::turnDegrees_Gyro(double degrees,int speed){ //IDK if this works, lol
  int shift = baseGyro;
  if(degrees < baseGyro){
    degrees = degrees-shift;
  }else{
    degrees = degrees+shift;
  }
  while(baseGyro > degrees){
    Spin(speed,speed);
  }
  Brake();
}

base myBase;