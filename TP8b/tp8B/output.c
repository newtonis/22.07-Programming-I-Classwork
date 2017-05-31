#include <stdio.h>
#include "output.h"

#define WHITE al_map_rgb(255,255,255)
#define TAB 20
#define T_ENTER (TITLE_W/2)
#define N_ENTER 20
#define NO_FLAG 0

int init_allegro_soft(allegro_utils_t *simulator){
    
    simulator->log = fopen("event_log","w");
    
    if(!al_init()){ // allegro init
        fprintf(simulator->log, "ERROR - allegro init\n");
        fclose(simulator->log);
        return -1;
    }
    fprintf(simulator->log, "OK - allegro init\n");
    
    simulator->event_q = al_create_event_queue();
    
    if(!(simulator->event_q)){ // event queue init
        fprintf(simulator->log, "ERROR - event queue init\n");
        fclose(simulator->log);
        return -1;
    }
    fprintf(simulator->log, "OK - event queue init\n");
    
    if(!al_install_keyboard()){ // keyboard install
        fprintf(simulator->log, "ERROR - keyboard install\n");
        al_destroy_event_queue(simulator->event_q);
        fclose(simulator->log);
        return -1;
    }
    fprintf(simulator->log, "OK - keyboard installed\n");
    
    simulator->timer_a = al_create_timer(1.0 / FPS);
    
    if(!(simulator->timer_a)){ // timer init
        fprintf(simulator->log, "ERROR - timer init\n");
        al_destroy_event_queue(simulator->event_q);
        fclose(simulator->log);
        return -1;
    }
    fprintf(simulator->log, "OK - timer init\n");
  
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    
    simulator->iso_title = al_load_font("isocpeur.ttf", TITLE_W, 0); // title font
    simulator->iso_text = al_load_font("isocpeur.ttf", TEXT_W, 0); // common text font
    
    if((!(simulator->iso_title))||(!(simulator->iso_text))){ // iso font init
        fprintf(simulator->log, "ERROR - font init\n");
        al_destroy_timer(simulator->timer_a);
        al_destroy_event_queue(simulator->event_q);
        fclose(simulator->log);
        return -1;
    }
    fprintf(simulator->log, "OK - font init\n");
    
        if(!al_init_image_addon()) { // ADDON for image manage
        al_destroy_timer(simulator->timer_a);
        al_destroy_event_queue(simulator->event_q);
        fprintf(simulator->log, "ERROR - image addon init\n");
        return -1;
    }
    fprintf(simulator->log, "OK - image addon init\n");
    
    simulator->ledON = al_load_bitmap("led_on.png");
    simulator->ledOFF = al_load_bitmap("led_off.png");
    
    if((!(simulator->ledON))||(!(simulator->ledOFF))){ // image load
        fprintf(simulator->log, "ERROR - no image\n");
        al_destroy_event_queue(simulator->event_q);
        al_destroy_timer(simulator->timer_a);
        fclose(simulator->log);
        return -1;        
    }
    fprintf(simulator->log, "OK - image load");
    
        
    simulator->disp_a = al_create_display(SCREEN_W, SCREEN_H);
    
    if(!(simulator->disp_a)){ // display init
        fprintf(simulator->log, "ERROR - display init\n");
        al_destroy_event_queue(simulator->event_q);
        al_destroy_timer(simulator->timer_a);
        al_destroy_bitmap(simulator->ledON);
        al_destroy_bitmap(simulator->ledOFF);
        fclose(simulator->log);
        return -1;
    }
    fprintf(simulator->log, "OK - display init\n");
}

void instruct_print(ALLEGRO_FONT *titleF, ALLEGRO_FONT *textF){
    
    float enter = T_ENTER;

    al_draw_text(titleF, WHITE, TAB, enter, NO_FLAG, "PORT SIMULATION SOFTWARE");
    enter += T_ENTER;
    al_draw_text(titleF, WHITE, TAB, enter, NO_FLAG, "=========================");
    enter += T_ENTER + N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "Enter option to set status of LEDs connected to port A.");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "If the entered option is not one of below, nothing happens.");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "Command list:");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "==> Numbers 0 to 7: port bit set corresponding to LED");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "==> B: the switched on LEDs will blink changing the state per 0.5 sec");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "       end blink mode by pressing C or exiting the program");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "==> S: sets all LEDs on");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "==> C: sets all LEDs off");
    enter += N_ENTER;
    al_draw_text(textF, WHITE, TAB, enter, NO_FLAG, "==> ESC: exit program (closing display also works)");
    
    al_flip_display();
    
}
