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
  lowFW = 42;
	while(ballOneLoaded() == true || ballTwoLoaded() == true)
	{
		ballIntakeController(0, 0, 1);
	}
	drivePID(forwards, 35, 3000);
  wait1Msec(2000);
	ballIntakeController(0, 0, 0);
	revUp = off;
	//drivePID(forwards, 25, 3000);
	driveTurnPID(left, 15, 3000);
	drivePID(forwards, 20, 3000);
	stopTask(autoFlyWheel);
	drivePID(backwards, 24, 3000);



	/*capIntakeMotor(-10);
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
  lowFW = 11;
	while(ballOneLoaded() == true || ballTwoLoaded() == true)
	{
		ballIntakeController(0, 0, 1);
	}
  wait1Msec(2000);
	ballIntakeController(0, 0, 0);
	revUp = off;
	drivePID(forwards, 25, 3000);
	driveTurnPID(left, 12.5, 3000);
	drivePID(forwards, 26, 3000);
	stopTask(autoFlyWheel);
	drivePID(backwards, 24, 3000);*/
}

void backBlueAuton()
{
	capIntakeMotor(-10);
	liftMotor(-15);
	startTask(autoBallIntake);
	drivePID(forwards, 47,3000);
	driveTurnPID(right, 90,3000);
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
	drivePID(backwards, 23,3000);
	autoCapIntake(closeClaw);
	liftUp( 380, 127, 15, 500, 2000);
	autoCapRotate();
	autoCapIntake(openClaw);
	drivePID(forwards, 5,3000);
	drivePID(backwards, 3,3000);
	drivePID(forwards, 10,3000);
	driveTurnPID(left, 8,3000);
	pew();
	shootingSpeed = 46;
	pew();

}

void backRedAuton()
{

	capIntakeMotor(-10);
	liftMotor(-15);

	drivePID(forwards, 40,2500);
	startTask(autoBallIntake);
	drivePID(forwards, 7,500);
	stopTask(autoBallIntake);
	drivePID(forwards, 10,500);
	drivePID(backwards, 4,500);
	startTask(autoBallIntake);
	driveTurnPID(left, 90,3000);
	stopTask(autoBallIntake);
	liftUp(580, 127, 15, 50, 2000);
	autoCapIntake(closeClaw);
	liftDown( 345, 127, -15, 50, 2000);
	//flySpeed = 48;
	//shootingSpeed = 48;
	//revUp = on;
	//startTask(autoFlyWheel);
	autoCapIntake(openClaw);

	rightBase(127);
	leftBase(127);
	wait1Msec(450);
	rightBase(0);
	leftBase(0);
	drivePID(backwards, 21.5,2500);
	autoCapIntake(closeClaw);
	wait1Msec(150);
	drivePID(forwards, 8,500);
	liftUp( 380, 127, 15, 500, 2000);
	autoCapRotate();


	driveTurnPID(right, 92,3000);


	drivePID(backwards, 40,2000);
	//driveTurnPID(left, 91,3000);
	liftUp( 1500, 127, 17, 50, 2000);
	drivePID(backwards, 7.5, 1500);
	//drivePID(forwards, 4,500);
	liftDown( 1500, 90, 15, 50, 2000);
	autoCapIntake(openClaw);
	drivePID(forwards, 10,500);
	//driveTurnPID(right, 8,3000);
	//flySpeed = 48;
	//shootingSpeed = 48;
	//pew();
	//shootingSpeed = 46;
	//flySpeed = 46;
	//pew();

}
