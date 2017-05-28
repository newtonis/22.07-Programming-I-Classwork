/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "graphic.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>



int init_graphic(graphic_vars_t * vars){
    if (!al_init()){
        return 0;
    }
    vars->event_q = al_create_event_queue();
    if (!vars->event_q){
        return 0;
    }
    if (!al_install_keyboard()){
        al_destroy_event_queue(vars->event_q);
        return 0;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    
    //vars->fonts->iso_text = al_load_font(FONT_ISOCPEUR , );

    
}
int end_graphic(graphic_vars_t* vars){
    
}