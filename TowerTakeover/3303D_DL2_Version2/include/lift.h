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
    void autoScore();
    void liftUp(int potValue, int speed, int waitTime);
    void liftDown(int potValue, int speed, int waitTime);
    void tiltForward(int potValue, int speed, int waitTime);
    void tiltBackward(int potValue, int speed, int waitTime);
    void userControl();   
};

lift::lift(){
  printf("Lift created");
}

void lift::Spin(int speedOne, int speedTwo){
  if(speedOne!=0 && speedTwo!=0){
    liftA.spin(vex::directionType::fwd, speedOne, vex::velocityUnits::pct);
    liftB.spin(vex::directionType::fwd, speedTwo, vex::velocityUnits::pct);
  }else{
    liftA.stop(vex::brakeType::hold);  
    liftB.stop(vex::brakeType::hold);    
  }
}


void lift::Stop(bool type){
  if(type){
      liftA.stop(vex::brakeType::coast);  
      liftB.stop(vex::brakeType::coast);            
    }else{
      liftA.stop(vex::brakeType::hold);   
      liftB.stop(vex::brakeType::hold);             
    }  
}

void lift::buttonReset(){
  if(Bumper.pressing()==1){
    liftA.resetRotation();
  }
}

void lift::liftUp(int potValue, int speed, int waitTime){
	while(liftSensor <= potValue)
	{
		Spin(speed, speed);
	}
  Stop(false);
	vex::task::sleep(waitTime);
}

void lift::liftDown(int potValue, int speed, int waitTime){
  while(liftSensor >= potValue)
	{
		Spin(-speed, -speed);
	}
  Stop(false);
	vex::task::sleep(waitTime);
}

void lift::tiltForward(int potValue, int speed, int waitTime){
	while(liftPot.value(vex::rotationUnits::deg) >= potValue)
	{
		Spin(speed, -speed);
	}
  Stop(false);
	vex::task::sleep(waitTime);
}

void lift::tiltBackward(int potValue, int speed, int waitTime){
  while(liftPot.value(vex::rotationUnits::deg) <= potValue)
	{
		Spin(-speed, speed);
	}
  Stop(false);
	vex::task::sleep(waitTime);
}

void lift::autoScore(){
  myIntake.Spin(-50);
  //myBase.Spin(-30, -30);
  this->Spin(60,-60);
}

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
  }else if(tiltMacroBtn){
    if(tiltSensor>=90){
      this->Spin(tiltSpeed, -tiltSpeed);
    }else if(tiltSensor>=41){
      this->Spin(slowSpeed, -slowSpeed);
    }
    else{
      this->Spin(10, -10);  
    }
  }else{
    this->Spin(0, 0);
  }
}

lift myLift;




