/////////////////////
// GRAPHIC LIBRARY //
// =============== /////////////////////////
// Functions for updating standard output // 
// with the new status of the leds.       //
////////////////////////////////////////////
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "port_utils.h"

#define N_LEDS 8
#define NEW_LEDSIZE 64

#define X_LED_POS 20
#define Y_LED_POS 250

#define LED_STEP ((640 - (2*X_LED_POS) - (N_LEDS*64))/(N_LEDS -1)) // for SCREEN_W = 640

void update_display(microPorts_t *mp,int *mode, ALLEGRO_BITMAP *led_ON, ALLEGRO_BITMAP *led_OFF);

void show_led(ALLEGRO_BITMAP *pled, int led_index);

#endif // GRAPHIC_H