#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include "nonblock.h"
#include "port_utils.h"


void userInput(microPorts_t *mp,int *end,int *mode,int time, int key){

            switch (key){
                    case ALLEGRO_KEY_ESCAPE:
                            *end = 1;
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
				if (time % 2 == 0){
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