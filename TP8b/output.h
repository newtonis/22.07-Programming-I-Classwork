////////////////////
// OUTPUT LIBRARY //
// ============== //////////////////////
// Standard output functions to guide //
// the user through the program.      //
////////////////////////////////////////
#ifndef OUTPUT_H
#define OUTPUT_H

#include "port_utils.h"

// showPort: prints in the standard out the new state of
// port bits if modified by hand (not used for led configuration program).
void showPort(port_t *port);

// instruction_print: prints in the standard out a text with the 
// valid commands.
void instruct_print(void);

#endif // OUTPUT_H