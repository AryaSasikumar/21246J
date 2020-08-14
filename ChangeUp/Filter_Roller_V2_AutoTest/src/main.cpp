/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       aryasasikumar                                             */
/*    Created:      Sun Jul 26 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LF                   motor         1               
// LT                   motor         2               
// LB                   motor         11              
// RF                   motor         10              
// RT                   motor         9               
// RB                   motor         20              
// rightIntake          motor         19              
// leftIntake           motor         12              
// Controller1          controller                    
// colorChecker         line          C               
// Vision5              vision        8               
// leftLineTracker      line          B               
// rightLineTracker     line          A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

vex::task   rTask; // variable to hold filter task instance
//vex::task   bTask; // variable to hold filter task instance

//***---Controller1 Definitions---***//
 
//---Y Definitions---//
#define Y_leftJoy Controller1.Axis3.value()
#define Y_rightJoy Controller1.Axis2.value()
 
//---X Definitions---//
#define X_leftJoy Controller1.Axis4.value()
#define X_rightJoy Controller1.Axis1.value()
 
//---Button Definitions---//
#define macroDriveBtn Controller1.ButtonLeft.pressing()
#define driveToggleBtn Controller1.ButtonA.pressing()
#define slowDriveBackBtn Controller1.ButtonY.pressing()

#define shootBtn Controller1.ButtonR1.pressing() 
#define allUpBtn Controller1.ButtonR2.pressing()
#define filterUpBtn Controller1.ButtonL2.pressing()
#define filterOutBtn Controller1.ButtonUp.pressing()
#define autoSortBtn Controller1.ButtonL1.pressing()
 
#define intakeMacro Controller1.ButtonX.pressing()
 
//---Sensor Definitions---//
#define colorSensor colorChecker.reflectivity();

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
 
const unsigned int halfSpeed[128] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0 , 10, 10, 10, 11, 11, 11, 12, 12, 12,
    13, 13, 13, 13, 13, 13, 14, 14, 14, 14,
    14, 15, 15, 15, 15, 16, 16, 16, 16, 16,
    17, 17, 17, 17, 17, 17, 17, 18, 18, 19,
    19, 19, 19, 19, 19, 20, 20, 20, 20, 20,
    21, 21, 21, 21, 22, 22, 22, 23, 23, 23,
    23, 24, 24, 24, 24, 25, 25, 25, 26, 26,
    26, 27, 27, 27, 28, 29, 29, 29, 30, 30,
    31, 32, 32,32, 33, 33, 34, 34, 34, 35,
    36, 36, 36, 37, 37, 38, 39, 39, 39, 39,
    40, 42, 42, 43, 43, 44, 44, 44, 44, 45,
    45, 45, 48, 48, 48,50,50,50};
 
bool useTrueSpeed = true;
bool toggle = false;

int case_no;
//General Drive Base Functions
void leftSpin(int speed = 0){
 leftSpeed = speed;
 if(leftSpeed != 0){
   LB.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
   LT.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
   LF.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
 }else{
   LB.stop(vex::brakeType::coast); 
   LT.stop(vex::brakeType::coast); 
   LF.stop(vex::brakeType::coast); 
 }
}
 
void rightSpin(int speed = 0){
 rightSpeed = speed;
 if(rightSpeed != 0){
   RB.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
   RT.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
   RF.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
 }else{
   RB.stop(vex::brakeType::coast);
   RT.stop(vex::brakeType::coast); 
   RF.stop(vex::brakeType::coast);
 }
}
 
void Spin(int leftSpeed, int rightSpeed){
 leftSpin(leftSpeed);
 rightSpin(rightSpeed);
}

void userControl(int bufferSize = 5, bool Stop = false){//driveToggleBtn
  if(macroDriveBtn){
    Spin(45, 45);  
  }else if(slowDriveBackBtn){
    Spin(-30, -30);  
  }
  else if(driveToggleBtn){
    toggle=!toggle;
    vex::task::sleep(300);
  }
  else if(Controller1.ButtonX.pressing()){
     Spin(2, 2); 
  }
  else{
    if(toggle==true){
      if(abs(Y_rightJoy)>bufferSize){
        if(Y_rightJoy>0){
          rightSpin(halfSpeed[abs(Y_rightJoy)]);
        }else{
          rightSpin(-halfSpeed[abs(Y_rightJoy)]);
        }
      }else{
        rightSpin(0);
      }
      if(abs(Y_leftJoy)>bufferSize){
        if(Y_leftJoy>0){
          leftSpin(halfSpeed[abs(Y_leftJoy)]);
        }else{
          leftSpin(-halfSpeed[abs(Y_leftJoy)]);
        }
      }else{
        leftSpin(0);
      }
    }
    else {
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
    }
  } 
}
 
//--------------------------AutoSortCode V2--------------------------//
int sort(){
        Brain.Screen.clearLine(1, black);
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("task running");

      case_no = 0;

      Vision5.takeSnapshot(Vision5__BLUEBOX,1);
      if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
        //blue found
        case_no = 1;
      }

      Vision5.takeSnapshot(Vision5__REDBOX,1);
      if (Vision5.largestObject.width > 100 && Vision5.largestObject.width > 100){
        //red found
        case_no = 2;

      if (colorChecker.reflectivity() > 50){
        //red found, top storage taken
        case_no = 3;
      }
    }

  switch(case_no){
    case 1: //blue found
      //filter
      rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
     leftIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
    break;

    case 2: //red found, nothing in top storage
      //intake up, run top roller
      while(colorChecker.reflectivity() < 50){
        rightIntake.spin(directionType::rev, 200, velocityUnits::rpm);
        leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
      }
    break;

    case 3: //red found, top storage taken
      //intake up
      rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
      leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    break;

    default:
      //intake normally
      rightIntake.spin(directionType::fwd, 200, velocityUnits::rpm);
      leftIntake.spin(directionType::rev, 200, velocityUnits::rpm);
    Brain.Screen.clearLine(1, black);
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("default");
  }
 return 0;
}


void ballControl(){
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
   rightIntake.stop(brakeType::coast);
   leftIntake.stop(brakeType::coast);
 }
}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


  //task myTaskRed = task(blueCheck);
  //task myTaskBlue = task(redCheck);

  rTask = vex::task(sort);
  //bTask = vex::task(blueCheck);

  // task rTask(redCheck);
  // task bTask(blueCheck);

   while(1){
    ballControl();
    userControl();
    if(autoSortBtn){
      sort();
    }
    vex::task::sleep(10);
  }  
}

// top sensor stuff

    // if(colorChecker.reflectivity() > 50){
    //   Brain.Screen.clearScreen();
    //   Brain.Screen.setCursor(1, 1);
    //   Brain.Screen.setFont(mono40);
    //   Brain.Screen.print("Ball");
    // }
    // else
    // {
    //   Brain.Screen.clearScreen();
    //   Brain.Screen.setCursor(1, 1);
    //   Brain.Screen.print("no ball");
    // }

// Checking top sensor code

    // Brain.Screen.clearScreen();
    // Brain.Screen.setCursor(1, 1);
    // Brain.Screen.print(leftLineTracker.reflectivity());