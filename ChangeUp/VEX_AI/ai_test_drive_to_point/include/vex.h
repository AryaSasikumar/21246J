/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "ai_jetson.h"
#include "ai_robot_link.h"

#include "Subsystems/Drive.h"

#include "robot-config.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

extern ai::jetson      jetson_comms;
extern ai::robot_link  link;

extern int dashboardTask( void );

#ifndef PI
  #define PI 3.14159265
#endif

motor Drive_LF = motor(PORT10, ratio6_1, false);
motor Drive_LM = motor(PORT5, ratio6_1, false);
motor Drive_LB = motor(PORT1, ratio6_1, false);

motor Drive_RF = motor(PORT20, ratio6_1, false);
motor Drive_RM = motor(PORT15, ratio6_1, false);
motor Drive_RB = motor(PORT12, ratio6_1, false);
