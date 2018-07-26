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

int breakSpeed = 127;
int breakTime = 10;

void stopWithBreaks(int dir, bool useBreaks)
{
	if(useBreaks == true)
	{
		switch(dir)
		{
		case 1:
			leftBase(-breakSpeed);
			rightBase(-breakSpeed);
			break;
		case 2:
			leftBase(breakSpeed);
			rightBase(breakSpeed);
			break;
		case 3:
			leftBase(-breakSpeed);
			rightBase(breakSpeed);
			break;
		case 4:
			leftBase(breakSpeed);
			rightBase(-breakSpeed);
			break;
		default:
			leftBase(0);
			rightBase(0);
		}
		wait1Msec(breakTime);
		leftBase(0);
		rightBase(0);
	}
	else
	{
		leftBase(0);
		rightBase(0);
	}
}

//-----AUTO_DRIVE_TIME_FUNCTIONS-----//
void driveTime(int dir, int speed, int time, bool useBreaks)
{
	switch(dir)
	{
	case 1:
		leftBase(speed);
		rightBase(speed);
		break;
	case 2:
		leftBase(-speed);
		rightBase(-speed);
		break;
	case 3:
		leftBase(speed);
		rightBase(-speed);
		break;
	case 4:
		leftBase(-speed);
		rightBase(speed);
		break;
	default:
		leftBase(0);
		rightBase(0);
	}
	wait1Msec(time);
	stopWithBreaks(dir,useBreaks);
}
//-----AUTO_DRIVE_TIME_FUNCTIONS-----//


//-----AUTO_DRIVE_SENSOR_FUNCTIONS-----//
void driveSensor(int dir, int speed, int measurement, bool useBreaks, int timer)
{
	clearTimer(T1);
	rightBaseSensor = 0;
	leftBaseSensor = 0;
	switch(dir)
	{
	case 1:
		while(rightBaseSensor <= measurement || leftBaseSensor <= measurement || time1[T1] <= timer)
		{
			leftBase(speed);
			rightBase(speed);
		}
		break;
	case 2:
		while(rightBaseSensor >= measurement || leftBaseSensor >= measurement || time1[T1] <= timer)
		{
			leftBase(-speed);
			rightBase(-speed);
		}
		break;
	case 3:
		while(rightBaseSensor >= measurement || leftBaseSensor <= measurement || time1[T1] <= timer)
		{
			leftBase(speed);
			rightBase(-speed);
		}
		break;
	case 4:
		while(rightBaseSensor <= measurement || leftBaseSensor >= measurement || time1[T1] <= timer)
		{
			leftBase(-speed);
			rightBase(speed);
		}
		break;
	default:
		leftBase(0);
		rightBase(0);
	}
	stopWithBreaks(dir,useBreaks);
}
//-----AUTO_DRIVE_SENSOR_FUNCTIONS-----//


//-----AUTO_LIFT_FUNCTIONS-----//
void liftSensor(int dir, int speed, int sensor, int measurement, int hold, int timer)
{
	clearTimer(T1);
	switch(dir)
	{
	case 1:
		while(sensor <= measurement || time1[T1] <= timer)
		{
			leftBase(speed);
			rightBase(speed);
		}
		break;
	case 2:
		while(sensor >= measurement || time1[T1] <= timer)
		{
			leftBase(-speed);
			rightBase(-speed);
		}
		break;
	default:
		leftBase(hold);
		rightBase(hold);
	}
	stopWithBreaks(dir,useBreaks);
}
//-----AUTO_LIFT_FUNCTIONS-----//
