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
	printf("==> A/a: port A\n");
	printf("==> B/b: port B\n");
	printf("==> D/d: port D\n");
	printf("==> L/l: LED configuration\n");
	printf("==> e: terminates the program\n\n");
}

void initError_print(void){

	printf("PORT SIMULATION SOFTWARE\n");
	printf("========================\n\n");

	printf("Error at configuring ports. Program terminated.-\n\n");
}

void portSel_print(void){

	printf("PORT SIMULATION SOFTWARE\n");
	printf("========================\n\n");

	printf("Enter option to set status of LEDs connected to port A\n");
	printf("Command list:\n");
	printf("==> numbers 0 to 7: port bit set corresponding to LED\n");
	printf("==> b: the switched on LEDs will blink\n");
	printf("==> s: sets all LEDs on\n");
	printf("==> c: sets all LEDs off\n");
	printf("==> e: terminates the program\n\n");
}

void bitConfig_print(char port){

	printf("PORT SIMULATION SOFTWARE\n");
	printf("========================\n\n");

	printf("Enter option to edit/see bit status of port %c\n", port);
	printf("Command list:\n");
	printf("==> 1: set bit\n");
	printf("==> 2: clear bit\n");
	printf("==> 3: get bit status\n");
	printf("==> 4: mask ON bits\n");
	printf("==> 5: mask OFF bits\n");
	printf("==> 6: mask TOGGLE bits\n");
	printf("==> e: terminates the program\n\n");
}