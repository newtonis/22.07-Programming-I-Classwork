#include <stdio.h>
#include "port_utils.h"
#include "output.h"

#define ESCAPE (27)


#define INPUT_ERR -1
#define INPUT_BIT -2
enum {FALSE, TRUE};

char get_input(void); // gets user input, only one char, otherwise returns INPUT_ERR

int main(){
	microPorts_t mp;

	int end = 0;
	char c;
	
	while(!end){

		c = get_input();

		int ans = initPorts(&mp);

		if(('0' <= c)&&(c <= '7')){
			bitSet(&mp.A,(int)(c-'0'));
			showPort(&mp.A);
		}else if(c == 'b'){
			int i = 0;
			int mask_aux=0;
			for(int i;i < 8;i++){
				if(bitGet(&mp.A,i)==1){
					mask_aux |=(1<<(7-i)); 
											// 01110000
				}						   // 
			}
			printf("%d",mask_aux);
			maskToggle(&mp.A,mask_aux);
			showPort(&mp.A);
		}else if(c == 'c'){
			maskOff(&mp.A,0xFF);
			showPort(&mp.A);
		}else if(c == 's'){
			maskOn(&mp.A,0xFF);
			showPort(&mp.A);
		}else if((int)c == ESCAPE){
			end = TRUE;
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