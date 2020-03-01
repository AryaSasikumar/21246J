//-----FLYWHEEL_CONTROL_TASK-----//

bool on = true;
bool off = false;
bool revUp = off;

task autoFlyWheel()
{
	while(true)
	{
		if(revUp == on)
		{
			flyWheelOn = true;
			flyWheelMotor(flyWheelMotorSpeed(shootingSpeed));	//Max is 60
		}
		else
		{
			flyWheelOn = false;
			flyWheelIsUpToSpeed = false;
			elevatorDisabled = false;
			flyWheelMotor(0);
		}
	}
}
//-----FLYWHEEL_CONTROL_TASK-----//


//-----BALL_INTAKE_TASK-----//
task autoBallIntake()
{
	while(true)
	{
		ballIntakeController(1, 0, 0);
	}
}

task autoBallOuttake()
{
	while(true)
	{
		ballIntakeController(0, 1, 0);
	}
}

//-----BALL_INTAKE_TASK-----//
