#include <stdio.h>
#include "port_utils.h"
#include "output.h"

#define EXIT 'e'

char get_input(void); // gets user input, only one char, otherwise returns INPUT_ERR

int main(){
	microPorts_t mp;

	int end = 0, config_ok;
	char c;

	int ans = initPorts(&mp);

	if(ans == 1){
		end = 1;
		initError_print();
	}else{
		instruction_print();
	}

	while(!end){

		c = get_input(); // char input

		config_ok = portConfig(&mp.A, c);

		if(!config_ok){
			if(c == EXIT){ // exit soft
				end = TRUE;
			}else{
				printf("Invalid input option\n");
			}
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
