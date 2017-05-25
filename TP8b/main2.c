#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nonblock.h"
#include "graphic.h"
#include "port_utils.h"
#include "output.h"
#include "input.h"

// netbeans test!

int main(){
	microPorts_t  mp;
	int err = initPorts(&mp);

	if (err == 1){
		printf("Fatal error, can't port heap memory");
	}else{	
		int end = 0;
		int mode = NORMAL;

		nonblock(NB_ENABLE);
		while (!end){
			long tm = (long)time(NULL);
			update_display(&mp,&mode);
			userInput(&mp,&end,&mode,tm);
			//while (tm == (long)time(NULL)); // wait to next second
		}
		nonblock(NB_DISABLE);
		system("clear");
	}
}