#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "port_utils.h"
#include "output.h"
#include "graphic.h"

#define N_LEDS 8
#define NEW_LEDSIZE 64

#define X_LED_POS 20
#define Y_LED_POS 270

#define LED_STEP ((SCREEN_W - (2*X_LED_POS) - (N_LEDS*64))/(N_LEDS -1))

static void show_led(ALLEGRO_BITMAP *pled, int led_index);

void update_display(microPorts_t *mp,int *mode, ALLEGRO_BITMAP *led_ON, ALLEGRO_BITMAP *led_OFF){

    int i;	
    for (i = 0;i < mp->A.sz; i++){
        if(bitGet(&mp->A,i)){
            show_led(led_ON, i);
        }else{
            show_led(led_OFF, i);
        }
    }

    al_flip_display();
}

void show_led(ALLEGRO_BITMAP *pled, int led_index){
    
    int src_pled_W = al_get_bitmap_width(pled);
    int src_pled_H = al_get_bitmap_height(pled);
    
    int X_TAB = X_LED_POS + (led_index*(NEW_LEDSIZE + LED_STEP));
    
    al_draw_scaled_bitmap(pled,0,0,src_pled_W,src_pled_H,X_TAB,Y_LED_POS,NEW_LEDSIZE,NEW_LEDSIZE,0);
}