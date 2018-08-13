void frontRedAuton()
{
	/*capIntakeMotor(-10);
	liftMotor(-15);
	shootingSpeed = 48;
	revUp = on;
	startTask(autoFlyWheel);
	startTask(autoBallIntake);*/
	fwds(3000, 127, 15, 50, 2000)
	//drivePID(forwards, 47);
	//drivePID(backwards, 40.3);
	//driveTurnPID(left, 91.5);
  /*stopTask(autoBallIntake);
	//drivePID(forwards, 12);
	pew();
	//drivePID(forwards, 15.6);
	pew();
	revUp = off;
	//driveTurnPID(left, 23);
	//drivePID(forwards, 25);
	stopTask(autoFlyWheel);
	//drivePID(backwards, 24);*/
}

void backBlueAuton()
{
	capIntakeMotor(-10);
	liftMotor(-15);
	startTask(autoBallIntake);
	drivePID(forwards, 47);
	driveTurnPID(right, 90);
	liftUp( 580, 127, 15, 50, 2000);
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
	pew();

}
