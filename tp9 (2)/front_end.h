/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   front_end.h
 * Author: newtonis
 *
 * Created on June 12, 2017, 11:56 PM
 */

#ifndef FRONT_END_H
#define FRONT_END_H

#ifdef __cplusplus
extern "C" {
#endif


    
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdbool.h>
    
#include "triag.h"
    
#define MAX_TEXT_CNT 10
#define DEF_SZ 50
   
#define CNT_COL 3
    
typedef struct { /// variables that main front end uses, but are not directly related with graphics
    triangle_hd_t *base_struct;
    float w_rot;
    int fract_count;
    
    int max_fract_count;
    float max_tol;
    float color[CNT_COL];
    int report_flag;
    char file_to_save[DEF_SZ];
    int save_data;
}shared_vars_t;

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
    ALLEGRO_TIMER *timer_b;
    void (*key_press)(graphic_vars_t* , int);
    void (*extra_draw_func)(graphic_vars_t* );
    void (*fractal_update)(graphic_vars_t*);
    
    show_text_t texts[MAX_TEXT_CNT]; // texts to show in the screen
    int texts_cnt;
    void* logic_ref; // a logic reference for callbacks
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

#endif /* FRONT_END_H */

