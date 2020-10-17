#include "main.h"
#include "subsystems/drive.hpp"

void executeProgSkills()
{
    drive::profileController.generatePath({{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
                                           {3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
                                          "A"                    // Profile name
    );

    drive::profileController.setTarget("A");
    drive::profileController.waitUntilSettled();
}
