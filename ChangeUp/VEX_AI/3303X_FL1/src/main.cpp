/*---MAIN_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

/*---Configuration-Includes---*/
#include "vex.h"
/*-------User-Includes-------*/
#include "Robot/Robot.h"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

Robot myRobot;

int rc_auto_loop_task() {
  while (FOREVER){
    myRobot.base.user_control_tank_drive();
  }
  return 0;
}

// create instance of jetson class to receive location and other
// data from the Jetson nano
//
//AI::Jetson  jetson_comms;

/*----------------------------------------------------------------------------*/
// Create a robot_link on PORT1 using the unique name robot_32456_1
// The unique name should probably incorporate the team number
// and be at least 12 characters so as to generate a good hash
//
// The Demo is symetrical, we send the same data and display the same status on both
// manager and worker robots
// Comment out the following definition to build for the worker robot
// #define  MANAGER_ROBOT    1

// #if defined(MANAGER_ROBOT)
// #pragma message("building for the manager")
// AI::Robot_Link link( PORT11, "robot_32456_1", vex::linkType::manager );
// #else
// #pragma message("building for the worker")
// AI::Robot_Link link( PORT11, "robot_32456_1", vex::linkType::worker );
// #endif
=======
>>>>>>> parent of edac948... Now Compiling In VEXcode
=======
>>>>>>> parent of edac948... Now Compiling In VEXcode
=======
>>>>>>> parent of edac948... Now Compiling In VEXcode


vex::competition Competition;

/*---Pre-Autonomous---*/
void pre_auton(void){ vexcodeInit(); }
/*-----Autonomous-----*/
void autonomous(void){ /*TODO*/ }
/*----User-Control----*/
void usercontrol(void){
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
  ENABLE_AUTON_TEST_BUTTON = false;// ENABLE FOR Y-BUTTON AS AUTON TEST BUTTON!//
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
  vex::task drive_task(rc_auto_loop_task);
  while(FOREVER){ wait(20, vex::msec); }// Sleep to prevent wasted resources.
}

int main(){
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while(FOREVER){
    //Use this loop for printf testing. EX: printf("Sensor Name: %d\n", sensor.value());
    vex::task::sleep(100);
  }
}

/*---MAIN_CPP---*/



// #include "vex.h"

// using namespace vex;

// create instance of jetson class to receive location and other
// data from the Jetson nano
// //
// ai::jetson  jetson_comms;

/*----------------------------------------------------------------------------*/
// Create a robot_link on PORT1 using the unique name robot_32456_1
// The unique name should probably incorporate the team number
// and be at least 12 characters so as to generate a good hash
//
// The Demo is symetrical, we send the same data and display the same status on both
// manager and worker robots
// Comment out the following definition to build for the worker robot
// #define  MANAGER_ROBOT    1

// #if defined(MANAGER_ROBOT)
// #pragma message("building for the manager")
// ai::robot_link       link( PORT11, "robot_32456_1", linkType::manager );
// #else
// #pragma message("building for the worker")
// ai::robot_link       link( PORT11, "robot_32456_1", linkType::worker );
// #endif


/*----------------------------------------------------------------------------*/

// int main() {
//     // Initializing Robot Configuration. DO NOT REMOVE!
//     vexcodeInit();

//     // local storage for latest data from the Jetson Nano
//     static MAP_RECORD       local_map;

//     // RUn at about 15Hz
//     int32_t loop_time = 66;

//     // start the status update display


//     thread t1(dashboardTask);
//     thread t2(UsercontrolTask);
//     // print through the controller to the terminal (vexos 1.0.12 is needed)
//     // As USB is tied up with Jetson communications we cannot use
//     // printf for debug.  If the controller is connected
//     // then this can be used as a direct connection to USB on the controller
//     // when using VEXcode.
//     //
//     //FILE *fp = fopen("/dev/serial2","wb");
//     while(1) {
//         // get last map data
//         jetson_comms.get_data( &local_map );

//         // set our location to be sent to partner robot
//         link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );

//         //fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az  );

//         // request new data        
//         jetson_comms.request_map();

//         // Allow other tasks to run
//         this_thread::sleep_for(loop_time);
//     }
// }