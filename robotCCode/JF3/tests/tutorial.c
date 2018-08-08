
#pragma config(Sensor, I2C_1,  RightEncoder,      sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  LeftEncoder,      sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,  LeftBase,  tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, I2C_2)
#pragma config(Motor,  port3,  RightBase, tmotorVex393HighSpeed_MC29, openLoop, driveRight, encoderPort, I2C_1)

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("Motors")

#pragma platform(VEX)

void moveBase (int speed)
{
	motor[LeftBase] = speed;
	motor[RightBase] = speed;
}

void turnBase (int speed) // positive is clockwise
{
	motor[LeftBase] = speed;
	motor[RightBase] = -speed;
}
//reading: ticks -- 627.2ticks/revolution
// 1 turn of the wheels -- 4 inch wheels = 627.2 *2 ticks
// 1 turn of each wheel 4*pi inches
// 4*pi inches = 627.2*2ticks
// ticks/inch = 627.2*2/(4*pi) = 99.82198

//when my error is 30
//the actual error in inches - 0.3

int inchToTicks (float inch)
{
	int ticks;
	ticks = inch*99.82198;
	return ticks;
}

int fixTimerValue (float rawSeconds)
{
	int miliseconds;
	miliseconds = rawSeconds*1000;
	if (miliseconds < 250)
	{
		miliseconds = 250;
	}
	return miliseconds;
}

//>>>>>>>>>>>>>>>>>>>>>>>>------------------0-----------------<<<<<<<<<<<<<<<<<<<<<<<<<

void PIDBaseControl (float target, float waitTime, float maxPower = 1)
{
	float Kp = 0.2;
	float Ki = 0.05;
	float Kd = 0.5;

	int error;

	float proportion;
	int integralRaw;
	float integral;
	int lastError;
	int derivative;

	float integralActiveZone = inchToTicks(3);
	float integralPowerLimit = 50/Ki;

	int finalPower;

	bool timerBool = true;

	nMotorEncoder[LeftBase] = 0;
	nMotorEncoder[RightBase] = 0;

	clearTimer(T1);

	while (time1[T1] < fixTimerValue(waitTime))
	{
		error = inchToTicks(target)-(nMotorEncoder[LeftBase]+nMotorEncoder[RightBase]);

		proportion = Kp*error;

		if (abs(error) < integralActiveZone && error != 0)
		{
			integralRaw = integralRaw+error;
		}
		else
		{
			integralRaw = 0;
		}

		if (integralRaw > integralPowerLimit)
		{
			integralRaw = integralPowerLimit;
		}
		if (integralRaw < -integralPowerLimit)
		{
			integralRaw = -integralPowerLimit;
		}

		integral = Ki*integralRaw;

		derivative = Kd*(error-lastError);
		lastError = error;

		if (error == 0)
		{
			derivative = 0;
		}

		finalPower = proportion+integral+derivative; //proportion+derivative+integral

		if (finalPower > maxPower*127)
		{
			finalPower = maxPower*127;
		}
		else if (finalPower < -maxPower*127)
		{
			finalPower = -maxPower*127;
		}

		moveBase(finalPower);

		wait1Msec(40);

		if (error < 30)
		{
			timerBool = false;
		}

		if (timerBool)
		{
			clearTimer(T1);
		}
	}
	moveBase(0);
}

void PIDBaseTurn (int target, float waitTime, float maxPower = 1)
{
	float Kp = 0.2;
	float Ki = 0.05;
	float Kd = 0.5;

	int error;

	float proportion;
	int integralRaw;
	float integral;
	int lastError;
	int derivative;

	float integralActiveZone = inchToTicks(3);
	float integralPowerLimit = 50/Ki;

	int finalPower;

	bool timerBool = true;

	nMotorEncoder[LeftBase] = 0;
	nMotorEncoder[RightBase] = 0;

	clearTimer(T1);

	while (time1[T1] < fixTimerValue(waitTime))
	{
		error = target-(nMotorEncoder[LeftBase]-nMotorEncoder[RightBase]);

		proportion = Kp*error;

		if (abs(error) < integralActiveZone && error != 0)
		{
			integralRaw = integralRaw+error;
		}
		else
		{
			integralRaw = 0;
		}

		if (integralRaw > integralPowerLimit)
		{
			integralRaw = integralPowerLimit;
		}
		if (integralRaw < -integralPowerLimit)
		{
			integralRaw = -integralPowerLimit;
		}

		integral = Ki*integralRaw;

		derivative = Kd*(error-lastError);
		lastError = error;

		if (error == 0)
		{
			derivative = 0;
		}

		finalPower = proportion+integral+derivative; //proportion+derivative+integral

		if (finalPower > maxPower*127)
		{
			finalPower = maxPower*127;
		}
		else if (finalPower < -maxPower*127)
		{
			finalPower = -maxPower*127;
		}

		turnBase(finalPower);

		wait1Msec(40);

		if (error < 30)
		{
			timerBool = false;
		}

		if (timerBool)
		{
			clearTimer(T1);
		}
	}
	turnBase(0);
}

task main ()
{
	PIDBaseControl(12,0,0.7); // move forward 12 inches with 0.25 sec delay;
	PIDBaseTurn(1000,1,); // turn right 1000 counts with 1 sec delay;
	PIDBaseControl(-7.5,1); // back off 7.5 inches with 1 sec delay;

	while(true)
	{
		wait1Msec(20);
	}
}
