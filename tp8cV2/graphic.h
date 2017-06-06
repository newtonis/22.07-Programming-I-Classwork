/////////////////////
// GRAPHIC LIBRARY //
// =============== /////////////////////////
// Functions for updating standard output // 
// with the new status of the leds.       //
////////////////////////////////////////////
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "port_utils.h"

// update_display: refresh the information shown in the standard out
// acording to the selected mode.
// 	Input: pointer to ports structure, pointer to mode
// 	Output: (none)
void update_display(microPorts_t *mp,int *mode);

#endif // GRAPHIC_H