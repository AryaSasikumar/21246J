#include "intake.h"

enum liftType {extend, retract};

class lift{
  private:
    int liftSpeed = 100;
    int tiltSpeed = 100;
    int slowSpeed = 30;
    void buttonReset();
  public:
    lift();
    void Spin(int speedOne, int speedTwo);
    void Stop(bool type);
    //void autoScore();
    void userControl();   
};

lift::lift(){
  printf("Lift created");
}

void lift::Spin(int speedOne, int speedTwo){
  if(speedOne!=0 && speedTwo!=0){
    liftOne.spin(vex::directionType::fwd, speedOne, vex::velocityUnits::pct);
    liftTwo.spin(vex::directionType::fwd, speedTwo, vex::velocityUnits::pct);
  }else{
    liftOne.stop(vex::brakeType::hold);  
    liftTwo.stop(vex::brakeType::hold);    
  }
}


void lift::Stop(bool type){
  if(type){
      liftOne.stop(vex::brakeType::coast);  
      liftTwo.stop(vex::brakeType::coast);            
    }else{
      liftOne.stop(vex::brakeType::hold);   
      liftTwo.stop(vex::brakeType::hold);             
    }  
}

void lift::buttonReset(){
  if(Bumper.pressing()==1){
    liftOne.resetRotation();
  }
}

//void lift::autoScore(){
//  myIntake().Spin(-50);
//  myBase().Spin(-30, -30);
//  this->Spin(60,-60);
//}

void lift::userControl(){
  if(liftUpBtn){
    this->Spin(90, liftSpeed);
  }else if(liftDownBtn){
    this->Spin(-liftSpeed, -liftSpeed);
  }else if(angleUpBtn){
    this->Spin(tiltSpeed, -tiltSpeed);
  }else if(angleDownBtn){
    this->Spin(-tiltSpeed, tiltSpeed);
  }else if(angleSlowBtn){
    this->Spin(slowSpeed, -slowSpeed);
  }else{
    this->Spin(0, 0);
  }
}



lift myLift;




