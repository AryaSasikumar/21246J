#include "lift.h"

class AutonomusRoutines{
  private:
    
  public:
    void blueFrontAuton();
    void blueBackAuton();
    void redFrontAuton();
    void redBackAuton();
    void simpleAuton();
    void score();
};

/*void score(){             FIXXXXX FOR NEW BOT
 tilt1.resetRotation() ;
 tilt1.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
 tilt2.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);   
 
 while(tilt1.rotation(vex::rotationUnits::deg)<525 ){
   if(tilt1.rotation(vex::rotationUnits::deg)>200){
   tilt1.spin(vex::directionType::fwd,30,vex::velocityUnits::pct);
   tilt2.spin(vex::directionType::fwd,30,vex::velocityUnits::pct); 
   }
   vex::task::sleep(1) ;
 }
 vex::task::sleep(1250) ;
 autoScore();
 vex::task::sleep(2000) ;
}*/

void AutonomusRoutines::blueFrontAuton(){
  myBase.turnPID(90);
  //myBase.drivePID(60, 60, 10);
}
void AutonomusRoutines::blueBackAuton(){
  
}
void AutonomusRoutines::redFrontAuton(){
  
}
void AutonomusRoutines::redBackAuton(){
  
}
void AutonomusRoutines::simpleAuton(){
  
}

AutonomusRoutines myAuton;