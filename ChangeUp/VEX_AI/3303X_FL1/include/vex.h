/*---VEX_H---*/
#ifndef VEX_H
#define VEX_H
/*----------------------------------------------------------------------------*/
/*    Module:       vex.h                                                     */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*    Description:  Primary Lib and Config Collection                         */
/*----------------------------------------------------------------------------*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "v5.h"
#include "v5_vcs.h"
#include "vex_global.h"

#include "Configuration/robot-config.h"
#include "Configuration/control-definitions.h"
#include "Configuration/general-definitions.h"

bool ENABLE_AUTON_TEST_BUTTON = false;

#define waitUntil(condition) \
  do{                        \
    wait(5, msec);           \
  }while (!(condition))

#define repeat(iterations) \
  for (int iterator = 0; iterator < iterations; iterator++)

#endif
/*---VEX_H---*/