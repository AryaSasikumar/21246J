/*---MAIN_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

/*---Configuration-Includes---*/
#include "vex.h"
/*-------User-Includes-------*/
#include "Robot.h"

AI::Jetson jetson_comm;

#define MANAGER_ROBOT
#if defined(MANAGER_ROBOT)
AI::Robot_Link robot_link(vex::PORT12, "ai_3303D_manager", vex::linkType::manager);
#else
AI::Robot_Link robot_link(vex::PORT12, "ai_3303D_worker", vex::linkType::worker);
#endif

static MAP_RECORD local_map;

int32_t loop_time = 66; //Run at about 15Hz

Robot thisRobot;

int rc_auto_loop_task() {
  while (FOREVER){
    thisRobot.base.user_control_tank_drive();
    if(UP_BUTTON){
      thisRobot.change_heading(0, 75);
    }
    if(DOWN_BUTTON){
      thisRobot.change_heading(180, 75);
    }
    if(LEFT_BUTTON){
      thisRobot.change_heading(-90, 75);
    }
    if(RIGHT_BUTTON){
      thisRobot.change_heading(90, 75);
    }


    if(TESTING_BUTTON1){
      thisRobot.change_position(600.0, 600.0, 100);
    }
    if(TESTING_BUTTON2){
      FILE *fp = fopen("/dev/serial2","wb");
      fprintf(fp, "Current Heading: %.5f\n", local_map.pos.az * 180.0/PI);
      fprintf(fp, "Current X: %.5f | Currnet Y: %.5f\n\n", local_map.pos.x, local_map.pos.y);
      fclose(fp);
    }
  }
  return 0;
}

vex::competition Competition;

/*---Pre-Autonomous---*/
void pre_auton(void){ vexcodeInit(); }
/*-----Autonomous-----*/
void autonomous(void){ /*TODO*/ }
/*----User-Control----*/

void usercontrol(void){
  vex::task drive_task(rc_auto_loop_task);
  while(FOREVER){ wait(20, vex::msec); }// Sleep to prevent wasted resources.
}

int main(){
  //Competition.autonomous(autonomous);
  //Competition.drivercontrol(usercontrol);
  //pre_auton();
  //start the status update display
  vex::thread t1(dashboardTask);
  vex::thread t2(rc_auto_loop_task);
  /* 
    Print through the controller to the terminal (vexos 1.0.12 is needed)
    As USB is tied up with Jetson communications we cannot use printf for debug.  
    If the controller is connected then this can be used as a direct connection 
    to USB on the controller when using VEXcode.
  */
  //FILE *fp = fopen("/dev/serial2","wb");
  while(FOREVER){
    jetson_comm.get_data( &local_map );//Get last map data
    robot_link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );//Set our location to be sent to partner robot
    thisRobot.refresh_position( &local_map );
    //fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az );
    jetson_comm.request_map(); //Request new data   
    vex::this_thread::sleep_for(loop_time); //Allow other tasks to run
  }
}
/*---MAIN_CPP---*/
