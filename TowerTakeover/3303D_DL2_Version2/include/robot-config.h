using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern smartdrive Drivetrain;
extern motor liftA;
extern motor liftB;
extern motor rightIntake;
extern motor leftIntake;
extern encoder baseEncoder;
extern gyro Gyro;
extern bumper Bumper;
extern pot liftPot;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );