/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"
vex::brain       Brain;
// A global instance of vex::competition


// define your global instances of motors and other devices here
vex::motor LF = vex::motor( vex::PORT2 );
vex::motor LB = vex::motor( vex::PORT3 );
vex::motor RF = vex::motor( vex::PORT8, true );
vex::motor RB = vex::motor( vex::PORT9, true );

vex::motor leftIntake  = vex::motor( vex::PORT1, true );
vex::motor rightIntake = vex::motor( vex::PORT10 );

vex::motor tilt1  = vex::motor( vex::PORT7, true );
vex::motor tilt2  = vex::motor( vex::PORT4 );

vex::controller Controller1 = vex::controller();

vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.F);
vex::encoder leftEncoder  = vex::encoder(Brain.ThreeWirePort.C) ;
vex::encoder rightEncoder = vex::encoder(Brain.ThreeWirePort.G) ;
vex::bumper Bumper = vex::bumper(Brain.ThreeWirePort.B);

const double wheelDiameterIN  = 4; 
const double baseDiameterIN  = 16.5;

#define Y_leftJoy Controller1.Axis3.value()
#define Y_rightJoy Controller1.Axis2.value()

#define X_leftJoy Controller1.Axis4.value()
#define X_rightJoy Controller1.Axis1.value()

#define baseLockBtn Controller1.ButtonA.pressing()

#define tiltOutBtn Controller1.ButtonL1.pressing()
#define tiltInBtn  Controller1.ButtonL2.pressing()

#define intakeBtn Controller1.ButtonR1.pressing()
#define outtakeBtn Controller1.ButtonR2.pressing()

/*
#define intakeBtn vexRT[Btn6D]
#define outtakeBtn vexRT[Btn6U]

#define liftUpBtn vexRT[Btn5U]
#define liftDownBtn vexRT[Btn5D]

#define changeDirectionBtn vexRT[Btn7L]

#define liftSensor SensorValue[liftPot]
#define leftBaseSensor SensorValue[leftBaseEncoder]
#define rightBaseSensor SensorValue[rightBaseEncoder]
#define baseGyroSensor SensorValue[baseGyro]*/

/*---------------------------------------------------------------------------*/
/*                            PID Functions                                  */
/*---------------------------------------------------------------------------*/

class pidController{
    private:
        double min = -100.0; // min - minimum value of manipulated variable
        double max = 100.0; // max - maximum value of manipulated variable
        double Kp = 0.02; // Kp -  proportional gain 
        double Ki = 0.0; // Ki -  Integral gain
        double integral = 0.0;
    public:
        pidController(double min, double max, double Kp, double Ki, double Kd, double dt);
        double speed(double currentVal, double desiredVal);
        double error = 0.0;
        double pre_error = 0.0;
        bool enabled = true;
        double dt = 0.0001; // dt -  loop interval time
        double Kd = 0.0; // Kd -  derivative gain
};

pidController::pidController(double min, double max, double Kp, double Ki, double Kd, double dt){
    this->min = min;
    this->max = max;
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->dt = dt;
}

double pidController::speed(double currentVal, double desiredVal){
    error = desiredVal - currentVal;
    double Pout = Kp * error; // Proportional term
    integral += error * dt;
    double Iout = Ki * integral; // Integral term
    double derivative = (error - pre_error) / dt; // Derivative term
    double Dout = Kd * derivative;
    double output = Pout + Iout + Dout;// Calculate total output 
    if(output > max) // Restrict to max/min
        output = max;
    else if(output < min)
        output = min;
    pre_error = error; // Save error to previous error
    dt += 0.001;
    return output; //Speed = (_Kp*error)+(_Ki*error*_dt)+(_Kd*((error-_pre_error)/_dt))
}

//pidController(double min, double max, double Kp, double Ki, double Kd, double dt);
pidController drive(-100.0, 100.0, 0.150, 0.0000000, 0.000, 0.0001);
pidController turn(-100.0, 100.0, 1, 0.00015, 0.01, 0.0001);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


class base{
    private:
      
