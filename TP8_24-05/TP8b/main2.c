#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nonblock.h"
#include "graphic.h"
#include "port_utils.h"
#include "output.h"
#include "input.h"
//////////////////////////////////////////////////
//// TP8b - STRUCT, UNION, BITFIELD - GROUP 3 ////
//// ---------------------------------------- ////
//// ==> MESTANZA, Joaquin                    ////
//// ==> NOWIK, Ariel                         ////
//// ==> REGUEIRA, Marcelo   	              ///////////////////////////
//// --------------------------------------------------------------- ////
//// The following code works as an emulator for leds connected to   ////
//// A port. The status of each can be changed as shown in the       ////
//// instructions when the program starts.                           ////
//// ==> output.h/output.c: functions to guide the user through the  ////
////     program.                                                    ////
//// ==> port_utils.h/port_utils.c: internal functions for woking    ////
////     with the ports.                             		     ////
//// ==> input.h/input.c: functions for update the standard out      ////
////     acording to user input.                                     ////
//// ==> nonblock.h/nonblock.c: this library allows non blocking     ////
////     reading from stdin on Linux systems.                        ////
//// ==> graphic.h/graphic.c: functions for update the standard out  ////
////     with the new state of the leds.       			     ////
//// --------------------------------------------------------------- ////
/////////////////////////////////////////////////////////////////////////

/*
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "led_api.h"

int main(int argc, char** argv) {
    led_vars_t led_vars;
    uint16_t led_manager;
    int i = 0;
    led_api_init(&led_vars , &led_manager , led_codes , CNT_LEDS);
    led_manager = 0x01;
    led_flush( &led_vars);
    
    //return (EXIT_SUCCESS);
}
*/
int main(){
	microPorts_t mp;
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