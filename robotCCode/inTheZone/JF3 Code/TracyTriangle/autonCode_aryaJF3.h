#include "driverCode_aryaJF3.h"
//#include "LCDCode_aryaJF3.h"

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
	while(SensorValue[clawPot] <= potValue && time1[T3] < 500 && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0)
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
	while(SensorValue[mogoPot] >= potValue && time1[T2] < 1000)
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


void autonRun(int autonNum)
{
	if(autonNum == 0)//---RED_POLE---//
	{
		motor[elevator] = 15;
		liftUp(1500, -127, 15, 30, 3000);
		clawClose(3100, -127, -20);//(potValue, speed, hold)
		clearTimer(T2);
		liftControl(127);
		motor[elevator] = 127;
		int g = 0;
		bool disable1 = false;
		bool disable2 = false;
		while(g!=2)
		{
			if(SensorValue[liftPot] <= 900 || time1[T2] >= 3000)
			{
				liftControl(30);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
				else{}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		liftControl(30);
		motor[elevator] = 30;

		fwds(650, 80, 10, 250, 3000);//(distance, speed, brake, wait, timer)

		liftDown(1100, 127, 10, 1000, 3000);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)

		//turnLeft(400, 127, 5, 300);
		bwds(700, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		fwds(100, 80, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		Kill();
	}
	else if(autonNum == 1)//---RED_RIGHT_10_POINT---//
	{

	}
	else if(autonNum == 2)//---RED_LEFT_10_POINT---//
	{

		motor[elevator] = 15;
		liftUp(1500, -127, 15, 30, 3000);
		clawClose(3100, -127, -25);//(potValue, speed, hold)

		//vbUp(350, 127, 10);
		//liftUp(1200, -127, 30, 0, 3000);
		clearTimer(T2);
		liftControl(127);
		motor[elevator] = 127;
		int g = 0;
		bool disable1 = false;
		bool disable2 = false;
		while(g!=2)
		{
			if(SensorValue[liftPot] <= 1100 || time1[T2] >= 3000)
			{
				liftControl(40);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
				else{}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		liftControl(30);
		motor[elevator] = 30;
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(1300, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -110, 0);//(potValue, speed, hold)
		liftDown(1575, 127, 10, 175, 3000);
		clawOpen(2575, -127, 0);//(potValue, speed, hold)
		wait1Msec(75);
		vbDown(2350, 127, 10);
		fwds(400, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		clawClose(3100, -127, -10);//(potValue, speed, hold)

		clearTimer(T2);
		clearEncoders();
		base(-127,-127);
		motor[elevator] = 127;
		g = 0;
		disable1 = false;
		disable2 = false;
		int brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 1350 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(brake,brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		wait1Msec(175);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		wait1Msec(75);
		turnRightEncoder(620, -127, 0, 100);//(distance, speed, brake, wait)
		fwds(350, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		turnRightEncoder(200, -127, 0, 100);//(distance, speed, brake, wait)
		fwds(100, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		liftUp(600, -127, 30, 250, 3000);
		mogoOut(2100, -127, 0);//(potValue, speed, hold)
		bwds(100, 127, 10, 50, 3000);//(distance, speed, brake, wait, timer)
		bwds(300, 127, 10, 50, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -110, 0);//(potValue, speed, hold)
		Kill();
	}
	else if(autonNum == 3)//---Blue_Left_20_Point---//
	{
		/*
		clawClose(3100, -127, -10);//(potValue, speed, hold)
		vbUp(350, 127, 10);
		liftUp(1200, -127, 30, 250, 3000);
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(1500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		liftDown(1630, 127, 30, 250, 3000);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		bwds(1500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(1100, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(350, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(750, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1200, -127, 30, 250, 1000);
		mogoOut(1200, -60, 0);//(potValue, speed, hold)
		//mogoIn(2985, 127, 0);//(potValue, speed, hold)
		bwds(700, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)*/



		motor[elevator] = 15;
		liftUp(1450, -127, 15, 30, 3000);
		clawClose(3100, -127, -25);//(potValue, speed, hold)
		//wait1Msec(10);
		//vbUp(350, 127, 10);
		//liftUp(1200, -127, 30, 0, 3000);
		clearTimer(T2);
		liftControl(127);
		motor[elevator] = 127;
		int g = 0;
		bool disable1 = false;
		bool disable2 = false;
		while(g!=2)
		{
			if(SensorValue[liftPot] <= 1100 || time1[T2] >= 3000)
			{
				liftControl(30);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
				else{}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		liftControl(30);
		motor[elevator] = 30;

		clearTimer(T2);
		clearEncoders();
		base(110,110);
		motor[mobile] = -127;
		g = 0;
		disable1 = false;
		disable2 = false;
		int brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 1200 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(-brake,-brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[mogoPot] >= 2390 || time1[T2] >= 3000)
			{
				motor[mobile] = 0;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
			}
		}



		//mogoOut(2390, -127, 0);//(potValue, speed, hold)
		//fwds(1200, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)

		mogoIn(180, -127, 0);//(potValue, speed, hold)

		liftDown(1575, 127, 10, 100, 3000);
		clawOpen(2575, -127, 0);//(potValue, speed, hold)
		wait1Msec(75);
		vbDown(2350, 127, 10);
		fwds(350, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		clawClose(3100, -127, -20);//(potValue, speed, hold)



		clearTimer(T2);
		clearEncoders();
		base(-127,-127);
		motor[elevator] = 127;
		g = 0;
		disable1 = false;
		disable2 = false;
		brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 1500 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(brake,brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		//wait1Msec(10);
		//vbUp(400, 127, 10);
		//wait1Msec(10);
		wait1Msec(180);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		wait1Msec(50);
		//bwds(1450, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		turnRightEncoder(600, -127, 0, 100);//(distance, speed, brake, wait)
		fwds(650, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)



		turnRightEncoder(300, -127, 0, 100);//(distance, speed, brake, wait)
		//fwds(700, 127, 10, 10, 3000);//(distance, speed, brake, wait, timer)
		//liftUp(1200, -127, 30, 0, 1000);

		clearTimer(T2);
		clearEncoders();
		base(127,127);
		liftControl(127);
		//motor[mobile] = -60;
	  g = 0;
		disable1 = false;
		disable2 = false;
		//bool disable3 = false;
		brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 700 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(-brake,-brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[liftPot] <= 1200 || time1[T2] >= 3000)
			{
				liftControl(30);
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		  /*if(SensorValue[mogoPot] >= 100 || time1[T2] >= 3000)
			{
				motor[mobile] = -15;
				if(disable3 == false)
				{
					g++;
					disable3 = true;
				}
			}*/
		}

		mogoOut(2100, -127, 0);//(potValue, speed, hold)
		//mogoIn(2985, 127, 0);//(potValue, speed, hold)
		bwds(500, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		Kill();
	}
	else if(autonNum == 4)//---BLUE_RIGHT_10_POINT---//
	{
		motor[elevator] = 15;
		liftUp(1400, -127, 15, 30, 3000);
		clawClose(3100, -127, -20);//(potValue, speed, hold)

		//vbUp(350, 127, 10);
		//liftUp(1200, -127, 30, 0, 3000);
		clearTimer(T2);
		liftControl(127);
		motor[elevator] = 127;
		int g = 0;
		bool disable1 = false;
		bool disable2 = false;
		while(g!=2)
		{
			if(SensorValue[liftPot] <= 1100 || time1[T2] >= 3000)
			{
				liftControl(30);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
				else{}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		liftControl(30);
		motor[elevator] = 30;
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(1300, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(200, -110, 0);//(potValue, speed, hold)
		liftDown(1575, 127, 10, 175, 3000);
		clawOpen(2575, -127, 0);//(potValue, speed, hold)
		wait1Msec(75);
		vbDown(2350, 127, 10);
		fwds(400, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		clawClose(3100, -127, -10);//(potValue, speed, hold)

		clearTimer(T2);
		clearEncoders();
		base(-127,-127);
		motor[elevator] = 127;
		g = 0;
		disable1 = false;
		disable2 = false;
		int brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 1300 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(brake,brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		wait1Msec(175);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		wait1Msec(75);
		turnLeftEncoder(620, -127, 0, 100);//(distance, speed, brake, wait)
		fwds(350, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		turnLeftEncoder(170, -127, 0, 100);//(distance, speed, brake, wait)
		fwds(100, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1100, -127, 30, 250, 3000);
		mogoOut(2100, -127, 0);//(potValue, speed, hold)
		bwds(100, 127, 10, 50, 3000);//(distance, speed, brake, wait, timer)
		bwds(300, 127, 10, 50, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -110, 0);//(potValue, speed, hold)
		Kill();
	}
	else if(autonNum == 5)//---BLUE_LEFT_10_POINT---//
	{

	}
	else if(autonNum == 6)//---SKILLS---//
	{
		clawClose(3100, -127, -10);//(potValue, speed, hold)
		vbUp(400, 127, 10);
		liftUp(1100, -127, 15, 250, 3000);
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(1000, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		bwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeft(775, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(275, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeft(650, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1200, -127, 10, 250, 1000);
		mogoOut(1200, -127, 0);//(potValue, speed, hold)
		liftDown(1200, 127, 10, 250, 1000);
		bwds(400, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(600, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(300, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(850, 127, 10, 100);//(distance, speed, brake, wait)
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(600, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1200, -127, 10, 250, 1000);
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		turnRight(1550, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(800, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		bwds(400, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(1700, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(800, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
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
	else if(autonNum ==7) //---BLUE_RIGHT_10_POINT---//
	{
		liftUp(1500, -127, 30, 250, 3000);
		clawClose(3100, -127, -10);//(potValue, speed, hold)
		vbUp(400, 127, 10);
		liftUp(1100, -127, 30, 250, 3000);
		mogoOut(2390, -127, 0);//(potValue, speed, hold)
		fwds(1500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		liftDown(1630, 127, 30, 250, 3000);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		bwds(1500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeftEncoder(1200, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(300, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeftEncoder(750, 127, 10, 100);//(distance, speed, brake, wait)
		fwds(500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1200, -127, 30, 250, 1000);
		mogoOut(1200, -60, 0);//(potValue, speed, hold)
		//mogoIn(2985, 127, 0);//(potValue, speed, hold)
		bwds(700, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)*/
	}
	else if(autonNum ==8) //---RED_RIGHT_20_POINT---//
	{
		motor[elevator] = 15;
		liftUp(1500, -127, 15, 30, 3000);
		clawClose(3100, -127, -25);//(potValue, speed, hold)
		//wait1Msec(10);
		//vbUp(350, 127, 10);
		//liftUp(1200, -127, 30, 0, 3000);
		clearTimer(T2);
		liftControl(127);
		motor[elevator] = 127;
		int g = 0;
		bool disable1 = false;
		bool disable2 = false;
		while(g!=2)
		{
			if(SensorValue[liftPot] <= 1100 || time1[T2] >= 3000)
			{
				liftControl(30);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
				else{}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		liftControl(30);
		motor[elevator] = 30;

		clearTimer(T2);
		clearEncoders();
		base(110,110);
		motor[mobile] = -127;
		g = 0;
		disable1 = false;
		disable2 = false;
		int brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 1200 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(-brake,-brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[mogoPot] >= 2350 || time1[T2] >= 3000)
			{
				motor[mobile] = 0;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
			}
		}



		//mogoOut(2390, -127, 0);//(potValue, speed, hold)
		//fwds(1200, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)

		mogoIn(170, -127, 0);//(potValue, speed, hold)

		liftDown(1575, 127, 10, 175, 3000);
		clawOpen(2575, -127, 0);//(potValue, speed, hold)
		wait1Msec(75);
		vbDown(2350, 127, 10);
		fwds(350, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		clawClose(3100, -127, -10);//(potValue, speed, hold)



		clearTimer(T2);
		clearEncoders();
		base(-127,-127);
		motor[elevator] = 127;
		g = 0;
		disable1 = false;
		disable2 = false;
		brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 1500 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(brake,brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[vbPot] <= 400 || time1[T2] >= 3000)
			{
				motor[elevator] = 30;
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		}
		//wait1Msec(10);
		//vbUp(400, 127, 10);
		//wait1Msec(10);
		wait1Msec(175);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		wait1Msec(75);
		//bwds(1450, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		turnLeftEncoder(530, -127, 0, 100);//(distance, speed, brake, wait)
		fwds(700, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)



		turnLeftEncoder(300, -127, 0, 100);//(distance, speed, brake, wait)
		//fwds(700, 127, 10, 10, 3000);//(distance, speed, brake, wait, timer)
		//liftUp(1200, -127, 30, 0, 1000);

		clearTimer(T2);
		clearEncoders();
		base(127,127);
		liftControl(127);
		//motor[mobile] = -60;
	  g = 0;
		disable1 = false;
		disable2 = false;
		//bool disable3 = false;
		brake = 10;
		while(g!=2)
		{
			if(abs(SensorValue[rightEncoder]) >= 700 || time1[T2] >= 3000)
			{
				if(brake != 0)
				{
					base(-brake,-brake);
					wait1Msec(100);
				}
				base(0,0);
				if(disable1 == false)
				{
					g++;
					disable1 = true;
				}
			}
			if(SensorValue[liftPot] <= 1200 || time1[T2] >= 3000)
			{
				liftControl(30);
				if(disable2 == false)
				{
					g++;
					disable2 = true;
				}
				else{}
			}
		  /*if(SensorValue[mogoPot] >= 100 || time1[T2] >= 3000)
			{
				motor[mobile] = -15;
				if(disable3 == false)
				{
					g++;
					disable3 = true;
				}
			}*/
		}

		mogoOut(2100, -127, 0);//(potValue, speed, hold)
		//mogoIn(2985, 127, 0);//(potValue, speed, hold)
		bwds(500, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		Kill();
	}
	else if(autonNum == 9)//---Resistance_Block---//
	{

	}
	else if(autonNum == 10)//---RED_LEFT_20_POINT---//
	{
		clawClose(3100, -127, -10);//(potValue, speed, hold)
		vbUp(310, 127, 10);
		liftUp(800, -127, 30, 250, 3000);
		mogoOut(2360, -127, 0);//(potValue, speed, hold)
		fwds(1500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn(170, -127, 0);//(potValue, speed, hold)
		liftDown(2030, 127, 30, 250, 3000);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		bwds(1400, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnRight(1400, 127, 10, 100);//(distance, speed, brake, wait)
		//fwds(400, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		//turnRight(750, 127, 10, 100);//(distance, speed, brake, wait)
		//fwds(500, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftUp(1000, -127, 30, 250, 1000);
		mogoOut(1200, -60, 0);//(potValue, speed, hold)
		//mogoIn(2985, 127, 0);//(potValue, speed, hold)
		bwds(300, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)*/
	}
}
