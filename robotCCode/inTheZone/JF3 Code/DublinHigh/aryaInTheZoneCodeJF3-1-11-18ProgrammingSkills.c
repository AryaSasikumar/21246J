#pragma config(Sensor, in1,    baseGyro,       sensorGyro)
#pragma config(Sensor, in3,    mogoPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    gyro,           sensorGyro)
#pragma config(Sensor, in5,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in6,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, in7,    vbPot,          sensorPotentiometer)
#pragma config(Sensor, in8,    navPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  towerPing,      sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl12, button,         sensorTouch)
#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port3,           rightFrontBase, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftFrontBase, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftBackBase,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightBackBase, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mobile,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          elevator,      tmotorVex393_HBridge, openLoop)
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

//Default AUTON Number//
// RED  POLE     == 0 //
// RED  RIGHT1   == 1 //
// RED  LEFT1    == 2 //
// Defence     == 3 //
// BLUE RIGHT1   == 4 //
// BLUE LEFT1    == 5 //
// SKILLS        == 6 //
// BLUE RIGHT2   == 7  v         //
// RED  RIGHT2   == 8 //
// Resistance Block    == 9 //
// RED  LEFT2    == 10//
int autonNum = 3;
//Default AUTON Number//

void Kill()//Kills power
{
	motor[intake] = 0;
	motor[rightFrontBase] = 0;
	motor[leftFrontBase] = 0;
	motor[rightLift] = 0;
	motor[leftLift] = 0;
	motor[leftBackBase] = 0;
	motor[rightBackBase] = 0;
	motor[mobile] = 0;
	motor[elevator] = 0;
}

//-----MOTOR_CONNECTION_FUNCTIONS-----//
void leftBase(int power)//Function used to control all the motors on the left side of the base at once.
{
	motor[leftFrontBase] = power;
	motor[leftBackBase] = power;
}

void rightBase(int power)//Function used to control all the motors on the right side of the base at once.
{
	motor[rightFrontBase] = power;
	motor[rightBackBase] = power;
}

void baseDriver(int leftSpeed, int rightSpeed)//Function to control base during driver control
{
	leftBase(leftSpeed);
	rightBase(rightSpeed);
}
void base(int rSpeed, int lSpeed){
	baseDriver(lSpeed, rSpeed);}

void liftControl(int power)//Function used to control all the motors on the lift at once.
{
	motor[rightLift] = power;
	motor[leftLift] = power;
}





//-----MOTOR_CONNECTION_FUNCTIONS-----//




//********************************************************************************************************//
//********************************************AUTON_FUNCTIONS*********************************************//
//********************************************************************************************************//

void clearEncoders()
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
}

