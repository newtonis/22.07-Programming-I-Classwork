#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"
#include "output.h"

#define EXIT 'e'

char get_input(void); // gets user input, only one char, otherwise returns INPUT_ERR

int main(){
	microPorts_t mp;

	int end = 0, config_ok, valid_in = 0, valid_set = 0;
	char c, port_chose;

	int ans = initPorts(&mp);

	if(ans == 1){
		end = 1;
		initError_print();
	}else{
		instruction_print();
		printf("Enter choice: ");
	}

	while(!end){

		while(!valid_in){

			port_chose = get_input();

			switch(port_chose){
				case 'A': case 'B': case 'D':
				case 'a': case 'b': case 'd': 
					valid_in = 1;
					system("clear");
					bitConfig_print(port_chose);
					printf("Enter choice: ");
				break;
				case 'L': case 'l':
					valid_in = 1;
					system("clear");
					portSel_print();	
					printf("Enter choice: ");
				break;
				case EXIT:
					end = TRUE;
					valid_in = 1;
					valid_set = 1;
				break;
				default:
					system("clear");
					instruction_print();
					printf("Invalid port choice. Type again:\n");
				break;
			}
		}

		if(valid_in)
			

		while(!valid_set){

			c = get_input(); // char input

			switch(port_chose){
				case 'L': case 'l':
					config_ok = portConfig(&mp.A, c);
				break;
				case 'A': case 'a':
					// make int function
				break;
				case 'B': case 'b':
					// make int function
				break;
				case 'D': case 'd':
					// make int funciton
				break;
			}

			if(!config_ok){
				if(c == EXIT){ // exit soft
					end = TRUE;
					valid_set = 1;
				}else{
					system("clear");
					portSel_print();
					printf("Invalid input option. Type again:\n");
				}
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
