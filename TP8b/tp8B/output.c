#include <stdio.h>
#include "output.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define WHITE al_map_rgb(255,255,255)
#define TAB 20
#define T_ENTER (TITLE_W/2)
#define N_ENTER 20
#define NO_FLAG 0

extern ALLEGRO_FONT *iso_title;
extern ALLEGRO_FONT *iso_text;

void instruct_print(void){
    
    float enter = T_ENTER;

    al_draw_text(iso_title, WHITE, TAB, enter, NO_FLAG, "PORT SIMULATION SOFTWARE");
    enter += T_ENTER;
    al_draw_text(iso_title, WHITE, TAB, enter, NO_FLAG, "=========================");
    enter += T_ENTER + N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "Enter option to set status of LEDs connected to port A.");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "If the entered option is not one of below, nothing happens.");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "Command list:");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "==> Numbers 0 to 7: port bit set corresponding to LED");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "==> B: the switched on LEDs will blink changing the state per 0.5 sec");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "       end blink mode by pressing C or exiting the program");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "==> S: sets all LEDs on");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "==> C: sets all LEDs off");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, TAB, enter, NO_FLAG, "==> ESC: exit program (closing display also works)");
    
    al_flip_display();
    
}
