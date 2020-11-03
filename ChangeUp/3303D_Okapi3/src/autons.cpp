#include "main.h"

autonRoutines autonRoutine = notSelected;

void executeProgSkills()
{
    // Instant Tower score with hood
    intake::currState = intake::autoShoot;
    pros::delay(1000);
    intake::currState = intake::intakeIn;

    // Tower 1 Score

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{42_in, 0_in, 0_deg}});
    pros::delay(0);
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(286_deg, 200);
    pros::delay(0);
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{14.5_in, 0_in, 0_deg}});
    intake::currState = intake::autoShoot;
    if (intake::currState = intake::notRunning)
    {
        drive::odometry.setPose({45_in, 0_in, 0_deg});
        drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    }
    else
    {
        pros::delay(1000);
        drive::odometry.setPose({45_in, 0_in, 0_deg});
        drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    }

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(155_deg, 200);
    //Filter Right here
    intake::currState = intake::autofilter;
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{22_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(257_deg, 200);

    //Scoring Tower 2

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{28_in, 0_in, 0_deg}});
    // intake::currState = intake::autoShoot;
    // //Vision Stop
    // pros::delay(1500);
    // intake::currState = intake::intakeIn;
    // drive::odometry.setPose({15_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(92_deg, 200);

    // // Scoring Tower 3

    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{46_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(317_deg, 200);
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{14.5_in, 0_in, 0_deg}});
    // intake::currState = intake::autoShoot;
    // //Vision Stop
    // pros::delay(1500);
    // intake::currState = intake::intakeIn;
    // drive::odometry.setPose({12_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(145_deg, 200);
    // drive::odometry.setPose({18_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({45_in, 36_in, 0_deg});
    // drive::chassisController.turnAngle(-7_deg);
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(257_deg, 200);

    // //Scoring Tower 4

    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{28_in, 0_in, 0_deg}});
    // intake::currState = intake::autoShoot;
    // //Vision Stop
    // pros::delay(1500);
    // intake::currState = intake::intakeIn;
    // drive::odometry.setPose({15_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(92_deg, 200);

    // //Scoring Tower 5

    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{46_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(317_deg, 200);
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{14.5_in, 0_in, 0_deg}});
    // intake::currState = intake::autoShoot;
    // //Vision Stop
    // pros::delay(1500);
    // intake::currState = intake::intakeIn;

    // //Scoring Tower 6
    // drive::odometry.setPose({45_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(155_deg, 200);
    // //Filter Right here
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{22_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(257_deg, 200);

    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{28_in, 0_in, 0_deg}});
    // intake::currState = intake::autoShoot;
    // //Vision Stop
    // pros::delay(1500);
    // intake::currState = intake::intakeIn;
    // drive::odometry.setPose({15_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(92_deg, 200);

    // // Scoring Tower 7

    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{46_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(317_deg, 200);
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{14.5_in, 0_in, 0_deg}});
    // intake::currState = intake::autoShoot;
    // //Vision Stop
    // pros::delay(1500);
    // intake::currState = intake::intakeIn;

    //Scoring Middle Tower
}
/*-------------------------------------------------------------------*/
void executeRedNear1()
{
}

void executeRedNear2() {}
void executeRedFar1() {}
void executeRedFar2()
{
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // // drive::turn(180_deg, 200);
    // drive::ramBoi.moveTo({{24_in, 12_in, 0_deg}});
    // drive::chassisController.turnAngle(-7_deg);
    // pros::delay(0);
    // drive::odometry.setPose({24_in, 12_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // pros::delay(0);
    // drive::chassisController.turnAngle(-7_deg);
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(180_deg, 200);
}
void executeBlueNear1() {}
void executeBlueNear2() {}
void executeBlueFar1() {}
void executeBlueFar2() {}