#include "intake.h"

enum liftType {extend, retract};

class lift{
  private:
    int liftSpeed = 100;
    int tiltSpeed = 100;
    int slowSpeed = 20;
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
    liftA.spin(directionType::fwd, speedOne, velocityUnits::pct);
    liftB.spin(directionType::fwd, speedTwo, velocityUnits::pct);
  }else{
    liftA.stop(brakeType::hold);  
    liftB.stop(brakeType::hold);    
  }
}


void lift::Stop(bool type){
  if(type){
      liftA.stop(brakeType::coast);  
      liftB.stop(brakeType::coast);            
    }else{
      liftA.stop(brakeType::hold);   
      liftB.stop(brakeType::hold);             
    }  
}

void lift::buttonReset(){
  if(tiltBumpBtn){
    liftA.resetRotation();
  }
}

void lift::liftUp(int potValue, int speed, int waitTime){
	while(liftSensor <= potValue)
	{
		Spin(speed, speed);
	}
  Stop(false);
	task::sleep(waitTime);
}

void lift::liftDown(int potValue, int speed, int waitTime){
  while(liftSensor >= potValue)
	{
		Spin(-speed, -speed);
	}
  Stop(false);
	task::sleep(waitTime);
}

void lift::tiltForward(int potValue, int speed, int waitTime){
	while(tiltSensor >= potValue)
	{
		Spin(speed, -speed);
	}
  Stop(false);
	task::sleep(waitTime);
}

void lift::tiltBackward(int potValue, int speed, int waitTime){
  while(tiltSensor <= potValue)
	{
		Spin(-speed, speed);
	}
  Stop(false);
	task::sleep(waitTime);
}

void lift::autoScore(){
  myIntake.Spin(-50);
  //myBase.Spin(-30, -30);
  this->Spin(60,-60);
}

void lift::userControl(){
  if(liftUpBtn && tiltBumpBtn){
    this->Spin(90, liftSpeed);
  }else if(liftDownBtn && tiltBumpBtn){
    this->Spin(-liftSpeed, -liftSpeed);
  }else if(angleUpBtn && !tiltBumpBtn){
    this->Spin(tiltSpeed, -tiltSpeed);
  }else if(angleDownBtn && !tiltBumpBtn){
    this->Spin(-tiltSpeed, tiltSpeed);
  }else if(angleSlowBtn && !tiltBumpBtn){
    this->Spin(slowSpeed, -slowSpeed);
  }else if(tiltMacroBtn && !tiltBumpBtn){
    if(tiltSensor>=90){
      this->Spin(tiltSpeed-10, -tiltSpeed+10);
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




