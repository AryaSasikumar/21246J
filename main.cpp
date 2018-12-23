#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;

int flyWheelSpeed = 200;
int rollerSpeed = 100;
int liftSpeed = 100;
int flipperUpSpeed = 100;
int flipperDownSpeed = 40;
bool on = false;
bool driveDir = false; //False = ball forward True = cap forward
int flipperState = 0; //0:Manual 2:up 1:down

///////////////////////////////Drive Control Functions//////////////////////////////

void driveDirTog(){
    if(Controller1.ButtonLeft.pressing())
    {
        vex::task::sleep(200);
        driveDir = !driveDir;
    }
}

void driveControl()
{
    if(driveDir){
        leftBack.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
        leftFront.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
        rightBack.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
        rightFront.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    }
    else{
        leftBack.spin(vex::directionType::rev, Controller1.Axis2.value(), vex::velocityUnits::pct);
        leftFront.spin(vex::directionType::rev, Controller1.Axis2.value(), vex::velocityUnits::pct);
        rightBack.spin(vex::directionType::rev, Controller1.Axis3.value(), vex::velocityUnits::pct);
        rightFront.spin(vex::directionType::rev, Controller1.Axis3.value(), vex::velocityUnits::pct);
    }
    
}

void rollerControl()
{
    if(Controller1.ButtonR1.pressing())
    {
        roller.spin(vex::directionType::fwd, rollerSpeed, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing())
    {
        roller.spin(vex::directionType::rev, rollerSpeed, vex::velocityUnits::pct);
    }
    else
    {
        roller.stop(vex::brakeType::hold);
    }
}

void flyWheelControl()
{
    if(Controller1.ButtonX.pressing())
    {
        vex::task::sleep(200);
        on = !on;
        if(on==true)
        {
            flyWheel.spin(vex::directionType::fwd, flyWheelSpeed, vex::velocityUnits::rpm);
        }
        else
        {
            flyWheel.stop(vex::brakeType::coast);
        }
    }
}

void liftControl()
{
    if(Controller1.ButtonL1.pressing())
    {
        lift.spin(vex::directionType::fwd, liftSpeed, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing())
    {
        lift.spin(vex::directionType::rev, liftSpeed, vex::velocityUnits::pct);
    }
    else
    {
        lift.stop(vex::brakeType::hold);
    }
}

void flipperControl()
{
    if(Controller1.ButtonRight.pressing())
    {
        flipperState=0;
        flipper.spin(vex::directionType::fwd, flipperUpSpeed, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonDown.pressing())
    {
        flipperState=0;
        flipper.spin(vex::directionType::rev, flipperDownSpeed, vex::velocityUnits::pct);
    }
    else
    {
        if(Controller1.ButtonUp.pressing())
        {
            vex::task::sleep(200);
            if(flipperState==1){
                flipper.rotateTo(180,vex::rotationUnits::deg,flipperUpSpeed,vex::velocityUnits::pct);
                flipperState=2;//up
            }
            else{
                
                flipper.rotateTo(0,vex::rotationUnits::deg,flipperDownSpeed,vex::velocityUnits::pct);
                flipperState=1; //down
            }
        }
        flipper.stop(vex::brakeType::hold);
    }
}

///////////////////////////////Drive Control Functions//////////////////////////////

///////////////////////////////Autonomous  Functions//////////////////////////////
/*
 void spinFlyWheel(int speed)
 {
 flyWheel.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
 }
 
 void drive(class direction, int distance, int speed)
 {
 if(direction = forward)
 {
 leftBack.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 leftFront.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightFront.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightBack.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 }
 else if(direction = backward)
 {
 leftBack.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 leftFront.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightFront.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightBack.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 }
 else if(direction = right)
 {
 leftBack.startRotateFor((-speed)),vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 leftFront.startRotateFor((-speed)),vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightFront.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightBack.startRotateFor(speed,vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 }
 else if(direction = left)
 {
 leftBack.startRotateFor(speed),vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 leftFront.startRotateFor(speed),vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightFront.startRotateFor((-speed),vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 rightBack.startRotateFor((-speed),vex::rotationUnits::deg,distance,vex::velocityUnits::pct);
 }
 leftBack.stop(vex::brakeType::coast);
 leftFront.stop(vex::brakeType::coast);
 rightFront.stop(vex::brakeType::coast);
 rightBack.stop(vex::brakeType::coast);
 }
 
 void liftControl(class direction, int distance, int speed)
 {
 if(direction = up)
 {
 
 }
 else if(direction = down)
 {
 
 }
 lift.stop(vex::brakeType::hold);
 }
 
 */


///////////////////////////////Autonomous  Functions//////////////////////////////

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
    // All activities that occur before the competition starts
    // Example: clearing encoders, setting servo positions, ...
    
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

void autonomous( void ) {
    // ..........................................................................
    // Insert autonomous user code here.
    // ..........................................................................
    
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void )
{
    //Use these variables to set the speed of the arm and claw.
    
    while (1)
    {
        driveDirTog();
        driveControl();
        rollerControl();
        flyWheelControl();
        liftControl();
        flipperControl();
        vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
    }
}

int main()
{
    //Run the pre-autonomous function.
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Prevent main from exiting with an infinite loop.
    while(1)
    {
        vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
}
