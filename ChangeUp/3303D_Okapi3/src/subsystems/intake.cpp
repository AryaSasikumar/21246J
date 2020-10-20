#include "main.h"

using namespace okapi;

ControllerButton shootBtn = controller[ControllerDigital::L1];
ControllerButton filterBtn = controller[ControllerDigital::L2];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton stopBtn = controller[ControllerDigital::R2];

namespace intake
{
    intakeStates currState;

    Motor intakeLeft(INTAKE_L, true, AbstractMotor::gearset::green);
    Motor intakeRight(INTAKE_R, false, AbstractMotor::gearset::green);

    Timer ballBrakeTimer;

    // bool intakeHasBall;
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

    void update()
    {
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
                intakeRight.moveVoltage(12000);
                currState = notRunning;
                break;

            case intakeIn:
                intakeLeft.moveVoltage(12000);
                intakeRight.moveVoltage(-12000);
                break;

            case filter:
                intakeLeft.moveVoltage(-12000);
                intakeRight.moveVoltage(-12000);
                currState = notRunning;
                break;

            case redBall:
                currState = notRunning;
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
