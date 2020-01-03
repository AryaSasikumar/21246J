#include "base.h"

class intake{
  private:
    int inSpeed = 100;
    int outSpeed = -100;
    int inSpeedWhileUp = 100;
    int outSpeedWhileUp = -60;
    int slowSpeed = 20;
    bool enable = false;
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
  if (!intakeBtn && !outtakeBtn) {
    if (!enable) {
      Stop();
      enable = true;
    }
  } else {
    enable = false;
  }
  if (!enable) {
    if(intakeBtn && outtakeBtn){
      Spin(slowSpeed);
    }else if(intakeBtn){ 
      Spin(inSpeed);
    }else if(outtakeBtn){ 
      Spin(outSpeed);
    }else if(macroDriveBtn){
      Spin(outtakeBtn);
    }else if(tiltMacroBtn && tiltSensor>=41 && tiltSensor<=90){
      //Spin(-slowSpeed);
    }
  }
}



intake myIntake;

