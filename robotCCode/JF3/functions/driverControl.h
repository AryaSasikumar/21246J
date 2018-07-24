//-----MOTOR_CONNECTION_FUNCTIONS-----//
void leftBase(int power)//Function used to control all the motors on the left side of the base at once.
{
	motor[leftMiddleBase] = power;
	motor[leftFrontBase] = power;
}

void rightBase(int power)//Function used to control all the motors on the right side of the base at once.
{
	motor[rightMiddleBase] = power;
	motor[rightFrontBase] = power;
}
//-----MOTOR_CONNECTION_FUNCTIONS-----//


//-----BASE_CONTROL_FUNCTIONS-----//
int direction = 1;

const unsigned int TrueSpeed[128] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

void baseDriver(int RT2, int RT1)
{
		if(RT2 > 0)
		{
			leftBase(-TrueSpeed[RT2]);
		}
		else if(RT2 < 0)
		{
			RT2 = RT2 * -1;
			leftBase(TrueSpeed[RT2]);
		}

		if(RT1 > 0)
		{
			rightBase(-TrueSpeed[RT1]);
		}
		else if(RT1 < 0)
		{
			RT1 = RT1 * -1;
			rightBase(TrueSpeed[RT1]);
		}
}

void directionController(int button)
{
	if(button == 1)
		{
			direction = direction * (-1);
			wait1Msec(250);
		}
}

void baseController(int rightJoy, int leftJoy)//Function to control base during driver control
{
		if(direction == -1)
		{
			baseDriver((rightJoy),(leftJoy));
		}
		else
		{
			baseDriver((-leftJoy),(-rightJoy));
		}
}
//-----BASE_CONTROL_FUNCTIONS-----//


//-----BALL_INTAKE_FUNCTIONS-----//
void ballIntakeMotor(int power)
{
	motor[ballIntake] = power;
}

void ballIntakeController(int intakeBtn, int outtakeBtn)
{
	if(intakeBtn == 1)
		{
			ballIntakeMotor(127);
		}
		else if(outtakeBtn == 1)
		{
			ballIntakeMotor(-127);
		}
		else
		{
			ballIntakeMotor(0);
		}
}
//-----BALL_INTAKE_FUNCTIONS-----//


//-----LIFT_CONTROL_FUNCTIONS-----//
int liftPower[5] = {127,-90,30,10,-10}; //{upPower, downPower, capHold, regularHold, downHold}
bool liftHoldToggle = true;

void liftMotor(int power)
{
	motor[lift] = power;
}

void liftControl(int liftUp, int liftDown, int sensor)
{
	if(liftUp == 1)
	{
		liftMotor(liftPower[0]);
	}
	else if(liftDown == 1)
	{
		liftMotor(liftPower[1]);
	}
	else
	{
		if(sensor <= 2300)
		{
			liftMotor(liftPower[4]);
		}
		else
		{
			if(liftHoldToggle == false)
			{
				liftMotor(liftPower[3]);
			}
			else
			{
				liftMotor(liftPower[2]);
			}
		}

	}

}

//-----LIFT_CONTROL_FUNCTIONS-----//