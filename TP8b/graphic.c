#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"
#include "output.h"
#include  "graphic.h"
#include <unistd.h>

void update_display(microPorts_t *mp,int *mode, ALLEGRO_BITMAP *led_ON, ALLEGRO_BITMAP *led_OFF){
    
    int src_ledON_W = al_get_bitmap_width(led_ON);
    int src_ledON_H = al_get_bitmap_height(led_ON);
    int src_ledOFF_W = al_get_bitmap_width(led_OFF);
    int src_ledOFF_H = al_get_bitmap_height(led_ON);
    
    al_draw_scaled_bitmap(led_ON,0,0,src_ledON_W,src_ledON_H,X_LED_POS,Y_LED_POS,64,64,0);
    al_flip_display();
/*
	int i;	
	for (i = 0;i < mp->A.sz;i++){
		printf("%s ",bitGet(&mp->A,i) ? "***" : "   ");
		printf("|");
	}

	printf("\n");
*/
}