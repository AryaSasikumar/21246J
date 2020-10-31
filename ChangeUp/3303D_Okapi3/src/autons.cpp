#include "main.h"

autonRoutines autonRoutine = notSelected;

void executeProgSkills()
{
}
/*-------------------------------------------------------------------*/

void executeRedNear1()
{
}

void executeRedNear2() {}
void executeRedFar1() {}
void executeRedFar2()
{
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(90_deg, 200);
    drive::ramBoi.moveTo({{12_in, 0_in, 0_deg}});
}
void executeBlueNear1() {}
void executeBlueNear2() {}
void executeBlueFar1() {}
void executeBlueFar2() {}