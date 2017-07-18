//// In this file all structures that handle game front end (graphics, events) are declared

/*** 
snake_graphic_base.h: In this file we handle all graphic intializations, destructions, 
and how the different graphical objects are drawn (Their position is relative to the screen size).

***/


#ifndef SNAKE_GRAPHIC_BASE_H
#define SNAKE_GRAPHIC_BASE_H


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "config.h"
#include "ui.h"

 //// front end different status moments
enum {INITIAL_MENU , PLAY , GAME_OVER};

/// Al fonts are stored in this structure
typedef struct{
    ALLEGRO_FONT *iso_title;
    ALLEGRO_FONT *iso_text;
    ALLEGRO_FONT *iso_big_text;
    ALLEGRO_FONT *iso_ultra_big_text;
}fonts_t;

/// All bitmaps are stored in this structure
typedef struct{ 
    ALLEGRO_BITMAP *arr_up , *arr_down;
    ALLEGRO_BITMAP *arr_up_2 , *arr_down_2;
    ALLEGRO_BITMAP *game_over;
    ALLEGRO_BITMAP *easy , *medium , *hard;
    ALLEGRO_BITMAP *food;
    ALLEGRO_BITMAP *start_button_image , *start_button_image_b;
    ALLEGRO_BITMAP *restart_image , *restart_image_b;
    ALLEGRO_BITMAP *snake_logo;
}images_t;

/// All structures for the menu
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

/// All structures for the scoreboard
typedef struct{
    show_text_t *score_text;
    show_text_t *high_score;
    show_text_t *score_number_text;
    show_text_t *high_score_number_text;
    
    show_text_t *game_over_text;
    button_t* restart_button;
}scoreboard_vars_t;

/// This is the main graphical structure,
/// So all graphical strctures in the end, are stored here
typedef struct{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer_a , *timer_b;

    cursor_handler_t* cursor_handler;
    
    bool key_pressed[MOVE_KEYS]; ///Key status
    bool redraw;
    bool do_exit; 

    images_t *images;
    initial_menu_vars_t *initial_menu; /// variables for initial menu
    scoreboard_vars_t *scoreboard;
    
    fonts_t* fonts;
    
    int key_press;
    int direction;
    int dir_control;
    int refresh;
    
    int front_end_status; // for the front-end FSM

    double time_counter; // count seconds
    int audio_state;
    int last_audio_state;
}full_graphic_content;

// Start graphic system
void init_snake_pc(full_graphic_content *content); 
// End graphic system
void destroy_graphic_base(full_graphic_content * content);
// update graphic elements position when screen resizes
void update_positions(full_graphic_content* content); 

/// Initializations and destrctions
static void load_fonts(fonts_t* fonts);
static void load_images(images_t* images);
static void init_menu(full_graphic_content *content);
static void init_scoreboard(full_graphic_content *content);

static void destroy_menu(full_graphic_content *content);
static void destroy_images(images_t* images);
static void destroy_fonts(fonts_t* fonts);
static void destroy_scoreboard(full_graphic_content *content);

// load image, or , if it could not be loaded, crash program.
static ALLEGRO_BITMAP* load_or_crash(const char *filename); 

#endif
