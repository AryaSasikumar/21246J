#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

pros::Task *driveActTask;

pros::Task *intakeActTask;

pros::Task *updateTask;

void initialize()
{
	pros::lcd::initialize();
	printf("before\n");
	printf("after\n");
	initActTasks();

	drive::profileController.startThread();

	// drive::appc.startThread();

	//autonSelector();
	autonRoutine = notSelected;

	// set all the states to not running by default
	drive::currState = drive::yield;
	intake::currState = intake::yield;
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	// macroActTask->resume();
	// set all the states to not running by default
	drive::currState = drive::notRunning;
	intake::currState = intake::notRunning;
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
