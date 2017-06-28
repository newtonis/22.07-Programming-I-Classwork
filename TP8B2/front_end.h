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

#include "config.h"
    
    
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdbool.h>
#include "game_logic.h"
    
#define MAX_TEXT_CNT 10
#define DEF_SZ 50
    
typedef struct{
    ALLEGRO_FONT *iso_title;
    ALLEGRO_FONT *iso_text;
}fonts_t;

typedef struct{
    int x,y;
    char text[DEF_SZ];
}show_text_t;

typedef struct graphic_vars graphic_vars_t;

struct graphic_vars{
    bool end;
    fonts_t fonts;
    ALLEGRO_DISPLAY *disp_a;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_TIMER *timer_a;
    void (*key_press)(graphic_vars_t* , int);
    game_vars_t *logic_ref; // we need a reference of logic game to be used by callbacks
    show_text_t texts[MAX_TEXT_CNT]; // texts to show in the screen
    int texts_cnt;
    show_text_t *status_text;
    show_text_t *time_left_text;
    
    /// music pointers
    ALLEGRO_SAMPLE *win_audio;         
    ALLEGRO_SAMPLE *lose_audio;
    ALLEGRO_SAMPLE *loop_audio;
    ALLEGRO_SAMPLE_INSTANCE *instance1;
    ALLEGRO_SAMPLE_INSTANCE *instance2;
    ALLEGRO_SAMPLE_INSTANCE *instance3;
} ;
typedef struct graphic_vars graphic_vars_t ;

int fe_init_graphic(graphic_vars_t * vars);

show_text_t* fe_add_show_text(graphic_vars_t* vars,int px,int py);

void fe_update_graphic(graphic_vars_t* vars);
void fe_update_events(graphic_vars_t* vars);
int fe_end_graphic(graphic_vars_t* vars);


#ifdef __cplusplus
}
#endif

#endif /* GRAPHIC_H */

