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
        redBall = 'r',
        shoot = 's',
        yield = 'y'
    };

    extern intakeStates currState;

    extern Motor intakeLeft, intakeRight;

    extern pros::ADILineSensor line;

    extern Potentiometer liftPot;

    extern AverageFilter<5> liftPotFilter;

    extern bool intakeHasBall;

    extern void update();

    extern void act(void *);
} // namespace intake

extern void runIntake(int speed);

#endif