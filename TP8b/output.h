////////////////////
// OUTPUT LIBRARY //
// ============== //////////////////////
// Standard output functions to guide //
// the user through the program.      //
////////////////////////////////////////
#ifndef OUTPUT_H
#define OUTPUT_H

#define SCREEN_W 640
#define SCREEN_H 480

#include "port_utils.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define WHITE al_map_rgb(255,255,255)
#define TITLE_W 30
#define TAB 10
#define T_TAB (TITLE_W/2)

// showPort: prints in the standard out the new state of
// port bits if modified by hand (not used for led configuration program).
void showPort(port_t *port);

// instruction_print: prints in the standard out a text with the 
// valid commands.
void instruct_print(void);

#endif // OUTPUT_H