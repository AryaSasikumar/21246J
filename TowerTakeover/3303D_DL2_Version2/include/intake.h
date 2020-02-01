#include "base.h"

class intake{
  private:
    int inSpeed = 100;
    int outSpeed = -100;
    int inSpeedWhileUp = 100;
    int outSpeedWhileUp = -60;
    int slowSpeed = 20;
    bool enabled = false;
  public:
    intake();
    void Spin(int speed);
    void Stop();
    void userControl();
};
intake::intake(){
  printf("Intake created");
}

void intake::Spin(int speed){
  leftIntake.spin(directionType::fwd, speed, velocityUnits::pct);
  rightIntake.spin(directionType::fwd, speed, velocityUnits::pct);
}
void intake::Stop(){
  leftIntake.stop(brakeType::brake);  
  rightIntake.stop(brakeType::brake);  
}

void intake::userControl(){
  if(intakeBtn && outtakeBtn){
    Spin(slowSpeed);
  }else if(intakeBtn){ 
    Spin((liftSensor >= 100) ? inSpeedWhileUp : inSpeed);
  }else if(outtakeBtn){ 
    Spin((liftSensor >= 100) ? outSpeedWhileUp : outSpeed);
  }else if(macroDriveBtn){
    Spin(outtakeBtn);
  }else if(tiltMacroBtn && tiltSensor>=41 && tiltSensor<=90){
    //Spin(-slowSpeed);
  }else if(autoScoreBtn){
    Spin(-5);
  }else{
    Stop();
  }
}



intake myIntake;

