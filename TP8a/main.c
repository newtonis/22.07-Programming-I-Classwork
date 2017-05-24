#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"
#include "output.h"

int main(){
	microPorts_t mp;

	int config_ok, global_state = 1;
	char c, port_chose;

	int ans = initPorts(&mp);

	if(ans == 1){
		global_state = 0;
		initError_print();
	}else{
		instruction_print();
		printf("Enter choice: ");
	}

	while(global_state){

		if(global_state == 1){

			port_chose = get_input();

			switch(port_chose){
				case 'A': case 'B': case 'D':
				case 'a': case 'b': case 'd': 
					global_state = 2;
					system("clear");
					bitConfig_print(port_chose);
					printf("Enter choice: ");
				break;
				case 'L': case 'l':
					global_state = 3;
					system("clear");
					portSel_print();	
					printf("Enter choice: ");
				break;
				case EXIT:
					end = TRUE;
					global_state = 0;
				break;
				default:
					system("clear");
					instruction_print();
					printf("Invalid port choice. Type again:\n");
				break;
			}
		}	

		if((global_state == 2)||(global_state == 3)){

			c = get_input(); // char input

			switch(port_chose){
				case 'L': case 'l':
					config_ok = portConfig(&mp.A, c);
				break;
				case 'A': case 'a':
					config_ok = bit_setup(&mp.A, c)
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
					global_state = 0;
				}
				else if(global_state == 3){
					system("clear");
					portSel_print();
					printf("Invalid input option. Type again:\n");
				}
				else if(global_state == 2){
					system("clear");
					bitConfig_print(port_chose);
					printf("Invalid input option. Type again:\n");
				}
			}
		}

	}

	endPorts(&mp); /// free ports memory
	
}
