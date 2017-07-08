
#ifndef SNAKE_GRAPHIC_BASE_H
#define SNAKE_GRAPHIC_BASE_H


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "config.h"
#include "interface.h"
#include "ui.h"

//// In this file all structures that handle game front end (graphics, events) are declared


 //// front end different status moments
enum {INITIAL_MENU , PLAY };

/// Al fonts are stored in this structure
typedef struct{
    ALLEGRO_FONT *iso_title;
    ALLEGRO_FONT *iso_text;
}fonts_t;

/// All bitmaps are stored in this structure
typedef struct{ 
    ALLEGRO_BITMAP *arr_up , *arr_down;
    ALLEGRO_BITMAP *arr_up_2 , *arr_down_2;
    ALLEGRO_BITMAP *game_over;
    ALLEGRO_BITMAP *easy , *medium , *hard;
    ALLEGRO_BITMAP *snake[MAX_LENGTH];
    ALLEGRO_BITMAP *food;
    ALLEGRO_BITMAP *start_button_image , *start_button_image_b;
}images_t;

typedef struct{
    button_t *play_button;
    reg_box_t *width_config_ui;
    reg_box_t *height_config_ui;
    reg_box_t *diff_ui; // difficulty
    
    show_text_t *text_config_size;
    show_text_t *extra_text_config;
    show_text_t *title_text;
    show_text_t *diff_text;
}initial_menu_vars_t;

typedef struct{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer_a , *timer_b;

    cursor_handler_t* cursor_handler;
    
    bool key_pressed[MOVE_KEYS]; //Estado de teclas, true cuando esta apretada
    bool redraw;
    bool do_exit; 

    images_t *images;
    initial_menu_vars_t *intial_menu; /// variables for initial menu
            
    fonts_t* fonts;
    
    int key_press;
    int direction;
    int dir_control;
    int refresh;
    
    int front_end_status;
}full_graphic_content;

void init_snake_pc(full_graphic_content *content);
void handle_events(logic_vars_t* vars , full_graphic_content * content );
void destroy_graphic_base(full_graphic_content * content);
void update_positions(full_graphic_content* content); // update graphic elements position when screen resizes

static void load_fonts(fonts_t* fonts);
static void load_images(images_t* images);
static void init_menu(full_graphic_content *content);
static void destroy_menu(full_graphic_content *content);
static void destroy_images(images_t* images);
static void destroy_fonts(fonts_t* fonts);

static ALLEGRO_BITMAP* load_or_crash(const char *filename); // load image, or , if it could not be loaded, crash program.

#endif