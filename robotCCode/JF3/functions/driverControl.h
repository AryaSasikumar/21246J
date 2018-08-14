bool flyWheelIsUpToSpeed = false;

//-----DIRECTION_CONTROL_FUNCTIONS-----//
int direction = 1;

void directionController(int button)
{
	if(button == 1)
	{
		direction = direction * (-1);
		wait1Msec(250);
	}
}
//-----DIRECTION_CONTROL_FUNCTIONS-----//


//-----INTAKE_BUTTON_CONTROL_FUNCTIONS-----//
int currentIntake(bool whichIntake)//Which intake: 1=ball intake , 0=cap intake
{
	if(direction == 1)
	{
		if(whichIntake == 1)
		{
			return ballIntakeBtn;
		}
		else
		{
			return capClawCloseBtn;
		}
	}
	else
	{
		if(whichIntake == 1)
		{
			return capClawCloseBtn;
		}
		else
		{
			return ballIntakeBtn;
		}
	}
}

int currentOuttake(bool whichIntake)
{
	if(direction == 1)
	{
		if(whichIntake == 1)
		{
			return ballOuttakeBtn;
		}
		else
		{
			return capClawOpenBtn;
		}
	}
	else
	{
		if(whichIntake == 1)
		{
			return capClawOpenBtn;
		}
		else
		{
			return ballOuttakeBtn;
		}
	}
}
//-----INTAKE_BUTTON_CONTROL_FUNCTIONS-----//


//-----BASE_CONTROL_FUNCTIONS-----//
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

