#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"
#include "output.h"
#include  "graphic.h"
#include <unistd.h>

void update_display(microPorts_t *mp,int *mode, ALLEGRO_BITMAP *led_ON, ALLEGRO_BITMAP *led_OFF){
    
    show_led(led_ON);
/*
	int i;	
	for (i = 0;i < mp->A.sz;i++){
		printf("%s ",bitGet(&mp->A,i) ? "***" : "   ");
		printf("|");
	}

	printf("\n");
*/
    al_flip_display();
}

void show_led(ALLEGRO_BITMAP *pled){
    
    int src_pled_W = al_get_bitmap_width(pled);
    int src_pled_H = al_get_bitmap_height(pled);
    
    al_draw_scaled_bitmap(pled,0,0,src_pled_W,src_pled_H,X_LED_POS,Y_LED_POS,NEW_LEDSIZE,NEW_LEDSIZE,0);
}