void fwds(int distance, int speed, int brake, int wait, int timer)
{
	clearTimer(T2);
	clearEncoders();
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

void turnRight(int distance, int speed, int brake, int wait)
{
	SensorValue[baseGyro] = 0;
	//RIGHT
	while(abs(SensorValue[baseGyro]) <= distance)
	{
		base((-speed),(speed));
	}
	if(brake != 0)
	{
		base(brake,-brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}

void turnLeft(int distance, int speed, int brake, int wait)
{
	SensorValue[baseGyro] = 0;
	//LEFT
	while(abs(SensorValue[baseGyro]) <= distance)
	{
		base((speed),(-speed));
	}
	if(brake != 0)
	{
		base(-brake,brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}

void turnRightEncoder(int distance, int speed, int brake, int wait)
{
	SensorValue[rightEncoder] = 0;
	//RIGHT
	while(abs(SensorValue[rightEncoder]) <= distance)
	{
		base((-speed),(speed));
	}
	if(brake != 0)
	{
		base(brake,-brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}

void turnLeftEncoder(int distance, int speed, int brake, int wait)
{
	SensorValue[rightEncoder] = 0;
	//LEFT
	while(abs(SensorValue[rightEncoder]) <= distance)
	{
		base((speed),(-speed));
	}
	if(brake != 0)
	{
		base(-brake,brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}


void clawOpen(int potValue, int speed, int hold)
{
	clearTimer(T3);
	while(SensorValue[clawPot] >= potValue && time1[T3] < 2000)
	{
		motor[intake] = speed;
	}
	motor[intake] = hold;
}

void clawClose(int potValue, int speed, int hold)
{
	clearTimer(T3);
	while(SensorValue[clawPot] <= potValue && time1[T3] < 2000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
	{
		motor[intake] = -speed;
	}
	motor[intake] = -hold;
}

void liftUp(int potValue, int speed, int hold, int waitTime, int timer)
{
	clearTimer(T2);
	while(SensorValue[liftPot] >= potValue && time1[T2] < timer)
	{
		liftControl(-speed);
	}
	liftControl(hold);
	wait1Msec(waitTime);
}

void liftDown(int potValue, int speed, int hold, int waitTime, int timer)
{
	clearTimer(T2);
	while(SensorValue[liftPot] <= potValue && time1[T2] < timer)
	{
		liftControl(-speed);
	}
	liftControl(hold);
	wait1Msec(waitTime);
}

void mogoOut(int potValue, int speed, int hold)
{
	clearTimer(T2);
	while(SensorValue[mogoPot] <= potValue && time1[T2] < 3000)
	{
		motor[mobile] = speed;
	}
	motor[mobile] = 0;//change to hold if needed
}

void mogoIn(int potValue, int speed, int hold)
{
	clearTimer(T2);
	while(SensorValue[mogoPot] >= potValue && time1[T2] < 3000)
	{
		motor[mobile] = -speed;
	}
	motor[mobile] = 0;//change to hold if needed
}

void vbUp(int potValue, int speed, int hold)
{
	while(SensorValue[vbPot] >= potValue)
	{
		motor[elevator] = (speed);
	}
	motor[elevator] = 0;
}

void vbDown(int potValue, int speed, int hold)
{
	while(SensorValue[vbPot] <= potValue)
	{
		motor[elevator] = (-speed);
	}
	motor[elevator] = hold;
}

void autonRun();
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------Pre-Autonomous Functions----------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void pre_auton()
{
	SensorValue[gyro] = 0;
	SensorValue[baseGyro] = 0;
	clearEncoders();
	clearTimer(T1);
}
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                           */
/*                                                              Autonomous Task                                                              */
/*                                                                                                                                           */
/*-------------------------------------------------------------------------------------------------------------------------------------------*/


// RED  POLE     == 0 //
// RED  RIGHT1   == 1 //
// RED  LEFT1    == 2 //
// BLUE POLE     == 3 //
// BLUE RIGHT1   == 4 //
// BLUE LEFT1    == 5 //
// SKILLS        == 6 //
// BLUE RIGHT2   == 7 //
// RED  RIGHT2   == 8 //
// BLUE LEFT2    == 9 //
// RED  LEFT2    == 10//

task autonomous()
{
	autonRun();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
task usercontrol()
{
}

void autonRun()
{
	if(autonNum == 6)//---SKILLS---//
	{
		clawClose(3100, -127, -10);//(potValue, speed, hold)
		vbUp(400, 127, 10);
		liftUp(1100, -127, 15, 250, 3000);
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(1000, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		bwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeftEncoder(300, 127, 10, 150);//(distance, speed, brake, wait)
		fwds(300, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeftEncoder(300, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1200, -127, 10, 250, 1000);
		mogoOut(2300, -127, 0);//(potValue, speed, hold)

		liftDown(1100, 127, 10, 250, 1000);
		vbUp(400, 127, 15);
		bwds(100, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		bwds(300, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRightEncoder(320, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(260, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRightEncoder(300, 127, 10, 100);//(distance, speed, brake, wait) //Face second
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1200, -127, 10, 250, 1000);
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		turnRightEncoder(670, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(800, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		bwds(400, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1200, -127, 10, 250, 1000);
		mogoIn(170, -127, 0);//(potValue, speed, hold)//obtain second goal
		turnRightEncoder(700, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(850, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		fwds(1100, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(700, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeft(700, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		bwds(400, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(700, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(400, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(700, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(800, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		turnRight(1600, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
	}
}
