#include "base.h"

class intake{
  private:
  public:
    intake();
    void Spin(int speed);
    void Stop();
    void ballToTop();
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

void intake::ballToTop(){
  while(colorChecker.reflectivity() < 50){
    rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
  }
}

void intake::userControl(){

 if(filterOutBtn){
    rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
 }
 else if(filterUpBtn){
   rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
   leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
 }
 else if(allUpBtn){
   rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);
   leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
 }
 else if(shootBtn){
   rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);
   leftIntake.spin(directionType::rev, 30, velocityUnits::rpm);
 }
 else{
   Stop();
 }
}

intake myIntake;

