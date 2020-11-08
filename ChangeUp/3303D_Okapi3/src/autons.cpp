#include "main.h"

autonRoutines autonRoutine = notSelected;

void executeProgSkills()
{
    // Instant Tower score with hood
    intake::currState = intake::autoShoot;
    pros::delay(500);
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
    pros::delay(1000);

    // Back Up from Tower 1

    drive::odometry.setPose({45_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(155_deg, 200);
    //Filter Right here
    intake::currState = intake::autofilter1;
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{22_in, 0_in, 0_deg}});
    //Intake ball
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(257_deg, 200);

    //Scoring Tower 2

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{28.5_in, 0_in, 0_deg}});
    intake::currState = intake::autoShoot;
    pros::delay(1500);

    //Backup From Tower 2

    drive::odometry.setPose({16_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(93_deg, 200);
    intake::currState = intake::autofilter1;

    //Intake ball
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{48_in, 0_in, 0_deg}});
    pros::delay(0);
    intake::currState = intake::autoShoot;
    pros::delay(500);
    intake::currState = intake::intakeIn;
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(314_deg, 200);

    //Scoring Tower 3

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{22_in, 0_in, 0_deg}});
    intake::currState = intake::autoShoot;
    pros::delay(1000);

    //Back Up and Allign
    drive::odometry.setPose({7_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(143_deg, 200);
    drive::odometry.setPose({22_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    intake::currState = intake::autofilter1;
    //Filter
    drive::odometry.setPose({0_in, 27_in, 0_deg});
    drive::ramBoi.moveTo({{73_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    /////////////////////////////////////////////////////////////////////
    // //NO BACK LINE
    // drive::odometry.setPose({45_in, 0_in, 0_deg});
    // drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    // drive::odometry.setPose({0_in, 0_in, 0_deg});
    // drive::turn(143_deg, 200);
    ///////////////////////////////////////////////////////////////////

    //Scoring Tower 4
    drive::turn(270_deg, 200);
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{30_in, 8_in, 0_deg}});
    intake::currState = intake::autoShoot;
    pros::delay(1500);

    // Backup from Tower 4
    drive::odometry.setPose({38_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    intake::currState = intake::autofilter1;
    //Filter
    drive::odometry.setPose({0_in, 52_in, 0_deg});
    drive::ramBoi.moveTo({{20_in, 0_in, 112_deg}});

    //Scoring Tower 5

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{17.5_in, 0_in, 0_deg}});
    intake::currState = intake::autoShoot;
    pros::delay(1000);
    //BackUp from Tower 5
    drive::odometry.setPose({45_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(140_deg, 200);
    //Filter Right here
    intake::currState = intake::autofilter1;
    //Intake Ball
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{30_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(270_deg, 200);

    //Scoring Tower 6

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{28.5_in, 0_in, 0_deg}});
    intake::currState = intake::autoShoot;
    pros::delay(1500);
    //Back up from Tower 6
    drive::odometry.setPose({16_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 0_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(94_deg, 200);
    intake::currState = intake::autofilter1;

    //Intaking Ball

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{46_in, 0_in, 0_deg}});
    pros::delay(0);
    intake::currState = intake::autoShoot;
    pros::delay(500);
    intake::currState = intake::intakeIn;
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::turn(310_deg, 200);

    //Scoring Tower 7

    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::ramBoi.moveTo({{21_in, 0_in, 0_deg}});
    intake::currState = intake::autoShoot;
    pros::delay(1250);

    //Backing up to Middle Tower
    drive::odometry.setPose({50_in, 24_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 90_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    intake::currState = intake::autofilter1;
    drive::chassisController.turnAngle(-33_deg);

    //Scoring Middle Tower
    drive::odometry.setPose({0_in, 3_in, 0_deg});
    drive::ramBoi.moveTo({{25_in, 0_in, 0_deg}});
    intake::currState = intake::autoShoot;
}
/*-------------------------------------------------------------------*/
void executeRedNear1()
{
    drive::odometry.setPose({50_in, 24_in, 0_deg});
    drive::ramBoi.moveTo({{0_in, 0_in, 90_deg}});
    drive::odometry.setPose({0_in, 0_in, 0_deg});
    drive::chassisController.turnAngle(-33_deg);
}

void executeRedNear2() {}
void executeRedFar1()
{
}
void executeRedFar2()
{
}
void executeBlueNear1() {}
void executeBlueNear2() {}
void executeBlueFar1() {}
void executeBlueFar2() {}