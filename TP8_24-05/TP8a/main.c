#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"
#include "output.h"
//////////////////////////////////////////////////
//// TP8a - STRUCT, UNION, BITFIELD - GROUP 3 ////
//// ---------------------------------------- ////
//// ==> MESTANZA, Joaquin                    ////
//// ==> NOWIK, Ariel                         ////
//// ==> REGUEIRA, Marcelo   	  			  ///////////////////////////
//// --------------------------------------------------------------- ////
//// The following code works as an emulator for ports named A B D,	 ////
//// of 8, 8, and 16 bits each. The user can do operations with      ////
//// particular bits of setting, clearing and getting status.        ////
//// Also setting, clearing and toggle mask operations can be made,  ////
//// but with predefined masks in port_utils.h.                      ////
//// ==> output.h/output.c: functions to guide the user through the  ////
////     program.                                                    ////
//// ==> port_utils.h/port_utils.c: internal functions for woking    ////
////     with the ports.                             				 ////
//// --------------------------------------------------------------- ////
/////////////////////////////////////////////////////////////////////////
int main(){
	microPorts_t mp;

	int config_ok, global_state = 1;
	char c, port_chose;

	int ans = initPorts(&mp);

	system("clear");

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
				case 'A': case 'B': case 'D': // port select
				case 'a': case 'b': case 'd': 
					global_state = 2;
					system("clear");
					bitConfig_print(port_chose);
					printf("Enter choice: ");
				break;
				case EXIT: // terminate program
					global_state = 0;
				break;
				default: // invalid!
					system("clear");
					instruction_print();
					printf("Invalid port choice. Type again: ");
				break;
			}
		}	

		if(global_state == 2){

			c = get_input(); // char input

			switch(port_chose){
				case 'A': case 'a':
					config_ok = bit_setup(&mp.A, c, 'A');
				break;
				case 'B': case 'b':
					config_ok = bit_setup(&mp.B, c, 'B');
				break;
				case 'D': case 'd':
					config_ok = bit_setup(&mp.D, c, 'D');
				break;
			}

			if(!config_ok){
				if(c == EXIT){ // exit soft
					global_state = 0;
				}
				else if(global_state == 2){
					system("clear");
					bitConfig_print(port_chose);
					printf("Invalid input option. Type again: ");
				}
			}else{
				global_state = 1;
				printf("Press ENTER to return to main menu\n");
				port_chose = get_input();
				system("clear");
				instruction_print();
				printf("Enter choice: ");
			}
		}

	}

	endPorts(&mp); /// free ports memory
	
}
