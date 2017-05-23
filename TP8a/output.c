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