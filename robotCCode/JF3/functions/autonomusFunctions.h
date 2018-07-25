int forward = 1;
int backward = 2;
int right = 3;
int left = 4;

int liftUp = 127;
int liftDown = 90;
int regularHold = 10;
int strongHold = 20;
int downHold = 20;
int noHold = 0;

//-----AUTO_DRIVE_TIME_FUNCTIONS-----//
void driveTime(int dir, int speed, int time, bool stopWithBreaks, int breakSpeed, int breakTime)
{
	if(dir == 1)
	{
		leftBase(speed);
		rightBase(speed);
		wait1Msec(time);
		if(stopWithBreaks == true)
		{
			leftBase(-breakSpeed);
			rightBase(-breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else if(dir == 2)
	{
		leftBase(-speed);
		rightBase(-speed);
		wait1Msec(time);
		if(stopWithBreaks == true)
		{
			leftBase(breakSpeed);
			rightBase(breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else if(dir == 3)
	{
		leftBase(-speed);
		rightBase(speed);
		wait1Msec(time);
		if(stopWithBreaks == true)
		{
			leftBase(breakSpeed);
			rightBase(-breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else if(dir == 4)
	{
		leftBase(speed);
		rightBase(-speed);
		wait1Msec(time);
		if(stopWithBreaks == true)
		{
			leftBase(-breakSpeed);
			rightBase(breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else
	{
		leftBase(0);
		rightBase(0);
	}
	leftBase(0);
	rightBase(0);
}
//-----AUTO_DRIVE_TIME_FUNCTIONS-----//


//-----AUTO_DRIVE_SENSOR_FUNCTIONS-----//
void driveSensor(int dir, int speed, int measurement,int rightSensor, int leftSensor,bool stopWithBreaks, int breakSpeed, int breakTime)
{
	rightSensor = 0;
	leftSensor = 0;
	if(dir == 1)
	{
		leftBase(speed);
		rightBase(speed);

		if(stopWithBreaks == true)
		{
			leftBase(-breakSpeed);
			rightBase(-breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else if(dir == 2)
	{
		leftBase(-speed);
		rightBase(-speed);
		wait1Msec(time);
		if(stopWithBreaks == true)
		{
			leftBase(breakSpeed);
			rightBase(breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else if(dir == 3)
	{
		leftBase(-speed);
		rightBase(speed);
		wait1Msec(time);
		if(stopWithBreaks == true)
		{
			leftBase(breakSpeed);
			rightBase(-breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else if(dir == 4)
	{
		leftBase(speed);
		rightBase(-speed);
		wait1Msec(time);
		if(stopWithBreaks == true)
		{
			leftBase(-breakSpeed);
			rightBase(breakSpeed);
			wait1Msec(breakTime);
		}
		leftBase(0);
		rightBase(0);
	}
	else
	{
		leftBase(0);
		rightBase(0);
	}
	leftBase(0);
	rightBase(0);
}
//-----AUTO_DRIVE_SENSOR_FUNCTIONS-----//
