//-----BASE_CONNECTION_FUNCTIONS-----//
void leftBase(float power)//Function used to control all the motors on the left side of the base at once.
{
	motor[leftMiddleBase] = power;
	motor[leftFrontBase] = power;
}

void rightBase(float power)//Function used to control all the motors on the right side of the base at once.
{
	motor[rightMiddleBase] = power;
	motor[rightFrontBase] = power;
}
//-----BASE_CONNECTION_FUNCTIONS-----//


//-----BALL_INTAKE_FUNCTIONS-----//
void ballIntakeMotor(int power)
{
	motor[ballIntake] = power;
}

void ballElevatorMotor(int power)
{
	motor[ballElevator] = power;
}
//-----BALL_INTAKE_FUNCTIONS-----//


//-----LIFT_CONTROL_FUNCTIONS-----//
void liftMotor(int power)
{
	motor[lift] = power;
}
//-----LIFT_CONTROL_FUNCTIONS-----//


//-----CAP_INTAKE_FUNCTIONS-----//
void capIntakeMotor(int power)
{
	motor[capClaw] = power;
}
//-----CAP_INTAKE_FUNCTIONS-----//


//-----CAP_ROTATE_FUNCTIONS-----//
void capRotateMotor(int power)
{
	motor[capTurner] = power;
}
//-----CAP_ROTATE_FUNCTIONS-----//


//-----FLYWHEEL_CONTROL_FUNCTIONS-----//
void flyWheelMotor(int power)
{
	motor[flyWheel] = power;
}
//-----FLYWHEEL_CONTROL_FUNCTIONS-----//
