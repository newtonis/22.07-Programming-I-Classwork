#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include "nonblock.h"
#include "port_utils.h"


void userInput(microPorts_t *mp,int *end,int *mode,int time, int key){
	int i = kbhit();
        

	if (i != 0){
		char c = fgetc(stdin);
		switch (c){
			case 27:
				*end = 1;
			break;
			case 'c':
			case 'C':
				*mode = NORMAL;
				maskOff(&mp->B,0xFF); // make all leds shut off
			break;
			case 's':
			case 'S':
				maskOn(&mp->B,0xFF);
			break;
			case 'b':
			case 'B':
				*mode = BLINK;
			break;
		}
		if (c >= '0' && c <= '7'){
			int led = c - '0';
			bitSet(&mp->B,led);
		}
	}
	fsmUpdate(mode,mp,time);
	
}
void fsmUpdate(int *mode,microPorts_t *mp,long time){
	
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