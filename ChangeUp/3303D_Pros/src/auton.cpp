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

    drive::profileController.generatePath({{0_ft, 0_ft, 0_deg}, {5_ft, 0_ft, 90_deg}}, "A");
    drive::profileController.generatePath({{0_ft, 0_ft, 0_deg}, {3_ft, 0_ft, 0_deg}}, "B");
    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();
    drive::profileController.setTarget("A");
    drive::profileController.waitUntilSettled();
}
