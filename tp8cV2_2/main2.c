#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "led_api.h"
#include "nonblock.h"
#include "graphic.h"
#include "port_utils.h"
#include "output.h"
#include "input.h"
#include "config.h"
///////////////////////////////////////////////////////
//// TP8c - Device drivers in user space - GROUP 3 ////
//// ----------------------------------------------////
//// ==> MESTANZA, Joaquin                         ////
//// ==> NOWIK, Ariel                              ////
//// ==> REGUEIRA, Marcelo   	                   /////////////////////////
//// -------------------------------------------------------------------////
//// Part of the following code works as an emulator for leds connected ////
//// to A port. The status of each can be changed as shown in the       ////
//// instructions when the program starts. Based on the led values      ////
//// in port A, we turn on/off the leds connected in the RaspberryPi.   ////
//// ==> output.h/output.c: functions to guide the user through the     ////
////     program.                                                       ////
//// ==> port_utils.h/port_utils.c: internal functions for working      ////
////     with the ports.                             		        ////
//// ==> input.h/input.c: functions for update the standard out         ////
////     acording to user input.                                        ////
//// ==> nonblock.h/nonblock.c: this library allows non blocking        ////
////     reading from stdin on Linux systems.                           ////
//// ==> graphic.h/graphic.c: functions for update the standard out     ////
////     with the new state of the leds.                                ////
//// ==>led_api.c/led_api.h : functions used for initializing and       ////
////    modifying leds in the RaspberyPi                                ////
//// -------------------------------------------------------------------////
////////////////////////////////////////////////////////////////////////////

int main(){
    
    microPorts_t mp;
    int err = initPorts(&mp);
    // init led interface, config to port A
    led_vars_t led_var;
    led_api_init( &led_var , mp.A.dir, led_codes,CNT_LEDS);
    
    if (err == 1){
	printf("Fatal error, can't port heap memory");
    }else{	
	int end = 0;
        int mode = NORMAL;     
        
	nonblock(NB_ENABLE);
	while (!end){ // loop until Esc key is hit
            long tm = (long)time(NULL);
            update_display(&mp,&mode);
            userInput(&mp,&end,&mode,tm);
			//while (tm == (long)time(NULL)); // wait to next second
            led_flush(&led_var);
        }
        nonblock(NB_DISABLE); 
	system("clear");
        
    }
    endPorts(&mp);
     
}


