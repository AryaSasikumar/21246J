#include "main.h"

using namespace okapi;

ControllerButton shootBtn = controller[ControllerDigital::L1];
ControllerButton filterBtn = controller[ControllerDigital::L2];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton stopBtn = controller[ControllerDigital::R2];
pros::Vision vis(VISION, pros::E_VISION_ZERO_TOPLEFT);
pros::vision_signature_s_t redBall = pros::Vision::signature_from_utility(4, 8097, 10251, 9174, -1541, 265, -638, 3, 0);

pros::vision_signature_s_t blueBall = pros::Vision::signature_from_utility(5, -4191, -2375, -3283, 10347, 14337, 12342, 3, 0);
pros::Vision setRed = vis.set_signature(1, &redBall);
pros::Vision setBlue = vis.set_signature(2, &blueBall);
pros::Vision setExp = vis.set_exposure(150);
namespace intake
{
    intakeStates currState;

    Motor intakeLeft(INTAKE_L, true, AbstractMotor::gearset::green);
    Motor intakeRight(INTAKE_R, false, AbstractMotor::gearset::green);
    Timer ballBrakeTimer;

    ///////////////////////////////////////////////////////
    // VISION CODE

    bool intakeHasBall;

    // bool intakeHadBall;

    // const double kP = 0.0008;
    // const double kI = 0.00;
    // const double kD = 0;
    // const double kayF = 0.15;

    // IterativePosPIDController liftController = IterativeControllerFactory::posPID(kP, kI, kD, 0, std::make_unique<AverageFilter<3>>());

    // bool hasBall()
    // {
    //     if (line.get_value() < 2200)
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    // bool intakeRising()
    // {
    //     if (intakeHasBall && !intakeHadBall)
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    // bool intakeFalling()
    // {
    //     if (intakeHadBall && !intakeHasBall)
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    void
    update()
    {
        pros::vision_object_s_t ball = vis.get_by_size(0);

        if (shootBtn.isPressed())
        {
            currState = shoot;
        }
        if (filterBtn.isPressed())
        {
            currState = filter;
        }
        if (intakeInBtn.changedToPressed())
        {
            currState = intakeIn;
        }
        if (stopBtn.changedToPressed())
            currState = notRunning;

        if (ball.signature == 2 && ball.width >= 100)
        {
            currState = autofilter;
        }
    }
    void act(void *)
    {
        double power;

        while (true)
        {

            switch (currState)
            {
            case notRunning:
                intakeLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
                intakeRight.setBrakeMode(AbstractMotor::brakeMode::coast);
                intakeLeft.moveVoltage(0);
                intakeRight.moveVoltage(0);
                break;
            case shoot:
                // Run motors in same direction.
                intakeLeft.moveVoltage(12000);
                intakeRight.moveVoltage(-12000);
                currState = intakeIn;
                break;

            case intakeIn:

                intakeLeft.moveVoltage(12000);
                intakeRight.moveVoltage(12000);
                break;

            case filter:
                intakeLeft.moveVoltage(-12000);
                intakeRight.moveVoltage(12000);
                currState = notRunning;
                break;
            case autofilter:
                intakeLeft.moveVoltage(-12000);
                intakeRight.moveVoltage(12000);
                pros::delay(2000);
                currState = intakeIn;
                break;
            case redBall:
                currState = notRunning;
                break;
            case autoShoot:
                intakeLeft.moveVoltage(12000);
                intakeRight.moveVoltage(-12000);
                break;
            // case shoot:
            //     intakeLeft.moveVoltage(-12000);
            //     intakeRight.moveVoltage(-12000);
            //     currState = notRunning;
            //     break;
            // case filter:
            //     intakeLeft.moveVoltage(12000);
            //     intakeRight.moveVoltage(12000);
            //     break;
            case yield:
                break;
            }
            pros::delay(10);
        }
    }

} // namespace intake

void runIntake(int speed)
{
    intake::intakeLeft.moveVelocity(1 * speed);
    intake::intakeRight.moveVelocity(-1 * speed);
}