    public:
      base();
      int leftSpeed;
      int rightSpeed;
      void rightSpin();
      void leftSpin();
        //double speed(double currentVal, double desiredVal);
};

base::base(){
    //this->min = min;
}

void base::rightSpin(){
  if(speed != 0){
      RB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
      RF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
      RB.stop(vex::brakeType::coast);  
      RF.stop(vex::brakeType::coast);  
  }
}

void base::leftSpin(){
    if(speed != 0){
      LB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
      LF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    }else{
      LB.stop(vex::brakeType::coast);  
      LF.stop(vex::brakeType::coast);  
    }
}

void baseStop(){
  LB.stop(vex::brakeType::hold);
  LF.stop(vex::brakeType::hold);
  RB.stop(vex::brakeType::hold);  
  RF.stop(vex::brakeType::hold);  
}

void driveUserControl(int bufferSize = 10, bool stop = false){
  if(baseLockBtn){
    vex::task::sleep(200);
    stop = !stop;
    if(stop==true){
      baseStop();
    }else{
      rightBaseSpin(0);
      leftBaseSpin(0);
    }
  }   
  if(abs(Y_rightJoy)>bufferSize){
    rightBaseSpin(Y_rightJoy);
  }else{
    rightBaseSpin(0);
  }  
  if(abs(Y_leftJoy)>bufferSize){
    leftBaseSpin(Y_leftJoy);
  }else{ 
    leftBaseSpin(0);
  }     
}

void tiltSpin(int speed){
  tilt1.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);   
  tilt2.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);  
}
void tiltStop(bool type){
  if(type){
      tilt1.stop(vex::brakeType::coast);  
      tilt2.stop(vex::brakeType::coast);            
    }else{
      tilt1.stop(vex::brakeType::hold);   
      tilt2.stop(vex::brakeType::hold);             
    }  
}

void tiltUserControl(int inSpeed = -100, int outSpeed = 100, int slowSpeed = 20){
  if(tiltInBtn && tiltOutBtn){
    tiltSpin(slowSpeed);                      
  }else if(tiltInBtn){ 
    tiltSpin(inSpeed);  
  }else if(tiltOutBtn){
    tiltSpin(outSpeed);  
  }else{
    if(tilt1.rotation(vex::rotationUnits::deg)<=75){
      tiltStop(1);        
    }else{
      tiltStop(0);           
    }     
  }
}

void intakeSpin(int speed){
  leftIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  rightIntake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}
void intakeStop(){
  leftIntake.stop(vex::brakeType::brake);  
  rightIntake.stop(vex::brakeType::brake);  
}

void intakeUserControl(int inSpeed = 100, int outSpeed = -100, int slowSpeed = 25){
  if(intakeBtn && outtakeBtn){
    intakeSpin(slowSpeed);
  }else if(intakeBtn){ 
    intakeSpin(inSpeed);
  }else if(outtakeBtn){ 
    intakeSpin(outSpeed);
  }else{
    intakeStop();
  }
}

void buttonReset(){
  if(Bumper.pressing()==1){
    tilt1.resetRotation();
  }
}

