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
  Spin(60,-60);
}

void lift::userControl(){
  // if(tiltBumpBtn){
  //   if(liftUpBtn){
  //     Spin(90, liftSpeed);
  //   }else if(liftDownBtn){
  //     Spin(-liftSpeed, -liftSpeed);
  //   }else if(angleUpBtn){
  //     if(liftSensor >= 82){
  //       Spin(-liftSpeed, -liftSpeed);
  //     } else {
  //       Spin(tiltSpeed, -tiltSpeed);
  //     }
  //   }else if(angleDownBtn){
  //     Spin(0,0);
  //   }else if(angleSlowBtn){
  //     Spin(slowSpeed, -slowSpeed);
  //   }else if(tiltMacroBtn){
  //     if(tiltSensor>=90){
  //       Spin(tiltSpeed-10, -tiltSpeed+10);
  //     }else if(tiltSensor>=41){
  //       Spin(slowSpeed, -slowSpeed);
  //     }else{
  //       Spin(10, -10);  
  //     }
  //   }else{
  //     Spin(0, 0);
  //   }
  // } else{
  //   if(liftUpBtn){
  //     Spin(-tiltSpeed, tiltSpeed);
  //   }else if(liftDownBtn){
  //     Spin(-tiltSpeed, tiltSpeed);
  //   }else if(angleUpBtn){
  //     Spin(tiltSpeed, -tiltSpeed);
  //   }else if(angleDownBtn){
  //     Spin(-tiltSpeed, tiltSpeed);
  //   }else if(angleSlowBtn){
  //     Spin(slowSpeed, -slowSpeed);
  //   }else if(tiltMacroBtn){
  //     if(tiltSensor>=90){
  //       Spin(tiltSpeed-10, -tiltSpeed+10);
  //     }else if(tiltSensor>=41){
  //       Spin(slowSpeed, -slowSpeed);
  //     }else{
  //       Spin(10, -10);  
  //     }
  //   }else{
  //     Spin(0, 0);
  //   }
  // }
  


  if(liftUpBtn){
    Spin(90, liftSpeed);
  }else if(liftDownBtn){
    Spin(-liftSpeed, -liftSpeed);
  }else if(angleUpBtn){
    Spin(tiltSpeed, -tiltSpeed);
  }else if(angleDownBtn){
    Spin(-tiltSpeed, tiltSpeed);
  }else if(angleSlowBtn){
    Spin(slowSpeed, -slowSpeed);
  }else if(tiltMacroBtn){
    if(tiltSensor>=90){
      Spin(tiltSpeed-10, -tiltSpeed+10);
    }else if(tiltSensor>=41){
      Spin(slowSpeed, -slowSpeed);
    }else{
      Spin(10, -10);  
    }
  }else{
    Spin(0, 0);
  }
}

lift myLift;




