/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ui.h
 * Author: sissi
 *
 * Created on July 5, 2017, 3:03 PM
 */

#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

struct button{
    double x , y , w , h;
    ALLEGRO_BITMAP * surface;
};

void init_button( const char * text ,int x ,int y){
    
}

void update_button(button* ref){
    
    
    if (mx > x - w / 2 && mx < x + w / 2 && my > y - h / 2 && my < y + h / 2){
        al_draw_text(vars->fonts.iso_text, al_map_rgb(0,0,0),x , y,ALLEGRO_ALIGN_CENTER, ref.);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* UI_H */

