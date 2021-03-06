#pragma config(Sensor, in1,    elbowPot,       sensorPotentiometer)
#pragma config(Sensor, in2,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, in3,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in8,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl1,  mobileReset,    sensorTouch)
#pragma config(Sensor, dgtl2,  mobileEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  mobileIndicator, sensorLEDtoVCC)
#pragma config(Sensor, dgtl9,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           claw,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightBackBase, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftFrontBase, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           topLeftLift,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mobileGoalIntake, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           bottomLift,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           topRightLift,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           elbow,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightFrontBase, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          leftBackBase,  tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"


int defHold = 0;
int mobileRing = 0;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

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



//********************************************************************************************************//
//********************************************AUTON_FUNCTIONS*********************************************//
//********************************************************************************************************//
//---Base---//:Controls the speed of the base motors.
void base(int rSpeed, int lSpeed)
{
	motor[rightFrontBase] = rSpeed;
	motor[rightBackBase] = rSpeed;
	motor[leftBackBase] = lSpeed;
	motor[leftFrontBase] = lSpeed;
}

//---Turn---//:Turns robot to a given angle at a given speed.
void turn(int distance, int speed, bool direction, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	if(direction == 0)
	{
		while(SensorValue[leftEncoder] <= distance || SensorValue[rightEncoder] <= distance)
		{
			base((-speed),(speed));
		}
		if(brake != 0)
		{
			base(-direction * brake,direction * brake);
			wait1Msec(100);
		}
		base(0,0);
		wait1Msec(wait);
	}
	else
	{
		while(SensorValue[leftEncoder] >= -distance || SensorValue[rightEncoder] >= -distance)
		{
			base((speed),(-speed));
		}
		if(brake != 0)
		{
			base(-direction * brake,direction * brake);
			wait1Msec(100);
		}
		base(0,0);
		wait1Msec(wait);
	}

}



//---Swing---//:Turns using only one side of the base.
void swing(int distance, int speed, int direction, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	if(direction > 0)
	{
		while(direction * SensorValue[rightEncoder] < distance)
		{
			base(direction * speed,-10);
		}
		if(brake != 0)
		{
			base(-brake,0);
			wait1Msec(200);
		}
	}
	else
	{
		while(direction * SensorValue[leftEncoder] < distance)
		{
			base(-10,-direction * speed);
		}
		if(brake != 0)
		{
			base(0,-brake);
			wait1Msec(200);
		}
	}

	base(0,0);
	wait1Msec(wait);
}

void swingB(int distance, int speed, int direction, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	if(direction > 0)
	{
		while(direction * SensorValue[leftEncoder] < distance)
		{
			base(10,-direction * speed);
		}
		if(brake != 0)
		{
			base(0,brake);
			wait1Msec(200);
		}
	}
	else
	{
		while(direction * SensorValue[rightEncoder] <distance)
		{
			base(direction * speed,10);
		}
		if(brake != 0)
		{
			base(brake,0);
			wait1Msec(200);
		}
	}

	base(0,0);
	wait1Msec(wait);
}

