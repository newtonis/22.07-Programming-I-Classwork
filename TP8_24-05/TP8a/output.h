////////////////////
// OUTPUT LIBRARY //
// ============== ////////////////////
// Functions for interact with user //
// at the standard out.			    //
//////////////////////////////////////
#ifndef OUTPUT_H
#define OUTPUT_H

#include "port_utils.h"

// showPort: prints in the standard out the new state of
// port bits if modified by hand (not used for led configuration program).
// 	Input: pointer to port
//  Output: (none)
void showPort(port_t *port);

// instruction_print: prints in the standard out a text with the 
// valid commands.
// 	Input/Output: (none)
void instruction_print(void);

// bitConfig_print: prints a set of valid commands to work with the port bits.
// 	Input: letter of the port
//  Output: (none)
void bitConfig_print(char port);

// initError_print: prints in the standard out a message of error in the 
// initialization of the ports. Next, the program aborts.
// 	Input/Output: (none)
void initError_print(void);

#endif // OUTPUT_H