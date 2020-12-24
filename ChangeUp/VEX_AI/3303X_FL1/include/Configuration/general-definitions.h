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

enum direction_t {FORWARDS, BACKWARDS};
enum turn_t {RIGHT, LEFT};

/*---Other---*/
#define FOREVER true


#endif
/*---GENERAL_DEFINITIONS_H---*/