//---Forwards/Backwards---//:Moves the base forward and backward using IME's.
void fwds(int distance, int speed, int brake, int wait, int timer)
{
	clearTimer(T2);
	SensorValue[rightEncoder] = 0;
	while(abs(SensorValue[rightEncoder]) < distance && time1[T2] < timer)
	{
		base(speed,speed);
	}
	if(brake != 0)
	{
		base(-brake,-brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}

void bwds(int distance, int speed, int brake, int wait, int timer)
{
	fwds(distance, -speed, brake, wait, timer);
}

void bwdsT(int time, int speed, int wait)
{
	base(-speed,-speed);
	wait1Msec(time);
	base(0,0);
	wait1Msec(wait);
}

void fwdsT(int time, int speed, int wait)
{
	bwdsT(time,-speed,wait);
}

void stopBase()
{
	motor[leftBackBase] = 0;
	motor[leftFrontBase] = 0;
	motor[rightBackBase] = 0;
	motor[rightFrontBase] = 0;
}


task autonomous()
{

	motor[claw]= -25;
	SensorValue[leftEncoder] = 0;
	motor[mobileGoalIntake] = 40;
	wait1Msec(500);
	motor[mobileGoalIntake] = 0;


	while(SensorValue[liftPot] <= 2000)
	{
	motor[bottomLift] = 80;
	motor[topRightLift] = 80;
	motor[topLeftLift] = 80;
	}
	motor[bottomLift] = 10;
	motor[topRightLift] = 10;
	motor[topLeftLift] = 10;


	while(SensorValue[mobileReset] == 0)
	{
	motor[mobileGoalIntake] = -127;
	}
	motor[mobileGoalIntake] = 0;
	SensorValue[mobileEncoder] = 0;
	SensorValue[mobileIndicator] = 1;
	wait1Msec(500);

	fwds(375, 65, 1, 500, 3000);

	while (SensorValue[liftPot] >= 1800)
	{
		motor[bottomLift] = -80;
		motor[topRightLift] = -80;
		motor[topLeftLift] = -80;
	}
	motor[bottomLift] = 15;
	motor[topRightLift] = 15;
	motor[topLeftLift] = 15;

	motor[claw] = 30;
	wait10Msec(1000);
	/*
	while(SensorValue[mobileEncoder] >= -150)
	{
	motor[mobileGoalIntake] = 25;
	}
	motor[mobileGoalIntake] = 0;


	bwds(1000, 90, 10, 500, 3000);
	bwds(350, 110, 10, 500, 3000);

	while(SensorValue[mobileReset] == 0)
	{
	motor[mobileGoalIntake] = -127;
	}
	motor[mobileGoalIntake] = 0;
	wait1Msec(500);

	fwds(925, 80, 10, 500, 3000);
	turn(130, 75, 0, 10, 500);

	fwds(550, 80, 10, 500, 3000);

	turn(180, 75, 0, 10, 500);

	fwds(300, 80, 10, 500, 3000);

	SensorValue[mobileEncoder] = 0;
	while(SensorValue[mobileEncoder] >= -150)
	{
	motor[mobileGoalIntake] = 127;
	}
	motor[mobileGoalIntake] = -15;
	bwds(400, 90, 10, 500, 3000);
	while(SensorValue[mobileEncoder] >= -180)
	{
	motor[mobileGoalIntake] = 127;
	}
	motor[mobileGoalIntake] = 0;
	fwds(30, 80, 10, 500, 2000);

	while(SensorValue[mobileReset] == 0)
	{
	motor[mobileGoalIntake] = -127;
	}
	motor[mobileGoalIntake] = 0;
	fwds(600, 75, 10, 500, 3000);
	*/
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

void base(bool setting, int duration, int speedLeft, int speedRight)//function to control base during auton and driver
{
	if(setting == 0) //Driver Code
	{
		motor[leftBackBase] = vexRT[Ch3];
		motor[leftFrontBase] = vexRT[Ch3];
		motor[rightBackBase] = vexRT[Ch2];
		motor[rightFrontBase] = vexRT[Ch2];
	}
	else
	{
		//Auton Code
		motor[leftBackBase] = speedLeft;
		motor[leftFrontBase] = speedLeft;
		motor[rightBackBase] = speedRight;
		motor[rightFrontBase] = speedRight;
		wait1Msec(duration);
		motor[leftBackBase] = 0;
		motor[leftFrontBase] = 0;
		motor[rightBackBase] = 0;
		motor[rightFrontBase] = 0;
		/*
		while(sensor <= duration)
		{
		motor[leftBackBase] = speedLeft;
		motor[leftFrontBase] = speedLeft;
		motor[rightBackBase] = speedRight;
		motor[rightFrontBase] = speedRight;
		}
		motor[leftBackBase] = 0;
		motor[leftFrontBase] = 0;
		motor[rightBackBase] = 0;
		motor[rightFrontBase] = 0;
		*/
	}
}

void lift(int upSpeed, int downSpeed, int hold)
{
	if(vexRT[Btn5U] == 1 && SensorValue[liftPot] <= 2600)
	{
		motor[bottomLift] = upSpeed;
		motor[topRightLift] = upSpeed;
		motor[topLeftLift] = upSpeed;
	}
	else if(vexRT[Btn5D] == 1 && SensorValue[liftPot] >= 100)
	{
		motor[bottomLift] = downSpeed;
		motor[topRightLift] = downSpeed;
		motor[topLeftLift] = downSpeed;
	}
	else
	{

		if(SensorValue[liftPot] <= 1200)
		{
			motor[bottomLift] = hold-5;
			motor[topRightLift] = hold-5;
			motor[topLeftLift] = hold-5;
		}
		else
		{
			motor[bottomLift] = hold;
			motor[topRightLift] = hold;
			motor[topLeftLift] = hold;
		}
	}
}

void elbowControl(int upSpeed, int downSpeed, int holdUp, int holdDown)
{

	if(vexRT[Btn8U] == 1)
	{
		defHold = 0;
		motor[elbow] = 127;
	}
	else if(vexRT[Btn8D] == 1)
	{
		defHold = 1;
		motor[elbow] = -127;
	}
	else if(vexRT[Btn8L] == 1)
	{
		if(SensorValue[elbowPot] <= 1900)
		{
			defHold = 1;
			clearTimer(T2);
			while(SensorValue[elbowPot] <= 1900&& time1[T2] < 1000)
			{
				motor[elbow] = downSpeed;
			}
		}
		else
		{
			defHold = 1;
			clearTimer(T2);
			while(SensorValue[elbowPot] >= 1900 && time1[T2] < 1000)
			{
				motor[elbow] = upSpeed;
			}
		}
	}
	else if(vexRT[Btn8R] == 1)
	{
		if(SensorValue[elbowPot] <= 950)
		{
			defHold = 0;
			clearTimer(T2);
			while(SensorValue[elbowPot] <= 950 && time1[T2] < 1000)
			{
				motor[elbow] = downSpeed;
			}
		}
		else
		{
			defHold = 0;
			clearTimer(T2);
			while(SensorValue[elbowPot] >= 1000 && time1[T2] < 1000)
			{
				motor[elbow] = upSpeed;
			}
		}
	}
	else
	{
		if(defHold == 1)
		{
			motor[elbow] = holdDown;
		}
		else if(defHold == 0)
		{
			motor[elbow] = holdUp;
		}
	}
}

void clawMove(int openSpeed, int closeSpeed, int hold)
{
	if(vexRT[Btn6U] == vexRT[Btn6D])
	{
		motor[claw] = hold;
	}
	else if(vexRT[Btn6U] == 1 && SensorValue[clawPot] >= 2600)
	{
		motor[claw] = openSpeed;
	}
	else if(vexRT[Btn6D] == 1  && SensorValue[clawPot] <= 3100)
	{
		motor[claw] = closeSpeed;
	}
}

void mobileIn(int upSpeed, int downSpeed, int hold)
{
	if(vexRT[Btn7U] == vexRT[Btn7D])
	{
		motor[mobileGoalIntake] = hold;
	}
	else if(vexRT[Btn7U] == 1)
	{
		motor[mobileGoalIntake] = upSpeed;
	}
	else if(vexRT[Btn7D] == 1 && SensorValue[mobileReset] == 0)
	{
		motor[mobileGoalIntake] = downSpeed;
	}
}

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		base(0,0,0,0); //base(bool setting, int speed, int duration,int side);
		lift(127, -80, 15); //lift(int upSpeed, int downSpeed, int hold);
		elbowControl(90, -40, 20, -10);
		clawMove(127, -127, 10);
		mobileIn(127, -127, -15);
	}
}
