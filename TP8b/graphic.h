/////////////////////
// GRAPHIC LIBRARY //
// =============== /////////////////////////
// Functions for updating standard output // 
// with the new status of the leds.       //
////////////////////////////////////////////
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "port_utils.h"

#define X_LED_POS 20
#define Y_LED_POS 250

void update_display(microPorts_t *mp,int *mode, ALLEGRO_BITMAP *led_ON, ALLEGRO_BITMAP *led_OFF);

#endif // GRAPHIC_H