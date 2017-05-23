#include <stdio.h>
#include "port_utils.h"
#include "output.h"

#define ESCAPE (27)


#define INPUT_ERR -1
#define INPUT_BIT -2
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

		if(('0' <= c)&&(c <= '7')){ // Bit set to port
			bitSet(&mp.A,(int)(c-'0'));
			printf("Status port ");
			showPort(&mp.A);
		}else if(c == 'b'){ // Blink bit
			int i = 0;
			int mask_aux=0;
			for(int i;i < 8;i++){
				if(bitGet(&mp.A,i)==1){
					mask_aux |=(1<<(7-i)); 
											// 01110000
				}						   // 
			}
			printf("Status port ");
			printf("%d",mask_aux);
			maskToggle(&mp.A,mask_aux);
			showPort(&mp.A);
		}else if(c == 'c'){ // Turn off bits
			maskOff(&mp.A,0xFF);
			printf("Status port ");
			showPort(&mp.A);
		}else if(c == 's'){ // Set all bits 
			maskOn(&mp.A,0xFF);
			printf("Status port ");
			showPort(&mp.A);
		}else if((int)c == ESCAPE){ // Exit soft
			end = TRUE;
		}else{
			printf("Invalid input option\n");
		}

	}

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

void instruction_print(void){

	printf("PORT SIMULATION SOFTWARE\n");
	printf("========================\n\n");

	printf("Enter option to set status of LEDs connected to port A\n");
	printf("Command list:\n");
	printf("==> numbers 0 to 7: port bit set corresponding to LED\n");
	printf("==> b: the switched on LEDs will blink\n");
	printf("==> s: sets all LEDs on\n");
	printf("==> c: sets all LEDs off\n");
	printf("==> Esc: terminates the program\n");
	printf("Enter choice: ");
}