/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       james                                                     */
/*    Created:      Mon Aug 31 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// create instance of jetson class to receive location and other
// data from the Jetson nano
//
ai::jetson  jetson_comms;

/*----------------------------------------------------------------------------*/
// Create a robot_link on PORT1 using the unique name robot_32456_1
// The unique name should probably incorporate the team number
// and be at least 12 characters so as to generate a good hash
//
// The Demo is symetrical, we send the same data and display the same status on both
// manager and worker robots
// Comment out the following definition to build for the worker robot
#define  MANAGER_ROBOT    1

#if defined(MANAGER_ROBOT)
#pragma message("building for the manager")
ai::robot_link       link( PORT11, "robot_32456_1", linkType::manager );
#else
#pragma message("building for the worker")
ai::robot_link       link( PORT11, "robot_32456_1", linkType::worker );
#endif

/*----------------------------------------------------------------------------*/

void spin_right(int speed = 0){
  if(speed != 0){
    Drive_RF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    Drive_RM.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    Drive_RB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    Drive_RF.stop(vex::brakeType::coast); 
    Drive_RM.stop(vex::brakeType::coast); 
    Drive_RB.stop(vex::brakeType::coast);
  }
}

void leftSpin(int speed = 0){
  if(speed != 0){
    Drive_LF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    Drive_LM.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    Drive_LB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }else{
    Drive_LF.stop(vex::brakeType::coast);  
    Drive_LM.stop(vex::brakeType::coast);  
    Drive_LB.stop(vex::brakeType::coast);  
  }
}




bool point_to_heading(float final_x, float final_y){
  float current_x, current_y, current_heading; 
  float diff_x, diff_y, final_heading;

  link.get_local_location(current_x, current_y, current_heading);
  diff_x = (final_x - current_x);
  diff_y = (final_y - current_y);

  final_heading = ((atan2(diff_y, diff_x)*180.0)/PI);

  

  return false;
}

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // local storage for latest data from the Jetson Nano
    static MAP_RECORD       local_map;

    // RUn at about 15Hz
    int32_t loop_time = 66;

    // start the status update display
    thread t1(dashboardTask);

    // print through the controller to the terminal (vexos 1.0.12 is needed)
    // As USB is tied up with Jetson communications we cannot use
    // printf for debug.  If the controller is connected
    // then this can be used as a direct connection to USB on the controller
    // when using VEXcode.
    //
    //FILE *fp = fopen("/dev/serial2","wb");

    while(1) {
        // get last map data
        jetson_comms.get_data( &local_map );

        // set our location to be sent to partner robot
        link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );

        //fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az);

        // request new data        
        jetson_comms.request_map();

        // Allow other tasks to run
        this_thread::sleep_for(loop_time);
    }
}