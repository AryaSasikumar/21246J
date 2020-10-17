#include "main.h"
#include "okapi/api.hpp"
#include "okapi/api/control/util/settledUtil.hpp"
Controller controller;

const double joyDeadband = .08;

void initActTasks()
{
    // Constructs and starts tasks for subsystems
    driveActTask = new pros::Task(drive::act, NULL, TASK_PRIORITY_DEFAULT,
                                  TASK_STACK_DEPTH_DEFAULT, "Act Drive");

    intakeActTask = new pros::Task(intake::act, NULL, TASK_PRIORITY_DEFAULT,
                                   TASK_STACK_DEPTH_DEFAULT, "Act Intake");
    // visionTask = new pros::Task(vision::loop, NULL, TASK_PRIORITY_DEFAULT,

    updateTask = new pros::Task(updateFunc, NULL, TASK_PRIORITY_DEFAULT,
                                TASK_STACK_DEPTH_DEFAULT, "Update");
}

// void waitUntilSettled(okapi::AbstractMotor &motor, double isAtTargetError = 50, double isAtTargetDerivative = 5, QTime isAtTargetTime = 250_ms)
// {
//     SettledUtil SettledUtil(std::unique_ptr<AbstractTimer> iatTargetTimer);
//     SettledUtil.isSettled(motor.getTargetPosition() - motor.getPosition());
//     while (1)
//     {
//         pros::delay(10);
//     }
// }

void updateFunc(void *)
{
    while (true)
    {
        drive::update();
        intake::update();

        pros::delay(5);
    }
}

void states();

void autonStates();

bool looperoni = false;