bool ballOneLoaded()
{
	if(ballTopSensor <= 2000)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool ballTwoLoaded()
{
	if(ballBottomSensor <= 2000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool elevatorDisabled = false;

void intakeControl(int intakeBtn, int outtakeBtn)
{
	if(intakeBtn == 1)
	{
		if(ballOneLoaded() == true && ballTwoLoaded() == true)
		{
			ballIntakeMotor(0);
		}
		else
		{
			ballIntakeMotor(127);
		}
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

//bool ballOneLoaded = false;
//bool ballTwoLoaded = false;
//bool elevatorDisabled = false;

bool stillPressed = false;

void elevatorControl(int intakeBtn, int outtakeBtn, int shootTwoInOneBtn)
{
	if(intakeBtn == 1 && elevatorDisabled == false)
	{
		flySpeed = highFW;
		shootingSpeed = highFW;
		if(ballOneLoaded() == true)
		{
			ballElevatorMotor(0);
			stillPressed = true;
		}
		else
		{
			ballElevatorMotor(127);
		}
	}
	else if(intakeBtn == 0 && stillPressed == true)
	{
		elevatorDisabled = true;
		stillPressed = false;
	}
	else if(pewBtn == 1)
	{
		flySpeed = 48;
		if(flyWheelIsUpToSpeed == true)
		{
			ballElevatorMotor(127);
			if(ballOneLoaded() == false)
			{
				elevatorDisabled = false;
			}
		}
		else
		{
			ballElevatorMotor(0);
		}
	}
	else if(shootTwoInOneBtn == 1)
	{
		if(ballOneLoaded() == true || ballTwoLoaded() == true)
		{
			flySpeed = highFW;
			shootingSpeed = flySpeed;
			elevatorDisabled = false;
			if(flyWheelIsUpToSpeed == true)
			{
				ballElevatorMotor(127);
			}
		}
		else if(ballOneLoaded() == false || ballTwoLoaded() == true)
		{
			flySpeed = lowFW;
			shootingSpeed = flySpeed;
			elevatorDisabled = false;
			if(flyWheelIsUpToSpeed == true)
			{
				ballElevatorMotor(127);
			}
		}
		else if(ballOneLoaded() == true || ballTwoLoaded() == false)
		{
			flySpeed = lowFW;
			shootingSpeed = flySpeed;
			elevatorDisabled = false;
			if(flyWheelIsUpToSpeed == true)
			{
				ballElevatorMotor(127);
			}
		}
		else if(ballOneLoaded() == false && ballTwoLoaded() == false)
		{
			flySpeed = highFW;
			shootingSpeed = flySpeed;
			elevatorDisabled = false;
			ballElevatorMotor(127);
		}
		else
		{
			ballElevatorMotor(0);
		}
	}



	else if(outtakeBtn == 1 && intakeBtn == 0)
	{
		ballElevatorMotor(-127);
		if(ballOneLoaded() == false)
		{
			elevatorDisabled = false;
		}
	}
	else
	{
		ballElevatorMotor(0);
	}
}



void ballIntakeController(int intakeBtn, int outtakeBtn, int shootTwoInOneBtn)
{
	elevatorControl(intakeBtn, outtakeBtn, shootTwoInOneBtn);
	intakeControl(intakeBtn, outtakeBtn);
}
//-----BALL_INTAKE_FUNCTIONS-----//


//-----LIFT_CONTROL_FUNCTIONS-----//
int liftPower[5] = {127,-90,30,10,-10}; //{upPower, downPower, capHold, regularHold, downHold}
int liftHieghtLow = 990;
int liftHieghtHigh = 1400;
bool liftHoldToggle = false;


void liftControl(int liftUp, int liftDown, int sensor, int height, int timer)
{
	if(liftUp == 1)
	{
		liftMotor(liftPower[0]);
	}
	else if(liftDown == 1)
	{
		liftMotor(liftPower[1]);
	}
	else if(vexRT[Btn8L] == 1)
	{
		clearTimer(T4);
		if(sensor <= height && time1[T4] < timer)
		{
			liftMotor(70);
		}
		else if(sensor >= height && time1[T4] < timer)
		{
			liftMotor(10);
		}
	}
	else
	{
		if(sensor <= 900)
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


//-----CAP_INTAKE_FUNCTIONS-----//
void capIntakeController(int intakeBtn, int outtakeBtn, int sensor)
{

	if(intakeBtn == 1 && outtakeBtn == 0 && sensor >= 1500)
	{
		capIntakeMotor(127);
	}
	else if(outtakeBtn == 1 && intakeBtn == 0 && sensor <= 1900)
	{
		capIntakeMotor(-127);
	}
	else if(intakeBtn == 1 && outtakeBtn == 1 && sensor <= 2100)
	{
		capIntakeMotor(-127);
	}
	else
	{
		if(sensor <= 1900)
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
bool capRotateActivate = false;
bool capIsFlipped = false;
void capRotateController(int turnerBtn, int sensor)
{
	if(turnerBtn == 1)
	{
		capRotateActivate = !capRotateActivate;
		wait1Msec(300);
	}
	if(capRotateActivate == true)
	{
		if(capIsFlipped == true)
		{
			if(sensor >= 650)
			{
				capRotateMotor(127);
			}
			if(sensor < 650)
			{
				capIsFlipped = false;
				capRotateActivate = false;
			}
		}
		else
		{
			if(sensor <= 3430)
			{
				capRotateMotor(-127);
			}
			if(sensor > 3430)
			{
				capIsFlipped = true;
				capRotateActivate = false;
			}
		}
	}
	else
	{
		if(sensor >= 1800)
		{
			capRotateMotor(10);
		}
		else
		{
			capRotateMotor(-10);
		}
	}
}
//-----CAP_ROTATE_FUNCTIONS-----//

//-----FLYWHEEL_CONTROL_FUNCTIONS-----//
bool flyWheelOn = false;

float ticks = 1;
float microSeconds = 1;
float flyWheelSpeed = 1;
float holdSpeed = 1;
float flyWheelCurrentRPS()//Rotations/Second
{

	if(time1[T2] <= 100)
	{
		ticks = flyWheelSensor;
		microSeconds = time1[T2]+1;
		flyWheelSpeed = (ticks*1000)/(microSeconds*360);
		return flyWheelSpeed;
	}
	else
	{
		flyWheelSensor = 1;
		clearTimer(T2);
		holdSpeed = flyWheelSpeed;
		return flyWheelSpeed;
	}

}

int outputSpeed = 0;
float powerToSpeedRatio = 1.924;

int flyWheelMotorSpeed(int desiredRPS)
{

	if(flyWheelCurrentRPS() < desiredRPS) //66 rps max output
	{
		outputSpeed = ((powerToSpeedRatio*flyWheelCurrentRPS())+5);
		if(outputSpeed <= 70)
		{
			outputSpeed = 70;
		}
		return outputSpeed;
	}
	else
	{
		flyWheelIsUpToSpeed = true;
		outputSpeed = outputSpeed -(outputSpeed*0.1);
		return outputSpeed;
	}

}

void flyWheelController(int toggleBtn, int flyWheelRPS)
{
	if(toggleBtn == 1)
	{
		flyWheelOn = !flyWheelOn;
		wait1Msec(300);
	}
	if(flyWheelOn == true)
	{
		flyWheelMotor(flyWheelMotorSpeed(flyWheelRPS));	//Max is 60
	}
	else
	{
		flyWheelIsUpToSpeed = false;
		elevatorDisabled = false;
		flyWheelMotor(0);
	}
}

//-----FLYWHEEL_CONTROL_FUNCTIONS-----//
