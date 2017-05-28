/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "graphic.h"
#include "config.h"
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>



int fe_init_graphic(graphic_vars_t * vars){
    if (!al_init()){
         fprintf(stderr , "Fatal error, could not init allegro");
        return 0;
    }
    vars->event_q = al_create_event_queue();
    if (!vars->event_q){
        fprintf(stderr , "Fatal error, could not init event queue\n");
        return 0;
    }
    if (!al_install_keyboard()){
        fprintf(stderr , "Fatal error, could not load keyboard\n");
        al_destroy_event_queue(vars->event_q);
        return 0;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    
    vars->fonts.iso_text = al_load_font( BASE_FONT , BASE_SIZE ,0 );
    
    if (!vars->fonts.iso_text){
        fprintf(stderr , "Fatal error, could not load fonts\n");
        return 0;
    }
    
    vars->timer_a = al_create_timer( 1.0 / FPS);
    if (!vars->timer_a){
        fprintf(stderr , "Fatal error, could not init timer\n");
        return 0;
    }
    vars->disp_a = al_create_display(SCREEN_W , SCREEN_H);
    if (!vars->disp_a){
        al_destroy_event_queue(vars->event_q);
        al_destroy_timer(vars->timer_a);
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    
    al_register_event_source(vars->event_q, al_get_display_event_source(vars->disp_a)); // registrar eventos de display
    al_register_event_source(vars->event_q, al_get_timer_event_source(vars->timer_a)); // registrar eventos de timer
    al_register_event_source(vars->event_q, al_get_keyboard_event_source()); // registrar eventos de teclado

    al_start_timer(vars->timer_a);
    
    vars->end = false;
    vars->texts_cnt = 0;
}
show_text_t* fe_add_show_text(graphic_vars_t* vars,int px,int py){
    vars->texts[vars->texts_cnt].x = px;
    vars->texts[vars->texts_cnt].y = py;
    return & vars->texts[vars->texts_cnt++];
}

void fe_update_graphic(graphic_vars_t* vars){
    int i;
    al_clear_to_color(al_map_rgb(0,0,0));
    for (i = 0;i < vars->texts_cnt;i++){
        al_draw_text(vars->fonts.iso_text, al_map_rgb(255,255,255),vars->texts[i].x, vars->texts[i].y,ALLEGRO_ALIGN_CENTER, vars->texts[i].text);
    }
    al_flip_display();
}

void fe_update_events(graphic_vars_t* vars){
    ALLEGRO_EVENT event_log;
    if(al_get_next_event(vars->event_q, &event_log)){
        switch (event_log.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                vars->end = true;
            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                vars->key_press( vars , event_log.keyboard.keycode);
            break;
            case ALLEGRO_EVENT_TIMER:
                fe_update_graphic(vars);
            break;
        }
    }
}
int fe_end_graphic(graphic_vars_t* vars){
    al_destroy_event_queue(vars->event_q);
    al_destroy_timer(vars->timer_a);
    al_destroy_display(vars->disp_a);
    al_destroy_font(vars->fonts.iso_text);
}