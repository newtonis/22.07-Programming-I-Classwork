////////////////////
// OUTPUT LIBRARY //
// ============== //////////////////////
// Standard output functions to guide //
// the user through the program.      //
////////////////////////////////////////
#ifndef OUTPUT_H
#define OUTPUT_H

// Allegro libraries
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FPS 60.0

#define SCREEN_W 640
#define SCREEN_H 380

#define TITLE_W 30
#define TEXT_W 20

typedef struct allegro_utils allegro_utils_t; // struct type declared

struct allegro_utils{ // struct type for allegro stuff
    
    ALLEGRO_DISPLAY *disp_a;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_TIMER *timer_a;
    ALLEGRO_BITMAP *ledON;
    ALLEGRO_BITMAP *ledOFF;
    ALLEGRO_FONT *iso_title;
    ALLEGRO_FONT *iso_text;
    
    FILE *log; // program event log
    
};


// instruction_print: prints in the standard out a text with the 
// valid commands.
//  Input/Output: (none)
void instruct_print(ALLEGRO_FONT *titleF, ALLEGRO_FONT *textF);

int init_allegro_soft(allegro_utils_t *simulator);

#endif // OUTPUT_H