// TP 8 Item A (1)
// Marcelo Regueira
// Joaquin Mestanza
// Ariel Nowik

// Git: https://github.com/newtonis/ITBA_PROG_TPS/tree/master/TP8b/tp8B


#include <stdio.h>
#include <stdlib.h>

#include "graphic.h"
#include "port_utils.h"
#include "output.h"
#include "input.h"

int main(){
    int start_control = false;
    
    allegro_utils_t led_sys; // struct with disp, timer, event queue and bitmaps
    
    start_control = init_allegro_soft(&led_sys); // initialize of struct
    
    if(start_control == START_ERR)
        return -1;
    
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    
    al_register_event_source(led_sys.event_q, al_get_display_event_source(led_sys.disp_a)); // register display events
    al_register_event_source(led_sys.event_q, al_get_timer_event_source(led_sys.timer_a)); // register timer events
    al_register_event_source(led_sys.event_q, al_get_keyboard_event_source()); // register keyboard events
    
    microPorts_t  mp;
    int err = initPorts(&mp); // port init

    if (err == 1){
            fprintf(led_sys.log, "ERROR - Can't port heap memory\n");
            fclose(led_sys.log);
            return -1;
    }else{	
        al_start_timer(led_sys.timer_a); 
        
        int end = false, tm = 0, timer_count = 0;
        int mode = NORMAL, i, key_pressed;
        
        instruct_print(led_sys.iso_title, led_sys.iso_text);
        
        while(!end){
            ALLEGRO_EVENT event;
            
            if(al_get_next_event(led_sys.event_q, &event)){ // if event
                if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ // display closed - end program
                    
                    end = true;
                }else if(event.type == ALLEGRO_EVENT_TIMER){ 
                    
                    if(++timer_count == ((int)FPS)/2){ // for blink case, refreshes at 0.5 secs
                        if(tm)
                            tm = 0;
                        else
                            tm = 1;
                        
                        timer_count = 0;
                    }
                    if((mode == BLINK)||(key_pressed != ALLEGRO_KEY_MAX)){ // for avoiding refreshing all time!
                        update_display(&mp,&mode,led_sys.ledON,led_sys.ledOFF);
                    }
                    
                    userInput(&mp,&end,&mode,tm,key_pressed);
                }else if(event.type == ALLEGRO_EVENT_KEY_DOWN){ 
                    
                    key_pressed = event.keyboard.keycode;
                    
                }else if(event.type == ALLEGRO_EVENT_KEY_UP){ 
                    
                    key_pressed = ALLEGRO_KEY_MAX; 
                }
            }

        }
    }
    
    fclose(led_sys.log);
    al_destroy_display(led_sys.disp_a);
    al_destroy_timer(led_sys.timer_a);
    al_destroy_event_queue(led_sys.event_q);
    
    return 0;
}