///////////////////
// INPUT LIBRARY //
// ============= ////////////////////
// Funtions for port status update //
// according to user input.        //
/////////////////////////////////////
#ifndef INPUT_H
#define INPUT_H

#include "port_utils.h"
enum {NORMAL , BLINK };

// userInput: process keyboard input. If the option is incorrect,
// nothing is modified.
// 	Input: pointer to ports struct, pointer to end program, 
//         pointer to mode, long int of time for blinking mode.
// 	Output: (none)
void userInput(microPorts_t *mp,int *end,int *mode,long time);

// fsmUpdate: modifies blinking for the leds.
// 	Input: pointer to mode, pointer to ports, long int of time for blinking mode.
// 	Output: (none)
static void fsmUpdate(int *mode,microPorts_t *mp,long time);

#endif