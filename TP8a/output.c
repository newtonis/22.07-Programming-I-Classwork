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

void welcome(void){
	printf("%s\n", "Welcome to the LED simulator program'\n'" );
	printf("%s\n", "-Please enter: ");
	printf("%s\n", "- a number from 0 to 7 if you want an specific LED to be on");
	printf("%s\n", "- 'b' if you want all the LEDS that are on to be triggered" );
	printf("%s\n", "- 'c' if you want all the LEDS off" );
	printf("%s\n", "- 's' if you want all the LEDS on" );
}