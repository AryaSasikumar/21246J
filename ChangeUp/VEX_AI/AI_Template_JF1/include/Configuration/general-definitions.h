/*---GENERAL_DEFINITIONS_H---*/
#ifndef GENERAL_DEFINITIONS_H
#define GENERAL_DEFINITIONS_H
/*----------------------------------------------------------------------------*/
/*    Module:       general-definitions.h                                     */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/

/*---Status-Returns---*/
#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif



#define ENABLE_AUTON_TEST_BUTTON

enum PID_BASE_MODE {PID_DRIVE, PID_TURN};
enum turn_t {RIGHT, LEFT};


/*---Other---*/
#define FOREVER true

#ifndef PI
    #define PI 3.14159
#endif



// #define ENABLE_AUTON_TEST_BUTTON
// //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
// ENABLE_AUTON_TEST_BUTTON = false;// ENABLE FOR Y-BUTTON AS AUTON TEST BUTTON!//
// //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

#endif /*---GENERAL_DEFINITIONS_H---*/