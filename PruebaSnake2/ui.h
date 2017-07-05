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


#include <allegro5/allegro_font.h>


enum {HOLD , RELEASE};
    
typedef struct{
    double x , y , w , h;
    ALLEGRO_BITMAP * surface_a;
    ALLEGRO_BITMAP * surface_b;
    int status;
}button_t;

typedef struct{
    button_t *up , *down;
    int value;
    ALLEGRO_FONT *font;
    int text_size;
    int x,y;
}reg_box_t;

/**** Create a dynamic button with two surfaces (one for each state) ****/
button_t *init_button( ALLEGRO_BITMAP* surface_a , ALLEGRO_BITMAP* surface_b , int x ,int y );

void draw_button(button_t* button);
int update_button(button_t* button);
void destroy_button(button_t* button);

reg_box_t *init_reg_box(ALLEGRO_BITMAP* surface_a , ALLEGRO_BITMAP* surface_b,ALLEGRO_FONT* font,int x,int y,int default_value,int size);
void draw_reg_box(reg_box_t *reg_box);
void destroy_reg_box(reg_box_t *reg_box);

#endif /* UI_H */

