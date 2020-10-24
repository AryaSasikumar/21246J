#ifndef INTAKE_GUARD
#define INTAKE_GUARD

#include "okapi/api.hpp"

using namespace okapi;

namespace intake
{

    enum intakeStates
    {
        notRunning = 'x',
        intakeIn = 'i',
        intakeOut = 'o',
        filter = 'f',
        autofilter = 'k',
        redBall = 'r',
        shoot = 's',
        yield = 'y'
    };

    extern intakeStates currState;

    extern Motor intakeLeft, intakeRight;

    extern pros::Vision vision;

    extern pros::ADILineSensor line;

    extern bool intakeHasBall;

    extern void update();

    extern double liftToDegrees(int potValue);

    extern void act(void *);
} // namespace intake

extern void runIntake(int speed);

#endif