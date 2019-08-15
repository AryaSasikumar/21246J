#include "pidController.h"
#include <cstdio>

enum dirType {forwards, backwards};
enum turnType {right, left};

class base{
  private:
    int leftSpeed = 0;
    int rightSpeed = 0;
    double distanceToTravel(double inchesGiven);
  public:
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
    void turnPID(double Angle);
    void drivePID(double Distance);
    void driveInches_MotorEnc(dirType mydirection, double travelTargetIN, int speed);
    void turnDegrees_MotorEnc(turnType mydirection, double travelTargetDEG, int speed);
    void driveDegrees_MotorEnc(double degrees, int speed);
    void turnDegrees_MotorEnc(double leftDegrees, double rightDegrees,int speed);
    void turnDegrees_Gyro(double degrees,int speed);
};

base::base(){}

void base::Spin(int leftSpeed, int rightSpeed){
  this->rightSpeed = rightSpeed;
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
}


double base::distanceToTravel(double inchesGiven){
  int wheelRadIN = 2;
  float floatDiv = (float)100.0/36.0;
  double Distance = (inchesGiven/(2*M_PI*wheelRadIN))*(360*floatDiv);
  return Distance; //Distance in ticks    
}
    
void base::drivePID(double Distance){
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
    if(fabs(turn.error)<=5){
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