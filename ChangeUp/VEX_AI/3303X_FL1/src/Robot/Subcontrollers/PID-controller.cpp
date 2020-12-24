/*---PID_CONTROLLER_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       PID-controller.cpp                                        */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "Robot/Subcontrollers/PID-Controller.h"


void PID_Controller::pidDriveLoop(int setpoint){
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

    LeftDrive.spin(fwd,speed,pct);
    RB.spin(fwd,speed,pct);
    LF.spin(fwd,speed,pct);
    RF.spin(fwd,speed,pct);

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
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

void PID_Controller::pidDriveBackLoop(int setpoint){
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
  LB.stop(vex::brakeType::brake);
  RF.stop(vex::brakeType::brake);
}

// void PID_Controller::pidTurnRightLoop(int setpoint){//thanks geroge :D
//   bool moveComplete = false;
//   int timesGood = 0;
//   integral = 0;
//   derivative = 0;
//   prevError = 0;
//   while(!moveComplete && baseInetrial<=setpoint){
//     error = setpoint-baseInetrial;
//     integral = integral +error;
//     if(error<=0 || baseInetrial>setpoint){
//       integral=0;
//     }
//     if(error > setpoint){
//       integral = 0;
//     }
//     derivative=error-prevError;
//     prevError = error;
//     speed=error*turnKp + integral*turnKi + derivative*turnKd;
//     vex::task::sleep(4);

//     LB.spin(fwd,speed,pct);
//     RB.spin(fwd,-speed,pct);
//     LF.spin(fwd,speed,pct);
//     RF.spin(fwd,-speed,pct);

//     if(error<=100){ 
//       timesGood++;
//     }
//     if(timesGood >= 100){
//       moveComplete = true;
//     }
//     task::sleep(1); 
//   }
//   LF.stop(vex::brakeType::brake);
//   RB.stop(vex::brakeType::brake);
//   LB.stop(vex::brakeType::brake);
//   RF.stop(vex::brakeType::brake);
// }

// void PID_Controller::pidTurnLeftLoop(int setpoint){//thanks geroge :D
//   bool moveComplete = false;
//   int timesGood = 0;
//   integral = 0;
//   derivative = 0;
//   prevError = 0;
//   while(!moveComplete && baseInetrial<=setpoint){
//     error = setpoint+baseInetrial;
//     integral = integral +error;
//     if(error<=0 || baseInetrial>setpoint){
//       integral=0;
//     }
//     if(error > setpoint){
//       integral = 0;
//     }
//     derivative=error-prevError;
//     prevError = error;
//     speed=error*turnKp + integral*turnKi + derivative*turnKd;
//     vex::task::sleep(4);

//     LB.spin(fwd,-speed,pct);
//     RB.spin(fwd,speed,pct);
//     LF.spin(fwd,-speed,pct);
//     RF.spin(fwd,speed,pct);

//     if(error<=100){ 
//       timesGood++;
//     }
//     if(timesGood >= 100){
//       moveComplete = true;
//     }
//     task::sleep(1); 
//   }
//   LF.stop(vex::brakeType::brake);
//   RB.stop(vex::brakeType::brake);
//   LB.stop(vex::brakeType::brake);
//   RF.stop(vex::brakeType::brake);
// }


//PID_Controller(double min, double max, double Kp, double Ki, double Kd, double dt);
// PID_Controller drive(-100.0, 100.0, 0.070, 0.0000600, 0.060, 0.0001);   LAST YEAR BOT
// PID_Controller turn(-100.0, 100.0, 0.750, 0.0000080, 0.200, 0.0001);    LAST YEAR BOT

//PID_Controller drive(-100.0, 100.0, 0.060, 0.0000300, 0.045, 0.0001);
//PID_Controller turn(-100.0, 100.0, 2.500, 0.0000300, 0.050, 0.0001);     //   NEWWWWW

// PID_Controller drive(-100.0, 100.0, 0.07, 0.0003, 0.006, 0);
// PID_Controller turn(-100.0, 100.0, 0.750, 0.0000080, 0.200, 0.0001); LATEST




//PID_Controller drive(-100.0, 100.0, 0.07, 0.000001, 0.081, 0.0001); today test

/*---PID_CONTROLLER_CPP---*/