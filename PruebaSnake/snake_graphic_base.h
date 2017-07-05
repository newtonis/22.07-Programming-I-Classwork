
#ifndef SNAKE_GRAPHIC_BASE_H
#define SNAKE_GRAPHIC_BASE_H


#include <allegro5/allegro.h>
#include "config.h"
#include "interface.h"

typedef struct{ //// Auxiliar graphic structures needed to plot game
    ALLEGRO_BITMAP *snake[MAX_LENGTH];
    ALLEGRO_BITMAP *food;
}graphic_vars;

typedef struct{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer_a , *timer_b;
    ALLEGRO_BITMAP *snake[MAX_LENGTH];
    ALLEGRO_BITMAP *food;


    bool key_pressed[MOVE_KEYS]; //Estado de teclas, true cuando esta apretada
    bool redraw;
    bool do_exit; 

    graphic_vars *plot_game_graphic;
    
    int key_press;
    int direction;
    int dir_control;
    int refresh;
    
}full_graphic_content;


void init_snake_pc(full_graphic_content *content);
void handle_events(logic_vars* vars , full_graphic_content * content);
void destroy_graphic_base(full_graphic_content * content);

#endif