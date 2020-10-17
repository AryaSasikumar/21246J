#include "vex.h"
/*---------------------------------------------------------------------------*/
/*                            PID Functions                                  */
/*---------------------------------------------------------------------------*/

class pidController{
    private:

    public:
        double Kp = 0.0675;                        //Ku = 0.245        0.245*0.6 = Kp = 0.147         Ki= 1.2*0.245/0.675=0.435     Kd= 0.075*0.245*0.675=0.0124
        double Ki = 0.0005;//0.0006   /0.000003    pU=0.675 seconds
        double Kd = 0.3;//0.0004    //0.001
        double turnKp = 0.7;
        double turnKi = 0.0005;
        double turnKd = 0.3;
        int Dt=15;
        double error;
        double speed;
        double integral;
        double derivative;
        double prevError;
        void pidDriveLoop(int setpoint);
        void pidDriveBackLoop(int setpoint);
        void pidTurnRightLoop(int setpoint);
        void pidTurnLeftLoop(int setpoint);
        bool pidRun;
};

void pidController::pidDriveLoop(int setpoint){
  mainBaseLeftEncReset;
  mainBaseRightEncReset;
  bool moveComplete = false;
  int timesGood = 0;
  integral = 0;
  derivative = 0;
  prevError = 0;
  while(!moveComplete && mainBaseEnc<=setpoint){
    error = setpoint-mainBaseEnc;
    integral = integral +error;
    if(error<=0 || mainBaseEnc>setpoint){
      integral=0;
    }
    if(error > setpoint){
      integral = 0;
    }
    derivative=error-prevError;
    prevError = error;
    speed=error*Kp + integral*Ki + derivative*Kd;
    vex::task::sleep(Dt);

    LB.spin(fwd,speed,pct);
    RB.spin(fwd,speed,pct);
    LF.spin(fwd,speed,pct);
    RF.spin(fwd,speed,pct);
    LT.spin(fwd,speed,pct);
    RT.spin(fwd,speed,pct);

    if(error<=100){ 
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    task::sleep(1); 
  }
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LT.stop(vex::brakeType::brake);
  RT.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

void pidController::pidDriveBackLoop(int setpoint){
  mainBaseLeftEncReset;
  mainBaseRightEncReset;
  bool moveComplete = false;
  int timesGood = 0;
  integral = 0;
  derivative = 0;
  prevError = 0;
  while(!moveComplete && mainBaseEnc<=setpoint){
    error = setpoint+mainBaseEnc;
    integral = integral +error;
    if(error<=0 || mainBaseEnc>setpoint){
      integral=0;
    }
    if(error > setpoint){
      integral = 0;
    }
    derivative=error-prevError;
    prevError = error;
    speed=error*Kp + integral*Ki + derivative*Kd;
    vex::task::sleep(Dt);

    LB.spin(fwd,-speed,pct);
    RB.spin(fwd,-speed,pct);
    LF.spin(fwd,-speed,pct);
    RF.spin(fwd,-speed,pct);
    LT.spin(fwd,-speed,pct);
    RT.spin(fwd,-speed,pct);

    if(error<=100){ 
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    task::sleep(1); 
  }
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LT.stop(vex::brakeType::brake);
  RT.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

void pidController::pidTurnRightLoop(int setpoint){//thanks geroge :D
  baseHeadingReset;
  baseRotationReset;
  bool moveComplete = false;
  int timesGood = 0;
  integral = 0;
  derivative = 0;
  prevError = 0;
  while(!moveComplete && baseInetrial<=setpoint){
    error = setpoint-baseInetrial;
    integral = integral +error;
    if(error<=0 || baseInetrial>setpoint){
      integral=0;
    }
    if(error > setpoint){
      integral = 0;
    }
    derivative=error-prevError;
    prevError = error;
    speed=error*turnKp + integral*turnKi + derivative*turnKd;
    vex::task::sleep(4);

    LB.spin(fwd,speed,pct);
    RB.spin(fwd,-speed,pct);
    LF.spin(fwd,speed,pct);
    RF.spin(fwd,-speed,pct);
    LT.spin(fwd,speed,pct);
    RT.spin(fwd,-speed,pct);

    if(error<=100){ 
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    task::sleep(1); 
  }
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LT.stop(vex::brakeType::brake);
  RT.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

void pidController::pidTurnLeftLoop(int setpoint){//thanks geroge :D
  baseHeadingReset;
  baseRotationReset;
  bool moveComplete = false;
  int timesGood = 0;
  integral = 0;
  derivative = 0;
  prevError = 0;
  while(!moveComplete && baseInetrial<=setpoint){
    error = setpoint+baseInetrial;
    integral = integral +error;
    if(error<=0 || baseInetrial>setpoint){
      integral=0;
    }
    if(error > setpoint){
      integral = 0;
    }
    derivative=error-prevError;
    prevError = error;
    speed=error*turnKp + integral*turnKi + derivative*turnKd;
    vex::task::sleep(4);

    LB.spin(fwd,-speed,pct);
    RB.spin(fwd,speed,pct);
    LF.spin(fwd,-speed,pct);
    RF.spin(fwd,speed,pct);
    LT.spin(fwd,-speed,pct);
    RT.spin(fwd,speed,pct);

    if(error<=100){ 
      timesGood++;
    }
    if(timesGood >= 100){
      moveComplete = true;
    }
    task::sleep(1); 
  }
  LF.stop(vex::brakeType::brake);
  RB.stop(vex::brakeType::brake);
  LT.stop(vex::brakeType::brake);
  RT.stop(vex::brakeType::brake);
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

pidController myPID;

//pidController(double min, double max, double Kp, double Ki, double Kd, double dt);
// pidController drive(-100.0, 100.0, 0.070, 0.0000600, 0.060, 0.0001);   LAST YEAR BOT
// pidController turn(-100.0, 100.0, 0.750, 0.0000080, 0.200, 0.0001);    LAST YEAR BOT

//pidController drive(-100.0, 100.0, 0.060, 0.0000300, 0.045, 0.0001);
//pidController turn(-100.0, 100.0, 2.500, 0.0000300, 0.050, 0.0001);     //   NEWWWWW

// pidController drive(-100.0, 100.0, 0.07, 0.0003, 0.006, 0);
// pidController turn(-100.0, 100.0, 0.750, 0.0000080, 0.200, 0.0001); LATEST




//pidController drive(-100.0, 100.0, 0.07, 0.000001, 0.081, 0.0001); today test