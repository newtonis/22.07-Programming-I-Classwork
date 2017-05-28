#include <stdio.h>
#include <stdlib.h>

#include "graphic.h"
#include "port_utils.h"
#include "output.h"
#include "input.h"

// Allegro libraries
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FPS 60.0

ALLEGRO_FONT *iso_title = NULL;
ALLEGRO_FONT *iso_text = NULL;

int main(){
    ALLEGRO_DISPLAY *disp_a = NULL;
    ALLEGRO_EVENT_QUEUE *event_q = NULL;
    ALLEGRO_TIMER *timer_a = NULL;
    ALLEGRO_BITMAP *ledON = NULL;
    ALLEGRO_BITMAP *ledOFF = NULL;
    
    FILE *fp = NULL;
    
    fp = fopen("event_log","w");
    
    if(!al_init()){ // allegro init
        fprintf(fp, "ERROR - allegro init\n");
        fclose(fp);
        return -1;
    }
    fprintf(fp, "OK - allegro init\n");
    
    event_q = al_create_event_queue();
    
    if(!event_q){ // event queue init
        fprintf(fp, "ERROR - event queue init\n");
        fclose(fp);
        return -1;
    }
    fprintf(fp, "OK - event queue init\n");
    
    if(!al_install_keyboard()){ // keyboard install
        fprintf(fp, "ERROR - keyboard install\n");
        al_destroy_event_queue(event_q);
        fclose(fp);
        return -1;
    }
    
    fprintf(fp, "OK - keyboard installed\n");
        
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    
    iso_title = al_load_font("isocpeur.ttf", TITLE_W, 0); // title font
    iso_text = al_load_font("isocpeur.ttf", TEXT_W, 0); // common text font
    
    if((!iso_title)||(!iso_text)){ // iso font init
        fprintf(fp, "ERROR - font init\n");
        al_destroy_event_queue(event_q);
        fclose(fp);
        return -1;
    }
    
    fprintf(fp, "OK - font init\n");
    
    timer_a = al_create_timer(1.0 / FPS);
    
    if(!timer_a){ // timer init
        fprintf(fp, "ERROR - font init\n");
        al_destroy_event_queue(event_q);
        fclose(fp);
        return -1;
    }
        
    if(!al_init_image_addon()) { // ADDON for image manage
            fprintf(fp, "ERROR - image addon init\n");
            return -1;
    }
    
    fprintf(fp, "OK - image addon init\n");
    
    
    ledON = al_load_bitmap("led_on.png");
    ledOFF = al_load_bitmap("led_off.png");
    
    if((!ledON)||(!ledOFF)){ // image load
        fprintf(fp, "ERROR - no image\n");
        al_destroy_event_queue(event_q);
        al_destroy_timer(timer_a);
        fclose(fp);
        return -1;        
    }
    
    
    disp_a = al_create_display(SCREEN_W, SCREEN_H);
    
    if(!disp_a){ // display init
        fprintf(fp, "ERROR - display init\n");
        al_destroy_event_queue(event_q);
        al_destroy_timer(timer_a);
        al_destroy_bitmap(ledON);
        al_destroy_bitmap(ledOFF);
        fclose(fp);
        return -1;
    }
    
    fprintf(fp, "OK - display init\n");
    
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    
    al_register_event_source(event_q, al_get_display_event_source(disp_a)); // register display events
    al_register_event_source(event_q, al_get_timer_event_source(timer_a)); // register timer events
    al_register_event_source(event_q, al_get_keyboard_event_source()); // register keyboard events
    
    microPorts_t  mp;
    int err = initPorts(&mp); // port init

    if (err == 1){
            fprintf(fp, "ERROR - Can't port heap memory\n");
            fclose(fp);
            return -1;
    }else{	
        al_start_timer(timer_a); 
        
        int end = false, tm = 0, timer_count = 0;
        int mode = NORMAL, i, key_pressed;
        
        instruct_print();
        
        while(!end){
            ALLEGRO_EVENT event_log;
            
            if(al_get_next_event(event_q, &event_log)){ // if event
                if(event_log.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ // display closed - end program
                    
                    end = true;
                }else if(event_log.type == ALLEGRO_EVENT_TIMER){ 
                    
                    if(++timer_count == ((int)FPS)/2){ // for blink case, refreshes at 0.5 secs
                        if(tm)
                            tm = 0;
                        else
                            tm = 1;
                        
                        timer_count = 0;
                    }
                    if((mode == BLINK)||(key_pressed != ALLEGRO_KEY_MAX)){ // for avoiding refreshing all time!
                        update_display(&mp,&mode,ledON,ledOFF);
                    }
                    
                    userInput(&mp,&end,&mode,tm,key_pressed);
                }else if(event_log.type == ALLEGRO_EVENT_KEY_DOWN){ 
                    
                    key_pressed = event_log.keyboard.keycode;
                    
                }else if(event_log.type == ALLEGRO_EVENT_KEY_UP){ 
                    
                    key_pressed = ALLEGRO_KEY_MAX; 
                }
            }

        }
    }
    
    fclose(fp);
    al_destroy_display(disp_a);
    al_destroy_timer(timer_a);
    al_destroy_event_queue(event_q);
    
    return 0;
}