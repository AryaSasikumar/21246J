#define PID_DISTANCE_SCALE (PI/360) //inches/tick
#define PID_ANGLE_SCALE    ((360*6*4*PI)/(24*360*13.5*PI))      //degrees/tick
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

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"
float  pid_Kp = 20.0;
float  pid_Ki = 0.004;
float  pid_Kd = 250;

bool   pidRunning = false;


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
	pid_Kp = 20.0;
	pid_Ki = 0.004;
	pid_Kd = 250;

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

	pid_Kp = 20;//10
	pid_Ki = 0.02;
	pid_Kd = 25;//9.8

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
          pidSensorCurrentValue = sensorAverage() * PID_ANGLE_SCALE;

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
          if(abs(pidError) <= 0.25)//.0001
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






//-----FLYWHEEL_CONTROL_FUNCTIONS-----//

float shootingSpeed = 48;
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

void pew()
{
	waitUntil(flyWheelIsUpToSpeed == true);
	ballIntakeMotor(100);
	ballElevatorMotor(100);
	wait1Msec(700);
	ballIntakeMotor(0);
	ballElevatorMotor(0);

}
//-----FLYWHEEL_CONTROL_FUNCTIONS-----//




//-----BALL_INTAKE_FUNCTIONS-----//
/*void autoBallIntake()
{
	while(ballOneLoaded() == false || ballTwoLoaded() == false)
	{
		intakeControl(1, 0);
	}
	intakeControl(0, 0);
}*/
void autoBallOuttake()
{
	while(ballOneLoaded() == true || ballTwoLoaded() == true)
	{
		intakeControl(0, 1);
	}
	intakeControl(0, 0);
}

task autoBallIntake()
{
	while(true)
	{
		ballIntakeController(1, 0);
	}
}


//-----BALL_INTAKE_FUNCTIONS-----//
