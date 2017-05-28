/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graphic.h
 * Author: newtonis
 *
 * Created on May 27, 2017, 8:40 PM
 */

#ifndef GRAPHIC_H
#define GRAPHIC_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
    
#include <stdbool.h>
    
#define MAX_TEXT_CNT 10
    
typedef struct{
    ALLEGRO_FONT *iso_title;
    ALLEGRO_FONT *iso_text;
}fonts_t;

typedef struct{
    int x,y;
    char *text;
}show_text_t;

struct graphic_vars_t;

typedef struct{
    fonts_t fonts;
    ALLEGRO_DISPLAY *disp_a;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_TIMER *timer_a;
    bool end;
    void * key_press(graphic_vars_t* , int);
    
    show_text_t texts[MAX_TEXT_CNT];
    int texts_cnt;
} graphic_vars_t;

int init_graphic(graphic_vars_t * vars);

void set_show_text_pos( int text_id,int px,int py);
void update_show_text( char *text ,int text_id);

void update_graphic(graphic_vars_t* vars);
void update_events(graphic_vars_t* vars);
int end_graphic(graphic_vars_t* vars);


#ifdef __cplusplus
}
#endif

#endif /* GRAPHIC_H */

