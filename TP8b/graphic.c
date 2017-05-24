#include <stdio.h>
#include <stdlib.h>
#include "nonblock.h"
#include "port_utils.h"
#include "output.h"
#include <unistd.h>


void update_display(microPorts_t *mp,int *mode){
	system("clear");
	instruct_print();
	int i;	
	for (i = 0;i < mp->A.sz;i++){
		printf("%s ",bitGet(&mp->A,i) ? "***" : "   ");
		printf("|");
	}


	printf("\n");

	usleep(100000);
	

}