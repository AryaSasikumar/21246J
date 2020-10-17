#include "main.h"

using namespace okapi;

namespace drive
{

    driveStates currState;

    Motor driveL1(DRIVE_L1, false, AbstractMotor::gearset::blue);
    Motor driveL2(DRIVE_L2, true, AbstractMotor::gearset::blue);
    Motor driveL3(DRIVE_L3, False, AbstractMotor::gearset::blue);
    Motor driveR1(DRIVE_R1, false, AbstractMotor::gearset::blue);
    Motor driveR2(DRIVE_R2, true, AbstractMotor::gearset::blue);
    Motor driveR3(DRIVE_R3, false, AbstractMotor::gearset::blue);

    TimeUtil chassisUtil = TimeUtilFactory::withSettledUtilParams(50, 5, 100_ms);
    TimeUtil profiledUtil = TimeUtilFactory::withSettledUtilParams(50, 5, 100_ms);

    okapi::MotorGroup leftMotorGroup({DRIVE_L1,
                                      DRIVE_L2,
                                      DRIVE_L3});
    okapi::MotorGroup rightMotorGroup({DRIVE_R1, DRIVE_R2, DRIVE_R3});

    AsyncPosIntegratedController leftController(std::shared_ptr<MotorGroup>(&leftMotorGroup), chassisUtil);
    AsyncPosIntegratedController rightController(std::shared_ptr<MotorGroup>(&rightMotorGroup), chassisUtil);

    SkidSteerModel integratedChassisModel = ChassisModelFactory::create({DRIVE_L1, DRIVE_L2, DRIVE_L3}, {-DRIVE_R1, -DRIVE_R2, -DRIVE_R3}, 300);
    SkidSteerModel discreteChassisModel = ChassisModelFactory::create({DRIVE_L1, DRIVE_L2, DRIVE_L3}, {-DRIVE_R1, -DRIVE_R2, -DRIVE_R3}, 300);
    // ChassisScales integratedScale = std_initializer_list<ChassisScales>(4.125_in, 13.273906_in);
    // ChassisScales discreteScale = std_initializer_list<ChassisScales>(2.75_in, 7.402083_in);

    ChassisScales drivenWheelsScales = {3.25_in, 12.676583_in};

    ChassisControllerIntegrated chassisController(
        chassisUtil,
        std::shared_ptr<SkidSteerModel>(&integratedChassisModel),
        std::unique_ptr<AsyncPosIntegratedController>(&leftController),
        std::unique_ptr<AsyncPosIntegratedController>(&rightController),
        AbstractMotor::gearset::blue, drivenWheelsScales);

    AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
        // 1.05, // Maximum linear velocity of the Chassis in m/s
        // 1.5, // Maximum linear acceleration of the Chassis in m/s/s
        // 5.0, // Maximum linear jerk of the Chassis in m/s/s/s
        1,
        2,
        10.0,
        chassisController // Chassis Controller
    );

    void update()
    {
        // currState = notRunning;
        if (abs(controller.getAnalog(ControllerAnalog::leftY)) > joyDeadband ||
            abs(controller.getAnalog(ControllerAnalog::rightY)) > joyDeadband)
        {
            currState = running; // begin running drive once small threshold on joystick is reached
        }
        // currState = autoAim;
    }

    void act(void *)
    {

        // pros::delay(500);
        // vision::vis.set_exposure(150);

        while (true)
        {
            // largestObjX = visionFilter.filter(vision::reader.get(0).x);

            // pros::lcd::print(0, "%f", drive::driveL1.getPosition());
            // pros::lcd::print(1, "%c", drive::currState);
            // printf("x: %i\n", largestObjX);

            switch (currState)
            {
            case notRunning: // the drive should not be moving; brake
                chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
                chassisController.stop();
                break;

            case running: // the drive moves according to joysticks
                chassisController.tank(
                    controller.getAnalog(ControllerAnalog::leftY) * 1.0,
                    controller.getAnalog(ControllerAnalog::rightY) * 1.0,
                    joyDeadband * 1.0);
                currState = notRunning;
                break;

            case yield: // for macro in order to take direct control of drive
                break;
            }
            pros::delay(10);
        }
    }

    // Helper function to facilitate turning during auton
} // namespace drive

// Remove path to clear up memory
void removePaths(std::string path1)
{
    drive::profileController.removePath(path1);
}

// Remove 2 paths at once to clear up memory
void removePaths(std::string path1, std::string path2)
{
    drive::profileController.removePath(path1);
    drive::profileController.removePath(path2);
}