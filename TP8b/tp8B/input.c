#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"

#include <allegro5/allegro5.h>

// fsmUpdate: modifies blinking for the leds.
// 	Input: pointer to mode, pointer to ports, long int of time for blinking mode.
// 	Output: (none)
static void fsmUpdate(int *mode,microPorts_t *mp,int time);

void userInput(microPorts_t *mp,int *end,int *mode,int time, int key){

            switch (key){
                    case ALLEGRO_KEY_ESCAPE:
                            *end = TRUE;
                    break;
                   
                    case ALLEGRO_KEY_C:
                            *mode = NORMAL;
                            maskOff(&mp->B,0xFF); // make all leds shut off
                    break;
                   
                    case ALLEGRO_KEY_S:
                            maskOn(&mp->B,0xFF); 
                    break;
                    
                    case ALLEGRO_KEY_B:
                            *mode = BLINK;
                    break;
            }
            if (key >= ALLEGRO_KEY_0 && key <= ALLEGRO_KEY_7){
                    int led = key - ALLEGRO_KEY_0;
                    bitSet(&mp->B,led);
            }
	
	fsmUpdate(mode,mp,time);
	
}
void fsmUpdate(int *mode,microPorts_t *mp,int time){
	
		//mp->A = mp->B
	int i;
	for (i = 0;i < mp->A.sz;i++){
		if ( bitGet(&mp->B,i) ){
			if (*mode == NORMAL){
				bitSet(&mp->A, i );
			}else if(*mode == BLINK){
				if (time % 2 == 0){ // time switches between 0 and 1
					bitSet(&mp->A, i );
				}else{
					bitClr(&mp->A, i);
				}
			}
		}else{
			bitClr(&mp->A, i);
		}
	}
	
}