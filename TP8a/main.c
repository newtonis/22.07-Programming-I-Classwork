#include <stdio.h>
#include "port_utils.h"
#include "output.h"

#define ESC (27)

#define INPUT_ERR -1
#define INPUT_BIT -2
#define ALL_BITS_MASK 0xFF
enum {FALSE, TRUE};

char get_input(void); // gets user input, only one char, otherwise returns INPUT_ERR

void instruction_print(void);

int main(){
	microPorts_t mp;

	int end = 0;
	char c;
	
	instruction_print();

	while(!end){

		c = get_input();

		int ans = initPorts(&mp);

		if(('0' <= c ) && ( c <= '7')){ // Bit set to port
			bitSet(&mp.A,(int)(c-'0'));
			printf("Status port ");
			showPort(&mp.A);
		}else if(c == 'b'){ // Blink bit
			int i = 0;
			int mask_aux = 0;
			for( int i ; i < sizeof(uint8_t) ; i++ ){
				if( bitGet (&mp.A,i) == 1 ){
					mask_aux |= 1<<i ;
				}						   
			}
			printf("Status port ");
			printf("%d",mask_aux);
			maskToggle(&mp.A,mask_aux);
			showPort(&mp.A);
		}else if(c == 'c'){ // Turn off bits
			maskOff(&mp.A,ALL_BITS_MASK);
			printf("Status port ");
			showPort(&mp.A);
		}else if(c == 's'){ // Set all bits 
			maskOn(&mp.A,ALL_BITS_MASK);
			printf("Status port ");
			showPort(&mp.A);
		}else if((int)c == ESC){ // Exit soft
			end = TRUE;
		}else{
			printf("Invalid input option\n");
		}

	}
/*
*/
	endPorts(&mp); /// free ports memory
	
}

char get_input(void){

	unsigned int i = 0;

	char c, in_char;

	while ( (c = getchar()) != '\n'){
		i++;
		in_char = c;
	}

	if(i != 1)	
		in_char = INPUT_ERR;
	
	return in_char;
}
