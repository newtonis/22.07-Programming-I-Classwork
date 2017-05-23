#include <stdio.h>
#include "output.h"

void showPort(port_t *port){
	
	printf("%c :",port->name);
	if (port->dir != NULL){
		int i;
		for (i = 0;i < port->sz;i++){
			printf("%d",bitGet(port,i));
		}
	}else{
		printf("NULL");
	}
	printf("\n");
}


void instruction_print(void){
	printf("PORT SIMULATION SOFTWARE\n");
	printf("========================\n\n");

	printf("Enter port to configure.\n");
	printf("Command list:\n");
	printf("==> A: port A\n");
	printf("==> B: port B\n");
	printf("==> D: port D\n");
	printf("==> e: terminates the program\n");
	printf("Enter choice: ");
}

void initError_print(void){

	printf("PORT SIMULATION SOFTWARE\n");
	printf("========================\n\n");

	printf("Error at configuring ports. Program terminated.-\n\n");
}

void portSel_print(void){

	printf("Enter option to set status of LEDs connected to port A\n");
	printf("Command list:\n");
	printf("==> numbers 0 to 7: port bit set corresponding to LED\n");
	printf("==> b: the switched on LEDs will blink\n");
	printf("==> s: sets all LEDs on\n");
	printf("==> c: sets all LEDs off\n");
	printf("==> e: terminates the program\n");
	printf("Enter choice: ");

}