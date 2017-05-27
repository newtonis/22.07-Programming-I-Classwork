#include <stdio.h>
#include "output.h"

extern ALLEGRO_FONT *iso_title;

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
    
    float enter = T_TAB;

    al_draw_text(iso_title, WHITE, TAB, enter, 0, "PORT SIMULATION SOFTWARE");
    enter += T_TAB;
    al_draw_text(iso_title, WHITE, TAB, enter, 0, "=========================");
    enter += T_TAB;
    /*
    printf("Enter option to set status of LEDs connected to port A.\n");
    printf("If the option is not one of below nothing is modified.\n");
    printf("Command list:\n");
    printf("==> numbers 0 to 7: port bit set corresponding to LED\n");
    printf("==> b: the switched on LEDs will blink changing the state per 1 sec\n");
    printf("==> s: sets all LEDs on\n");
    printf("==> c: sets all LEDs off\n");
    printf("==> Esc key: terminates the program\n");
    printf("Enter option:\n\n");*/
    
    al_flip_display();
    
}
