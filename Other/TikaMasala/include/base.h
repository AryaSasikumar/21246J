#include "vex.h"

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
    void xDriveControl();
};

base::base(){
  printf("Base created\n\n");
}

void base::Spin(int leftSpeed, int rightSpeed){
  rightSpeed = rightSpeed;
  leftSpeed = leftSpeed;
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

void base::xDriveControl() //void function - has no return type.
{
    double X_comp = Controller1.Axis4.position(vex::percentUnits::pct);  //Takes the x-component from axis-4 on the controller (left-negative, right-positive)
    double Y_comp = Controller1.Axis3.position(vex::percentUnits::pct);  //Takes the y-component from axis-3 on the controller (up-positive, down-negative)
    double rot_comp = Controller1.Axis1.position(vex::percentUnits::pct);//Takes the rotate-component from axis-1 on the controller (left-negative, right-positive)
    
    //Assuming the following control scheme:
	//X-Drive Base, where all motors drive forward when set to 127
	//X and Y are as they are defined in the Cartesian coordinate plane
	//Rotation is positive for CW, negative for CCW

    //Uses algebra to add the individual components to find how much power to give to each motor repectively.
	double rfBase = Y_comp - X_comp - rot_comp; //For the right-front base: y-component subtract x-component subtract rotate-component
	double lfBase = Y_comp + X_comp + rot_comp; //For the left-front base: y-component add x-component add rotate-component
	double rbBase = Y_comp + X_comp - rot_comp; //For the right-back base: y-component add x-component subtract rotate-component
	double lbBase = Y_comp - X_comp + rot_comp; //For the left-back base: y-component subtract x-component add rotate-copmonent
    
    if(X_comp != 0 || Y_comp != 0 || rot_comp != 0) //IF any of the values are NOT zero. Alternatively, if(!(x_comp == 0 && y_comp == 0 && rot_comp == 0))
    {
        LF.spin(vex::directionType::fwd,lfBase,vex::velocityUnits::pct); //Applies left-front base to left-front motor
        RB.spin(vex::directionType::fwd,rbBase,vex::velocityUnits::pct); //Applies right-back base to right-back motor
        LB.spin(vex::directionType::fwd,lbBase,vex::velocityUnits::pct);  //Applies left-back base to the left-back motor
        RF.spin(vex::directionType::fwd,rfBase,vex::velocityUnits::pct);//Applies right-front base to right-front motor
    }
    else //ELSE (all components are zero) - STOP
    {
        RB.stop(vex::brakeType::coast); //STOP motor
        LF.stop(vex::brakeType::coast); //STOP motor
        LB.stop(vex::brakeType::coast);  //STOP motor
        RF.stop(vex::brakeType::coast);//STOP motor
    }
}

void base::userControl(int bufferSize = 5, bool Stop = false){
 if(autoScoreBtn){
    Spin(-30, -30);
 }else if(macroDriveBtn){
    Spin(45, 45);   
 }else{
   if(baseLockBtn){
     task::sleep(200);
     Stop = !Stop;
     if(Stop==true){ 
      Hold();
     }
     else{
      Spin(0,0);
     }
   }
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
base myBase;