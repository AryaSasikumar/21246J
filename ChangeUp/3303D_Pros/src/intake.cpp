#include "main.h"
#include "pros/vision.h"

using namespace okapi;

ControllerButton shootBtn = controller[ControllerDigital::L1];
ControllerButton filterBtn = controller[ControllerDigital::L2];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton stopBtn = controller[ControllerDigital::R2];
pros::Vision vision(VISION);
pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(1,
                                                                          5845,
                                                                          6791,
                                                                          6318,
                                                                          -1041,
                                                                          -231,
                                                                          -636,
                                                                          4.2,
                                                                          0);

pros::vision_signature_s_t BLUE_SIG = pros::Vision::signature_from_utility(2, -3245, -2725, -2985, 7143, 7809, 7476, 7.9, 0);
// bool intakeHasBall;

namespace intake
{
    intakeStates currState;

    Motor intakeLeft(INTAKE_L, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor intakeRight(INTAKE_R, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    Timer ballBrakeTimer;

    // bool intakeBlueBall;
    // bool intakeRedBall;

    // bool intakeHasBall()
    // {
    //     if (vision notices ball)
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    // bool intakeBlueBall()
    // {
    //     if (vision notices blue ball)
    //     {
    //         return true;
    //     }
    //     return false;
    // }
    //  bool intakeRedBall()
    // {
    //     if (vision notices blue ball)
    //     {
    //         return true;
    //     }
    //     return false;
    // }
    void
    update()
    {
        pros::vision_object_s_t redRtn = vision.get_by_sig(0, 1);
        pros::vision_object_s_t blueRtn = vision.get_by_sig(0, 2);
        // User input handlers
        if (redRtn.width >= 100)
        {
            currState = redBall;
        }
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
            vision.set_led(COLOR_BLANCHED_ALMOND);
            currState = intakeIn;
        }
        if (stopBtn.changedToPressed())
            currState = notRunning;
        // {
        //     // Engage lift PID if B button is pressed.
        //     currState = filter;
        // }
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
    intake::intakeLeft.moveVelocity(-1 * speed);
    intake::intakeRight.moveVelocity(1 * speed);
}