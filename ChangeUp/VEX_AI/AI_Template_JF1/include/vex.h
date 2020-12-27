/*---VEX_H---*/
#ifndef VEX_H
#define VEX_H
/*----------------------------------------------------------------------------*/
/*    Module:       vex.h                                                     */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      26 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

//V5 Reference: https://api.vexcode.cloud/v5/html/index.html

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "v5.h"
#include "v5_vcs.h"
#include "vex_global.h"

#include "Configuration/robot-config.h"
#include "Configuration/robot-definitions.h"
#include "Configuration/control-definitions.h"
#include "Configuration/general-definitions.h"

#include "AI/AI_Jetson.h"
#include "AI/AI_Robot_Link.h"

#ifdef __cplusplus
extern "C" {
#endif

#define waitUntil(condition) \
  do{                        \
    wait(5, msec);           \
  }while (!(condition))

#define repeat(iterations) \
  for (int iterator = 0; iterator < iterations; iterator++)

extern AI::Jetson      jetson_comm;
extern AI::Robot_Link  robot_link;

extern int dashboardTask( void );
// extern int UsercontrolTask( void );




#ifdef __cplusplus
}
#endif
#endif
/*---VEX_H---*/