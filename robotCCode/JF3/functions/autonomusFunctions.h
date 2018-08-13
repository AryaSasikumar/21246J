#define PID_DISTANCE_SCALE (PI/360) //inches/tick
#define PID_ANGLE_SCALE    (0.095)  ////10ths of degrees ((360*6*4*PI)/(24*360*13.5*PI))
#define PID_LIFT_SCALE    1
#define PID_MOTOR_SCALE     -1

//   1 rotation      24 teeth      360 ticks     ///  14*pi inches    1 rotation
//   ----------- * ------------ * ------------ * ///  ------------ * ------------
//   4*pi inches    1 rotation       6 teeth     ///  1 rotation     360 degrees
//
//    ticks
//   -------
//   inches


#define PID_DRIVE_MAX       127
#define PID_DRIVE_MIN     (-127)

#define PID_INTEGRAL_LIMIT  50

float  pid_Kp = 20.0;
float  pid_Ki = 0.004;
float  pid_Kd = 250;

bool   pidRunning = false;

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"



int sensorAverage()
{
	return ((abs(leftBaseSensor)+abs(rightBaseSensor))/2);
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  pid control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

int forwards = 1;
int backwards = -1;
void drivePID(int dir, float pidRequestedValue)
{
	pid_Kp = 15.0;
	pid_Ki = 0.004;
	pid_Kd = 225;

	pidRunning = true;
	pidRequestedValue = dir*pidRequestedValue;

	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;

	// If we are using an encoder then clear it
	leftBaseSensor = 0;
	rightBaseSensor = 0;


	// Init the variables - thanks Glenn :)
	pidLastError  = 0;
	pidIntegral   = 0;

	while( pidRunning )
	{
		// Is PID control active ?
		if( pidRunning )
		{
			// Read the sensor value and scale
			pidSensorCurrentValue = dir*sensorAverage() * PID_DISTANCE_SCALE;

			// calculate error
			pidError = pidSensorCurrentValue - pidRequestedValue;

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

			// limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// send to motor
			leftBase(pidDrive * PID_MOTOR_SCALE);
			rightBase(pidDrive * PID_MOTOR_SCALE);
			showError = pidError;
			if(abs(pidError) <= 2)
			{
				pidRunning = !pidRunning;
			}
		}
		else
		{
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			leftBase(0);
			rightBase(0);
		}

		// Run at 50Hz
		wait1Msec(25);
	}

}






int right = 1;
int left = -1;

void driveTurnPID(int dir, float pidRequestedValue)
{

	pidRunning = true;

	pid_Kp = 10;
	pid_Ki = 0.05;
	pid_Kd = 40;

	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;

	// If we are using an encoder then clear it
	baseGyroSensor = 0;
	wait1Msec(200);


	// Init the variables - thanks Glenn :)
	pidLastError  = 0;
	pidIntegral   = 0;

	while( pidRunning )
	{
		// Is PID control active ?
		if( pidRunning )
		{
			// Read the sensor value and scale
			pidSensorCurrentValue = abs(baseGyroSensor) * PID_ANGLE_SCALE;

			// calculate error
			pidError = pidSensorCurrentValue - pidRequestedValue;

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

			// limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// send to motor
			pidDrive = dir*pidDrive;
			leftBase(pidDrive * PID_MOTOR_SCALE);
			rightBase(-pidDrive * PID_MOTOR_SCALE);
			showError = pidError;
			if(abs(pidError) <= 0.5)//.0001
			{
				pidRunning = !pidRunning;
			}
		}
		else
		{
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			leftBase(0);
			rightBase(0);
		}

		// Run at 50Hz
		wait1Msec(25);
	}
	// clear all
	pidError      = 0;
	pidLastError  = 0;
	pidIntegral   = 0;
	pidDerivative = 0;
	leftBase(0);
	rightBase(0);

}

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




//-----Non_Pid_Functions-----//

void base(int rSpeed, int lSpeed)
{
	rightBase(rSpeed);
	leftBase(lSpeed);
}

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

void clearEncoders()
{
	SensorValue[rightBaseSensor] = 0;
	SensorValue[leftBaseSensor] = 0;
}

void fwds(int distance, int speed, int brake, int wait, int timer)
{
	clearTimer(T2);
	clearEncoders();
	while(abs(SensorValue[rightBaseEncoder]) < distance && time1[T2] < timer)
	{
		leftBase(speed);
		rightBase(speed);
	}
	if(brake != 0)
	{
		base(-brake,-brake);
		wait1Msec(100);
	}
		leftBase(0);
		rightBase(0);
	wait1Msec(wait);
}

void bwds(int distance, int speed, int brake, int wait, int timer)
{
	fwds(distance, -speed, brake, wait, timer);
}

void turnRight(int distance, int speed, int brake, int wait)
{
	clearEncoders();
	//RIGHT
	while(abs(SensorValue[rightBaseSensor]) <= distance)
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
	clearEncoders();
	//LEFT
	while(abs(SensorValue[rightBaseSensor]) <= distance)
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

//-----FLYWHEEL_CONTROL_FUNCTIONS-----//
void pew()
{
	waitUntil(flyWheelIsUpToSpeed == true);
	ballIntakeMotor(127);
	ballElevatorMotor(127);
	wait1Msec(550);
	ballIntakeMotor(0);
	ballElevatorMotor(0);

}
//-----FLYWHEEL_CONTROL_FUNCTIONS-----//



//-----CAP_INTAKE_FUNCTIONS-----//
int closeClaw = 1;
int openClaw = -1;

void autoCapIntake(int dir)
{
	if(dir == closeClaw && clawSensor >= 1500)
	{
		capIntakeMotor(127);
	}
	else if(dir == openClaw && clawSensor <= 2000)
	{
		capIntakeMotor(-127);
	}
	else
	{
		if(clawSensor <= 1900)
		{
			capIntakeMotor(20);
		}
		else
		{
			capIntakeMotor(-10);
		}
	}
}
//-----CAP_INTAKE_FUNCTIONS-----//


//-----CAP_ROTATE_FUNCTIONS-----//
void autoCapRotate()
{
	capRotateActivate = true;
	while(capRotateActivate == true)
	{
		if(capIsFlipped == true)
		{
			if(clawTurnerSensor >= 650)
			{
				capRotateMotor(127);
			}
			if(clawTurnerSensor < 650)
			{
				capIsFlipped = false;
				capRotateActivate = false;
			}
		}
		else
		{
			if(clawTurnerSensor <= 3430)
			{
				capRotateMotor(-127);
			}
			if(clawTurnerSensor > 3430)
			{
				capIsFlipped = true;
				capRotateActivate = false;
			}
		}
	}
	if(clawTurnerSensor >= 1800)
	{
		capRotateMotor(10);
	}
	else
	{
		capRotateMotor(-10);
	}
}
//-----CAP_ROTATE_FUNCTIONS-----//


//-----LIFT_CONTROL_FUNCTIONS-----//
void liftUp(int potValue, int speed, int hold, int waitTime, int timer)
{
	clearTimer(T3);
	while(liftSensor <= potValue && time1[T3] < timer)
	{
		liftMotor(speed);
	}
	liftMotor(hold);
	wait1Msec(waitTime);
}

void liftDown(int potValue, int speed, int hold, int waitTime, int timer)
{
	clearTimer(T3);
	while(liftSensor >= potValue && time1[T3] < timer)
	{
		liftMotor(-speed);
	}
	liftMotor(hold);
	wait1Msec(waitTime);
}
//-----LIFT_CONTROL_FUNCTIONS-----//
