#include <stdio.h>
#include "output.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

extern ALLEGRO_FONT *iso_title;
extern ALLEGRO_FONT *iso_text;

void showPort(port_t *port){
	
	printf("%c :",port->name);
	if (port->dir != NULL){
		int i;
		for (i = 0;i < port->sz;i++){
			printf("%d",bitGet(port,i));
		}
	}else{
		printf("NULL");
	}
	printf("\n");
}

void instruct_print(void){
    
    float enter = T_ENTER;

    al_draw_text(iso_title, WHITE, TAB, enter, 0, "PORT SIMULATION SOFTWARE");
    enter += T_ENTER;
    al_draw_text(iso_title, WHITE, TAB, enter, 0, "=========================");
    enter += T_ENTER + N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "Enter option to set status of LEDs connected to port A.");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "If the option is not one of below nothing is modified.");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "Command list:");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "==> Numbers 0 to 7: port bit set corresponding to LED");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "==> B: the switched on LEDs will blink changing the state per 1 sec");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "==> S: sets all LEDs on");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "==> C: sets all LEDs off");
    enter += N_ENTER;
    al_draw_text(iso_text, WHITE, 2*TAB, enter, 0, "==> ESC: exit program");
    
    al_flip_display();
    
}