void autoScore(){
  //intakeSpin(100);
  leftIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::rpm);
  rightIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::rpm);
  RB.spin(vex::directionType::rev, 60, vex::velocityUnits::rpm);
  RF.spin(vex::directionType::rev, 60, vex::velocityUnits::rpm);
  LB.spin(vex::directionType::rev, 60, vex::velocityUnits::rpm);
  LF.spin(vex::directionType::rev, 60, vex::velocityUnits::rpm);
  tilt1.spin(vex::directionType::rev, 120, vex::velocityUnits::rpm);
  tilt2.spin(vex::directionType::rev, 120, vex::velocityUnits::rpm);    
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void turnPID(double angle){
    Gyro.startCalibration();
    while(Gyro.isCalibrating())
        vex::task::sleep(1); 
    vex::task::sleep(1000);    
    turn.dt=0.0001;
    double speed = turn.speed(Gyro.value(vex::rotationUnits::deg),angle);
    turn.pre_error = angle - Gyro.value(vex::rotationUnits::deg);
    turn.error = turn.pre_error;
    int timesGood = 0;
    bool moveComplete = false;
    while(!moveComplete && turn.enabled){
        if(angle>0){
            speed = turn.speed(Gyro.value(vex::rotationUnits::deg),angle);
            rightBaseSpin(-speed);
            leftBaseSpin(speed);
        }
        else{
            speed = turn.speed(-Gyro.value(vex::rotationUnits::deg),-angle);
            rightBaseSpin(speed);
            leftBaseSpin(-speed);
        }
        if(fabs(turn.error)<=3)
            timesGood++;
        if(timesGood >= 100)
            moveComplete = true;
        vex:: task:: sleep(1);
    }
    LF.stop(vex::brakeType::brake);
    RB.stop(vex::brakeType::brake);
    LB.stop(vex::brakeType::brake);
    RF.stop(vex::brakeType::brake);
    vex:: task:: sleep(10);
}

double distanceToTravel(double inchesGiven){
    int wheelRadIN = 2;
    float floatDiv = (float)95.0/36.0;
    double distance = (inchesGiven/(2*M_PI*wheelRadIN))*(360*floatDiv);
    return distance; //Distance in ticks    
}
    
void drivePID(double distance){
    distance = distanceToTravel(distance);
    rightEncoder.resetRotation(); 
    leftEncoder.resetRotation();
    vex::task::sleep(100); 
    drive.dt=0.0001;
    double encoderDeg = (rightEncoder.rotation(vex::rotationUnits::deg) + leftEncoder.rotation(vex::rotationUnits::deg))/2;
    double speed = drive.speed(encoderDeg,distance);
    drive.pre_error = distance - encoderDeg;
    drive.error = drive.pre_error;
    int timesGood = 0;
    bool moveComplete = false;
    while(!moveComplete && drive.enabled){ 
        encoderDeg = (rightEncoder.rotation(vex::rotationUnits::deg) + leftEncoder.rotation(vex::rotationUnits::deg))/2;
        speed = drive.speed(encoderDeg,distance);
        rightBaseSpin(speed);
        leftBaseSpin(speed);
        if(fabs(drive.error)<=40)
            timesGood++;
        if(timesGood >= 100)
            moveComplete = true;
        vex:: task:: sleep(1);
    }
    LF.stop(vex::brakeType::brake);
    RB.stop(vex::brakeType::brake);
    LB.stop(vex::brakeType::brake);
    RF.stop(vex::brakeType::brake);
    vex:: task:: sleep(10);
}

enum directiontype {forwards, backwards};
void driveInches(directiontype mydirection, double travelTargetIN, int speed)
{
  double circumference = wheelDiameterIN * M_PI;
  double degreesToRotate = (360 * travelTargetIN) / circumference;
  if(mydirection == forwards)
  {
    
    LB.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
    RF.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    LF.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    RB.rotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct); 
  }
  else if(mydirection == backwards)
  {
     degreesToRotate = degreesToRotate*-1;
    LB.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
    LF.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    RF.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    RB.rotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct); 
  }
}

