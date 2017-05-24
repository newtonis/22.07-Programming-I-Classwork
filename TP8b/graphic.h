/////////////////////
// GRAPHIC LIBRARY //
// =============== /////////////////////////
// Functions for updating standard output // 
// with the new status of the leds.       //
////////////////////////////////////////////
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "port_utils.h"

void update_display(microPorts_t *mp,int *mode);

#endif // GRAPHIC_H