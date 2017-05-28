/////////////////////
// GRAPHIC LIBRARY //
// =============== /////////////////////////
// Functions for updating standard output // 
// with the new status of the leds.       //
////////////////////////////////////////////
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "port_utils.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

// update_display: refresh the information shown in the standard out
// acording to the selected mode.
// 	Input: pointer to ports structure, pointer to mode, pointer to led ON image, pointer to led OFF image
// 	Output: (none)
void update_display(microPorts_t *mp,int *mode, ALLEGRO_BITMAP *led_ON, ALLEGRO_BITMAP *led_OFF);

#endif // GRAPHIC_H