enum turningtype {right, left};
void turnDegrees(turningtype mydirection, double travelTargetDEG, int speed)
{
  double baseCircumference = baseDiameterIN * M_PI; //51.81
  double degreesToRotate = ((360 * travelTargetDEG) / baseCircumference)/2; // 32,400
  if(mydirection == right)
  {
    
    LB.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
    LF.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    RF.startRotateFor(degreesToRotate*-1,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    RB.rotateFor(degreesToRotate*-1,vex::rotationUnits::deg,speed,vex::velocityUnits::pct); 
  }
  else if(mydirection == left)
  {

    LB.startRotateFor(degreesToRotate*-1,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
    LF.startRotateFor(degreesToRotate*-1,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    RF.startRotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);  
    RB.rotateFor(degreesToRotate,vex::rotationUnits::deg,speed,vex::velocityUnits::pct); 
  }
}

enum tiltType {extend, retract};
void moveTitl(tiltType mydirection, int speed=0, int timeOut=2){
  if(mydirection == extend){
    tilt1.setTimeout(timeOut,vex::timeUnits::sec);
    tilt1.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
    tilt2.spin(vex::directionType::rev,speed,vex::velocityUnits::rpm);    
  }
  else if(mydirection == retract){
    tilt1.setTimeout(timeOut,vex::timeUnits::sec);
    tilt1.spin(vex::directionType::rev,speed,vex::velocityUnits::rpm);
    tilt2.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
  }
  else{
    tilt1.stop(vex::brakeType::hold);
    tilt2.stop(vex::brakeType::hold);
  }
}

void turnonbase(int power,bool fwd) {
  if(fwd){
    RF.spin(vex::directionType::fwd,power,vex::velocityUnits ::rpm) ;
    RB.spin(vex::directionType::fwd,power,vex::velocityUnits ::rpm) ;
    LF.spin(vex::directionType::fwd,power,vex::velocityUnits ::rpm) ;
    LB.spin(vex::directionType::fwd,power,vex::velocityUnits ::rpm) ;
  }
else{
    RF.spin(vex::directionType::rev,power,vex::velocityUnits ::rpm) ;
    RB.spin(vex::directionType::rev,power,vex::velocityUnits ::rpm) ;
    LF.spin(vex::directionType::rev,power,vex::velocityUnits ::rpm) ;
    LB.spin(vex::directionType::rev,power,vex::velocityUnits ::rpm) ;
  }
}
void basetobrake() {
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);

}

void drivefwd_pid(int speed,int distance ){
  LF.resetRotation() ;
  double i=0;
  //turn on base at the rquested speed.
    turnonbase(speed,true) ;
    while(LF.rotation(vex::rotationUnits::deg)<distance ){
      vex::task::sleep(1) ;
      if(LF.rotation(vex::rotationUnits::deg)>(distance*i) && LF.rotation(vex::rotationUnits::deg)>(distance*.70) && LF.rotation(vex::rotationUnits::deg)<(distance*.90) ) {
        turnonbase(speed*(1-i),true);
    }
    i=1/(leftEncoder.rotation(vex::rotationUnits::deg)) ;
  }
  basetobrake() ;
}
void drivefwd_nopid(int speed,int distance) {
  LF.resetRotation() ;
  //reset the encoder
  turnonbase(speed,true) //turn on drive train.
  while(LF.rotation(vex::rotationUnits::deg)<distance){
    vex::task::sleep(1);
  }
  basetobrake() ; //stop moving base motors and turn them to brake.
  }

void reversedrive(int speed,int distance){
  LF.resetRotation() ;
  turnonbase(speed,false) ;
  while((LF.rotation(vex::rotationUnits::deg)*-1)<distance){
    vex::task::sleep(1);
  }
    basetobrake() ;
  }
void turn_(double degree,bool leftturn,int sp){
       int x =Gyro.value(vex::rotationUnits::deg );
       if(leftturn){
         RF.spin(vex::directionType::fwd,sp,vex::velocityUnits ::rpm) ;
      RB.spin(vex::directionType::fwd,sp,vex::velocityUnits ::rpm) ;
      LF.spin(vex::directionType::rev,sp,vex::velocityUnits ::rpm) ;
    LB.spin(vex::directionType::rev,sp,vex::velocityUnits ::rpm) ;
        while((Gyro.value(vex::rotationUnits::deg)> x-degree)){
          vex::task::sleep(1);
        }
       }
       else{
         RF.spin(vex::directionType::rev,sp,vex::velocityUnits ::rpm) ;
      RB.spin(vex::directionType::rev,sp,vex::velocityUnits ::rpm) ;
      LF.spin(vex::directionType::fwd,sp,vex::velocityUnits ::rpm) ;
    LB.spin(vex::directionType::fwd,sp,vex::velocityUnits ::rpm) ;
         //for rightturn
         while(Gyro.value(vex::rotationUnits::deg)<x+degree){
           vex::task::sleep(1);
         }

       }
       basetobrake() ;
}
void outake(int distance ){
  //first reset encoder for outaking.
  rightIntake.resetRotation() ;
  leftIntake.spin(vex::directionType::rev, 70, vex::velocityUnits::pct);
  rightIntake.spin(vex::directionType::rev, 70, vex::velocityUnits::pct);
  while((rightIntake.rotation(vex::rotationUnits::deg)*-1)<distance) {
    vex::task::sleep(1) ;
  }
  leftIntake.stop(vex::brakeType::hold);
   rightIntake.stop(vex::brakeType::hold) ;
}
void deployslide(int speed,int distance ) {
  tilt1.resetRotation() ;
  tilt1.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
  tilt2.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);    
  
  while(tilt1.rotation(vex::rotationUnits::deg)<distance ){
    vex::task::sleep(1) ;
  }
  tilt1.stop(vex::brakeType::coast);
  tilt2.stop(vex::brakeType::coast);
  tilt2.resetRotation() ;
  tilt1.spin(vex::directionType::rev,speed,vex::velocityUnits::pct);
  tilt2.spin(vex::directionType::rev,speed,vex::velocityUnits::pct);
  while(!(Bumper.pressing())) 
  vex::task::sleep(1) ;
  tilt1.stop(vex::brakeType::coast);
  tilt2.stop(vex::brakeType::coast);
  turnonbase(40,false) ;
  vex::task::sleep(500) ;
}
void score(){
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
  vex::task::sleep(1500) ;
  autoScore() ;
  vex::task::sleep(2000) ;
}

