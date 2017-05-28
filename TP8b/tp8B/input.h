///////////////////
// INPUT LIBRARY //
// ============= ////////////////////
// Funtions for port status update //
// according to user input.        //
/////////////////////////////////////
#ifndef INPUT_H
#define INPUT_H

#include "port_utils.h"

enum {NORMAL , BLINK};

// userInput: process keyboard input. If the option is incorrect,
// nothing is modified.
// 	Input: pointer to ports struct, pointer to end program, 
//         pointer to mode, time reference for blinking mode, key pressed
// 	Output: (none)
void userInput(microPorts_t *mp,int *end,int *mode,int time, int key);

#endif