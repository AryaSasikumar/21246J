//#include "autonCode_aryaJF3.h"


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

//-----MOTOR_CONNECTION_FUNCTIONS-----//--//DO_NOT_EDIT//----\/----//
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
void base(int leftSpeed, int rightSpeed)//Function to control base during driver control
{
	leftBase(leftSpeed);
	rightBase(rightSpeed);
}
void liftControl(int power)//Function used to control all the motors on the lift at once.
{
	motor[rightLift] = power;
	motor[leftLift] = power;
}
//-----MOTOR_CONNECTION_FUNCTIONS-----//--//DO_NOT_EDIT//----/\----//

void tipWarning()
{
	while(SensorValue[gyro] <= -140 && SensorValue[liftPot] < 1200)
	{
		playSound(soundBeepBeep);
		wait1Msec(100);
		base(127, 127);
		liftControl(-127);
		if(vexRT[Btn7R] == 1)
		{
			SensorValue[gyro] = 0;
		}
	}
	while(SensorValue[gyro] >= 80 && SensorValue[liftPot] < 1200)
	{
		playSound(soundBeepBeep);
		wait1Msec(100);
		base(-127, -127);
		liftControl(-127);
		if(vexRT[Btn7R] == 1)
		{
			SensorValue[gyro] = 0;
		}
	}

	if(time1[T1] >= 5000)
	{
		SensorValue[gyro] = 0;
		clearTimer(T1);
	}
	if(vexRT[Btn7R] == 1)
	{
		SensorValue[gyro] = 0;
	}
}

void intakeClaw(int speed, int hold)
{
	if(vexRT[Btn6U] == 1 && vexRT[Btn6D] == 1)
	{
		motor[intake] = 0;
	}
	else if(vexRT[Btn6D] == 1)
	{
		motor[intake] = speed;
	}
	else if(vexRT[Btn6U] == 1)
	{
		motor[intake] = -speed;
	}
	else
	{
		if(SensorValue[clawPot] <= 2050)
		{
			motor[intake] = 20;
		}
		else
		{
			motor[intake] = 0;
		}
	}
}

int liftVal;
void liftUserControl(int speed, int hold)
{
	if(vexRT[Btn5U] == 1)
	{
		liftControl(speed);
	}
	else if(vexRT[Btn5D] == 1)
	{
		liftControl(-speed);
	}
	else if(vexRT[Btn7U] == 1 || vexRT[Btn7D] == 1)
	{

	}
	else if(vexRT[Btn7L] == 1)
	{
		while(SensorValue[liftPot] <= 1300)
		{
			liftControl(-speed);
		}
		while(SensorValue[liftPot] >= 1500)
		{
			liftControl(speed);
		}
		liftControl(hold);
	}

	else if(vexRT[Btn7R] == 1)
	{
		clearTimer(T3);
		while(SensorValue[clawPot] <= 3100 && time1[T3] < 2000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
		{
			motor[intake] = 127;
		}
		motor[intake] = 20;
		clearTimer(T3);
		while(SensorValue[towerPing] <= 20 && SensorValue[liftPot] >= 5 && time1[T3] < 5000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
		{
			liftControl(110);
		}
		liftVal = SensorValue[liftPot];
		liftControl(hold+20);
		clearTimer(T3);
		while(SensorValue[vbPot] >= 400 && time1[T3] < 2000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
		{
			motor[elevator] = 127;
		}
		motor[elevator] = 30;
		wait1Msec(150);
		clearTimer(T3);
		while(SensorValue[liftPot] <= (liftVal+200) && time1[T3] < 2000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
		{
			liftControl(-60);
		}
		liftControl(hold+30);
		wait1Msec(250);
		clearTimer(T3);
		while(SensorValue[clawPot] >= 2575 && time1[T3] < 2000)
		{
			motor[intake] = -127;
		}
		motor[intake] = -15;
		wait1Msec(100);
		clearTimer(T3);
		while(SensorValue[liftPot] >= (liftVal-200) && time1[T3] < 2000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
		{
			liftControl(110);
		}
		liftControl(hold);
		wait1Msec(200);
		clearTimer(T3);
		while(SensorValue[vbPot] <= 1700 && time1[T3] < 2000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
		{
			motor[elevator] = -127;
		}
		motor[elevator] = 20;
		wait1Msec(50);
		clearTimer(T3);
		while(SensorValue[liftPot] <= 1250 && time1[T3] < 2000 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
		{
			liftControl(-90);
		}
		liftControl(hold+10);
	}
	else
	{
		if(SensorValue[liftPot] >= 1500)
		{
			liftControl(0);
		}
		else
		{
			liftControl(hold);
		}
	}
}


void vbUserControl(int speed, int hold)
{
		if(vexRT[Btn8D] == 1)
		{
			motor[elevator] = -speed;
		}
		else if(vexRT[Btn8U] == 1)
		{
			motor[elevator] = speed;
		}
		else if(vexRT[Btn8R]) //DOWN
		{
			int timer = 2000;
			clearTimer(T3);
			if(SensorValue[vbPot] <= 350 || SensorValue[vbPot] <= 1400)
			{
				while(SensorValue[vbPot] <= 1400 && time1[T3] < timer)
				{
					motor[elevator] = -speed;
				}
				motor[elevator] = hold;
			}
			else if(SensorValue[vbPot] <= 1400 || SensorValue[vbPot] <= 2550)
			{

				while(SensorValue[vbPot] <= 2550 && time1[T3] < timer)
				{
					motor[elevator] = -speed;
				}
				motor[elevator] = hold;
			}
			else
			{
				motor[elevator] = hold;
			}
		}
		else if(vexRT[Btn8L])//UP
		{
			int timer = 1000;
			clearTimer(T3);
			if(SensorValue[vbPot] >= 2600 || SensorValue[vbPot] >= 2000)
			{
				while(SensorValue[vbPot] >= 2000 && time1[T3] < timer)
				{
					motor[elevator] = speed;
				}
				motor[elevator] = hold;
			}
			else if(SensorValue[vbPot] >= 2000 || SensorValue[vbPot] >= 350)
			{
				while(SensorValue[vbPot] >= 400 && time1[T3] < timer)
				{
					motor[elevator] = speed;
				}
				motor[elevator] = hold;
			}
			else
			{
				motor[elevator] = hold;
			}
		}
		else
		{
			motor[elevator] = hold;
		}
}

void mobileGoal(int speed, int hold)//Function used to control all the motors on the lift at once.
{
	if (vexRT[Btn7U] == 1)
	{
		if(SensorValue[liftPot] >= 1300)
		{
			liftControl(127);
		}
		else
		{
			liftControl(15);
			motor[mobile] = speed;
		}
	}
	else if(vexRT[Btn7D] == 1)
	{
		if(SensorValue[liftPot] >= 1300)
		{
			liftControl(127);
		}
		else
		{
			liftControl(15);
			motor[mobile] = -speed;
		}
	}
	else
	{
		motor[mobile] = hold;
	}
}