void blueAuton(){
  //first part is to calibrate gyro for turning
  Gyro.startCalibration();
  while(Gyro.isCalibrating())
        vex::task::sleep(1); 
    
    //after calibration turn slide on.
  deployslide(90,430) ;
  //after the slide deploys reverse back into the wall to align cubes.and drive train.
  
  
  //turn on the intake motors to prepare scoring cubes
  leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  drivefwd_nopid(85,1520) ;//first paremeter is speed next parameter is distance.
  vex::task::sleep(1000) ; 
  //made to get the green cube to the right of things.
  reversedrive(100,400) ;
  turn_(8.5,false,80) ; //this will turn robot toe right using the gyro sensor.
  vex::task::sleep(100) ;
  drivefwd_nopid(120,420) ;
  vex::task::sleep(300) ;
  
  //turn intake motors to hold.
  reversed
  
  rive(180,670) ; //reverse back to the goal
  turn_(165,true,50) ;
  
  vex::task::sleep(50) ; //sleep system after turn for better accuracy
  drivefwd_nopid(160,370) ; //driveto the goal
  outake(300); ///get the last cube to the bottom to score all the cubes.
  score() ;//use the score function when cubes are ready to be delivered.
}

void redAuton(){
  //first part is to calibrate gyro for turning
  Gyro.startCalibration();
  while(Gyro.isCalibrating())
        vex::task::sleep(1); 
    
    //after calibration turn slide on.
  deployslide(90,430) ;
  //after the slide deploys reverse back into the wall to align cubes.and drive train.
  turn_(0.5,true,5) ;
  
  //turn on the intake motors to prepare scoring cubes
  leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  drivefwd_nopid(85,1520) ;
  vex::task::sleep(1000) ; 
  //made to get the green cube to the right of things.
  reversedrive(100,400) ;
  turn_(9,true,80) ; //this will turn robot toe right using the gyro sensor.
  vex::task::sleep(100) ;
  drivefwd_nopid(120,350) ;
  vex::task::sleep(300) ;
  
  //turn intake motors to hold.
  reversedrive(180,650) ; //reverse back to the goal
  turn_(164.5,false,50) ;
  
  vex::task::sleep(50) ; //sleep system after turn for better accuracy
  drivefwd_nopid(160,385) ; //driveto the goal
  outake(300); ///get the last cube to the bottom to score all the cubes.
  score() ;//use the score function when cubes are ready to be delivered.
}