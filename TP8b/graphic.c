#include <stdio.h>
#include <stdlib.h>
#include "nonblock.h"
#include "port_utils.h"
#include "output.h"
#include <unistd.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

void update_display(microPorts_t *mp,int *mode){

	int i;	
	for (i = 0;i < mp->A.sz;i++){
		printf("%s ",bitGet(&mp->A,i) ? "***" : "   ");
		printf("|");
	}

	printf("\n");

}