#include "main.h"

using namespace okapi;

ControllerButton shootBtn = controller[ControllerDigital::L1];
ControllerButton filterBtn = controller[ControllerDigital::L2];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton shotBtn = controller[ControllerDigital::R2];

namespace intake
{
    intakeStates currState;

    Motor intakeLeft(INTAKE_L, true, AbstractMotor::gearset::green);
    Motor intakeRight(INTAKE_R, false, AbstractMotor::gearset::green);

    Timer ballBrakeTimer;

    bool intakeHasBall;
    bool prevIntakeHasBall;

    void update()
    {

        // User input handlers
        if (shootBtn.isPressed())
        {
            currState = shoot;
        }
        if (filterBtn.isPressed())
        {
            currState = filter;
        }
        if (currState == notRunning && intakeInBtn.changedToPressed())
        {
            currState = intakeIn;
        }
        if (filterBtn.changedToPressed())
        {
            // Engage lift PID if B button is pressed.
            currState = filter;
        }
    }

    void act(void *)
    {
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
            case intakeIn:
                // Run motors in same direction.
                intakeLeft.moveVoltage(-1200);
                intakeRight.moveVoltage(-1200);
                break;
            case shoot:
                intakeLeft.moveVelocity(200);
                intakeRight.moveVelocity(200);
                currState = notRunning;
                break;
            case filter:
                intakeLeft.moveVoltage(-12000);
                intakeRight.moveVoltage(12000);
                break;
            case yield:
                break;
            }

            pros::delay(10);
        }
    }

} // namespace intake

void runIntake(int speed)
{
    intake::intakeLeft.moveVelocity(-1 * speed);
    intake::intakeRight.moveVelocity(1 * speed);
}