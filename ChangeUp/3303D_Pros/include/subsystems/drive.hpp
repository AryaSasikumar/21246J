#ifndef DRIVE_GUARD
#define DRIVE_GUARD

#include "okapi/api.hpp"

using namespace okapi;

namespace drive
{
    enum driveStates
    {
        notRunning = 'x',
        running = 'r',
        yield = 'a'
    };

    extern driveStates currState;
    extern Motor driveR1, driveR2, driveR3, driveL1, driveL2, driveL3;
    extern ChassisControllerIntegrated chassisController;
    extern AsyncMotionProfileController profileController;

    extern void update();

    extern void act(void *);

    extern void turn(QAngle angle, double maxVel = 100, bool async = true);
} // namespace drive

extern void removePaths(std::string path1);
extern void removePaths(std::string path1, std::string path2);

#endif