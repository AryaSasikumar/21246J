void frontRedAuton()
{
	capIntakeMotor(-10);
	liftMotor(-15);
	shootingSpeed = highFW;
	revUp = on;
	startTask(autoFlyWheel);
	startTask(autoBallIntake);
	drivePID(forwards, 46.5, 3000);
	drivePID(backwards, 40.3, 3000);
	driveTurnPID(left, 91.5, 3000);
  stopTask(autoBallIntake);
  highFW = 42;
  lowFW = 15;
	while(ballOneLoaded() == true || ballTwoLoaded() == true)
	{
		ballIntakeController(0, 0, 1);
	}
  wait1Msec(2000);
	ballIntakeController(0, 0, 0);
	revUp = off;
	drivePID(forwards, 25, 3000);
	driveTurnPID(left, 12.5, 3000);
	drivePID(forwards, 25, 3000);
	stopTask(autoFlyWheel);
	drivePID(backwards, 24, 3000);
}

void backBlueAuton()
{
	capIntakeMotor(-10);
	liftMotor(-15);
	startTask(autoBallIntake);
	//drivePID(forwards, 47);
	fwds(4000, 127, 15, 10, 2000);
	//driveTurnPID(right, 90);
	turnRight(1000, 127, 15, 10);
	/*liftUp( 580, 127, 15, 50, 2000);
	autoCapIntake(closeClaw);
	liftDown( 345, 127, -15, 50, 2000);
	shootingSpeed = 49;
	revUp = on;
	startTask(autoFlyWheel);
	autoCapIntake(openClaw);
	stopTask(autoBallIntake);
	rightBase(127);
	leftBase(127);
	wait1Msec(450);
	rightBase(0);
	leftBase(0);
	//drivePID(forwards, 7.5);
	drivePID(backwards, 23);
	autoCapIntake(closeClaw);
	liftUp( 380, 127, 15, 500, 2000);
	autoCapRotate();
	autoCapIntake(openClaw);
	drivePID(forwards, 5);
	drivePID(backwards, 3);
	drivePID(forwards, 10);
	driveTurnPID(left, 8);
	pew();
	shootingSpeed = 46;
	pew();*/

}
