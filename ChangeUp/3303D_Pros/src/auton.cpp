#include "main.h"
#include "subsystems/drive.hpp"

void executeProgSkills()
{

    // drive::profileController.generatePath({{0_ft, 0_ft, 0_deg}, {5_ft, 3_ft, 0_deg}}, "A");
    // drive::profileController.setTarget("A");

    // drive::profileController.waitUntilSettled();
    // pros::delay(1000);
    // drive::chassisController.turnAngleAsync(355_deg);
    // pros::delay(100);

    // drive::chassisController.turnAngleAsync(710_deg);
    // set the state to zero
    chassis->setState({0_in, 0_in, 0_deg});
    // turn 45 degrees and drive approximately 1.4 ft
    chassis->driveToPoint({1_ft, 1_ft});
    // turn approximately 45 degrees to end up at 90 degrees
    chassis->turnToAngle(90_deg);
    // turn approximately -90 degrees to face {5_ft, 0_ft} which is to the north of the robot
    chassis->turnToPoint({5_ft, 0_ft});
}
