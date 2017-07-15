#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "snake_pc.h"
#include "ui.h"

void init_snake_pc(full_graphic_content *content){

    int i = 0;
    
    for (i = 0;i < 4;i++){
        content->key_pressed[i] = 0;
    }
    content->time_counter = 0;
    
    content->redraw = false;
    content->do_exit = false; 
 
    snake_node_t snake_H[MAX_LENGTH]; // initial snake
    snake_node_t *pHead = snake_H; // pointer to snake
        
    food_t gameFood; // food in game
    food_t *pGameFood = &gameFood; // pointer to food struct
        
    if(!al_init()) {
	fprintf(stderr, "failed to initialize allegro!\n");
	exit(1);
    }
 
    if(!al_install_keyboard()) {
	fprintf(stderr, "failed to initialize the keyboard!\n");
	exit(1);
    }
 
    content->timer_a = al_create_timer(1.0 / FPS_A);
    if(!content->timer_a) {
	fprintf(stderr, "failed to create timer!\n");
	exit(1);
    }
    
    content->timer_b = al_create_timer(1.0 / FPS_B);
    if(!content->timer_b) {
	fprintf(stderr, "failed to create timer!\n");
	exit(1);
    }
        
    for(i = 0; i < MAX_LENGTH; i++){ // snake create
        content->images->snake[i] = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE);
        if(!content->images->snake[i]) {
            fprintf(stderr, "failed to create snake bitmap!\n");
            al_destroy_timer(content->timer_a);
            al_destroy_timer(content->timer_b);

            while(i >= 0){
                al_destroy_bitmap(content->images->snake[i]);
                i--;
            }
            exit(1);
        }
    }
        
    content->images->food = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE); // food create
    if(!content->images->food){
        fprintf(stderr, "failed to create food bitmap!\n");
        al_destroy_timer(content->timer_a);
	al_destroy_timer(content->timer_b);

        al_destroy_bitmap(content->images->snake[i]);
        exit(1);
    }
    
    content->event_queue = al_create_event_queue();
    if(!content->event_queue) {
	fprintf(stderr, "failed to create event_queue!\n");
        for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
            al_destroy_bitmap(content->images->snake[i]);
        }
        al_destroy_bitmap(content->images->food);
	al_destroy_timer(content->timer_a);
	al_destroy_timer(content->timer_a);
	exit(1);
    }
 
    al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED);
    content->display = al_create_display(SCREEN_W, SCREEN_H);
    
    if(!content->display) {
	fprintf(stderr, "failed to create display!\n");
	al_destroy_timer(content->timer_a);
	al_destroy_timer(content->timer_b);
	for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
            al_destroy_bitmap(content->images->snake[i]);
        }
        al_destroy_bitmap(content->images->food);
	al_destroy_event_queue(content->event_queue);
        exit(1);
    }
	
  
    
    al_set_target_bitmap(al_get_backbuffer(content->display));
  
    al_register_event_source(content->event_queue, al_get_display_event_source(content->display));
    al_register_event_source(content->event_queue, al_get_timer_event_source(content->timer_a));
    al_register_event_source(content->event_queue, al_get_timer_event_source(content->timer_b));
    al_register_event_source(content->event_queue, al_get_keyboard_event_source()); 
 
        
    al_start_timer(content->timer_a);
    al_start_timer(content->timer_b);
    
    content->front_end_status = INITIAL_MENU;
    
    /// start mouse cursor handler
    content->cursor_handler = init_cursor_handler(content->display);
    
    /// init fonts
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    load_fonts(content->fonts);
    
    //// load all game images
    al_init_image_addon();
    load_images(content->images);

    /// init mouse driver
    al_install_mouse();
    
    /// init menu
    init_menu(content);
    
    /// init scoreboard
    init_scoreboard(content);
}




void destroy_graphic_base(full_graphic_content * content){
    int i;
    for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
        al_destroy_bitmap(content->images->snake[i]);
    }
    al_destroy_timer(content->timer_a);
    al_destroy_timer(content->timer_b);
    al_destroy_bitmap(content->images->food);
    al_destroy_display(content->display);
    
    destroy_handler(content->cursor_handler);
    destroy_menu(content);
    destroy_images(content->images);
    destroy_fonts(content->fonts);
    
}

//// Load all game bitmaps
void load_images(images_t* images){
   
    images->arr_down  = load_or_crash("flecha_abajo.png");
    images->arr_down_2= load_or_crash("flecha_abajo_2.png");
    images->arr_up    = load_or_crash("flecha_arriba.png");
    images->arr_up_2  = load_or_crash("flecha_arriba_2.png");
    
    
    images->game_over = load_or_crash("game_over.png");
    images->easy      = load_or_crash("lento.png");
    images->medium    = load_or_crash("medio.png");
    images->hard      = load_or_crash("rapido.png");
    images->start_button_image = load_or_crash("start.png");
    images->start_button_image_b = load_or_crash("start_b.png");
    
    images->restart_image   = load_or_crash("restart.png");
    images->restart_image_b = load_or_crash("restart_b.png");
    
}
void destroy_images(images_t* images){
    al_destroy_bitmap(images->arr_down);
    al_destroy_bitmap(images->arr_up);
    al_destroy_bitmap(images->game_over);
    al_destroy_bitmap(images->easy);
    al_destroy_bitmap(images->medium);
    al_destroy_bitmap(images->hard);
    al_destroy_bitmap(images->start_button_image);
}
/*** Create all user interface elements ***/
void init_menu(full_graphic_content *content){
    //content->intial_menu->play_button = init_button( NULL , NULL );
    
    content->intial_menu = malloc(sizeof(initial_menu_vars_t));
    if (!content->intial_menu){
        fprintf(stderr,"Could not allocate memory");
        exit(1);
    }
    
    ALLEGRO_BITMAP *arr_box_images[] = {
        content->images->arr_up,
        content->images->arr_up_2,
        content->images->arr_down,
        content->images->arr_down_2
    };
    
    content->intial_menu->play_button = init_button(content->images->start_button_image , content->images->start_button_image_b, content->cursor_handler, SCREEN_W / 2 , SCREEN_H - START_BUTTON_CORR);
    
   
    content->intial_menu->width_config_ui = init_reg_box(arr_box_images, content->cursor_handler,content->fonts->iso_text,SCREEN_W/8*1,SCREEN_H/2,DEFAULT_WIDTH,MIN_TABLE_WIDTH,MAX_TABLE_WIDTH);
    content->intial_menu->height_config_ui = init_reg_box(arr_box_images, content->cursor_handler, content->fonts->iso_text,SCREEN_W/4,SCREEN_H/2,DEFAULT_HEIGHT,MIN_TABLE_HEIGHT,MAX_TABLE_HEIGHT);
    content->intial_menu->diff_ui = init_reg_box(arr_box_images, content->cursor_handler, content->fonts->iso_text,SCREEN_W/4*3,SCREEN_H/2,DEFAULT_DIFFICULTY,MIN_DIFF,MAX_DIFF);
    
    
    content->intial_menu->text_config_size = init_show_text(MAP_SIZE_TEXT,BOX_COLOR,content->fonts->iso_text,SCREEN_W/16*3,SCREEN_H/2-TEXT_CONF_DISTANCE);
    content->intial_menu->extra_text_config = init_show_text("X",BOX_COLOR,content->fonts->iso_text,SCREEN_W/16*3,SCREEN_H/2-DEF_SZ/2);
    content->intial_menu->title_text = init_show_text(GAME_TITLE_TEXT,BOX_COLOR,content->fonts->iso_title,SCREEN_W/2,TITLE_DISTANCE_Y);
    content->intial_menu->diff_text = init_show_text(DIFF_TEXT,BOX_COLOR,content->fonts->iso_text,SCREEN_W/4*3,SCREEN_H/2-TEXT_CONF_DISTANCE);
    
    
}

void destroy_menu(full_graphic_content *content){
    destroy_button(content->intial_menu->play_button);
    destroy_reg_box(content->intial_menu->width_config_ui);
    destroy_reg_box(content->intial_menu->height_config_ui);
    
    destroy_text(content->intial_menu->text_config_size);
    destroy_text(content->intial_menu->extra_text_config);
    destroy_text(content->intial_menu->title_text);
    destroy_text(content->intial_menu->diff_text);
    
    free(content->intial_menu);
}
void init_scoreboard(full_graphic_content *content){
    content->scoreboard = malloc(sizeof(scoreboard_vars_t));
    if (!content->scoreboard){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    content->scoreboard->score_text = init_show_text("Score: ",LIGHT_BOX_COLOR,content->fonts->iso_big_text,SCREEN_W/2,SCREEN_H/2-DISTANCE_SCOREBOARD_Y);
    content->scoreboard->high_score = init_show_text("Highscore: ",LIGHT_BOX_COLOR,content->fonts->iso_big_text,SCREEN_W/8*3,SCREEN_H/2+DISTANCE_SCOREBOARD_Y);

    content->scoreboard->score_number_text = init_show_text("",LIGHT_BOX_COLOR,content->fonts->iso_big_text,SCREEN_W/2+DISTANCE_SCOREBOARD_X,SCREEN_H/2-DISTANCE_SCOREBOARD_Y);
    content->scoreboard->high_score_number_text = init_show_text("",LIGHT_BOX_COLOR,content->fonts->iso_big_text,SCREEN_W/8*3+DISTANCE_HIGHSCORE_X,SCREEN_H/2+DISTANCE_SCOREBOARD_Y);
    
    content->scoreboard->score_number_text->text = malloc(sizeof(char)*5); // this text MUST BE dynamic, because it changes .
    content->scoreboard->high_score_number_text->text = malloc(sizeof(char)*5);
    
    content->scoreboard->game_over_text = init_show_text("GAME OVER",GAME_OVER_COLOR,content->fonts->iso_ultra_big_text,SCREEN_W/2,SCREEN_H/8);
    
    content->scoreboard->restart_button = init_button(content->images->restart_image,content->images->restart_image_b,content->cursor_handler,SCREEN_W/2,SCREEN_H/6*5);
}
void destroy_scoreboard(full_graphic_content *content){
    free(content->scoreboard->score_text);
    free(content->scoreboard->high_score);
    free(content->scoreboard->high_score_number_text);
    
    free(content->scoreboard->score_number_text->text);
    free(content->scoreboard->high_score_number_text->text);
    
    destroy_text(content->scoreboard->high_score_number_text);
    destroy_text(content->scoreboard->score_number_text);
    destroy_text(content->scoreboard->high_score);
    destroy_text(content->scoreboard->score_text);
    destroy_text(content->scoreboard->game_over_text);
    
    free(content->scoreboard);
}



void update_positions(full_graphic_content* content){ /// when screen resizes
    double screen_width  = (double)al_get_display_width(content->display);
    double screen_height = (double)al_get_display_height(content->display);
    
    
    //// Initial Menu
    update_show_text_position(content->intial_menu->title_text,screen_width/2,TITLE_DISTANCE_Y);
    update_show_text_position(content->intial_menu->text_config_size,screen_width/16*3,screen_height/2-TEXT_CONF_DISTANCE);
    update_show_text_position(content->intial_menu->diff_text,screen_width/4*3,screen_height/2-TEXT_CONF_DISTANCE);
    update_show_text_position(content->intial_menu->extra_text_config,screen_width/16*3,screen_height/2-DEF_SZ/2);
    
    update_button_position(content->intial_menu->play_button,screen_width/2,screen_height-START_BUTTON_CORR);
    
    update_reg_box_position(content->intial_menu->width_config_ui,screen_width/8,screen_height/2);
    update_reg_box_position(content->intial_menu->height_config_ui,screen_width/4,screen_height/2);
    update_reg_box_position(content->intial_menu->diff_ui,screen_width/4*3,screen_height/2);
    

    //// Scoreboard
    update_show_text_position(content->scoreboard->score_text,screen_width/2,screen_height/2-DISTANCE_SCOREBOARD_Y);
    update_show_text_position(content->scoreboard->high_score,screen_width/8*3,screen_height/2+DISTANCE_SCOREBOARD_Y);
    update_show_text_position(content->scoreboard->score_number_text,screen_width/2+DISTANCE_SCOREBOARD_X,screen_height/2-DISTANCE_SCOREBOARD_Y);
    update_show_text_position(content->scoreboard->high_score_number_text,screen_width/8*3+DISTANCE_HIGHSCORE_X,screen_height/2+DISTANCE_SCOREBOARD_Y);
    update_show_text_position(content->scoreboard->game_over_text,screen_width/2,screen_height/8);
    
    update_button_position(content->scoreboard->restart_button,screen_width/2,screen_height/6*5);
}



void load_fonts(fonts_t* fonts){
    fonts->iso_text = NULL;
    fonts->iso_title = NULL;
    fonts->iso_text = al_load_font("fonts/isocpeur.ttf",FONT_SIZE_A,0);
    fonts->iso_title = al_load_font("fonts/isocpeur.ttf",FONT_SIZE_B,0);
    fonts->iso_big_text = al_load_font("fonts/isocpeur.ttf",FONT_SIZE_C,0);
    fonts->iso_ultra_big_text = al_load_font("fonts/isocpeur.ttf",FONT_SIZE_D,0);
    
    
    if (!fonts->iso_text || !fonts->iso_title || !fonts->iso_big_text || !fonts->iso_ultra_big_text){
        fprintf(stderr,"Could not load fonts");
        exit(1);
    }
}
void destroy_fonts(fonts_t* fonts){
    al_destroy_font(fonts->iso_text);
    al_destroy_font(fonts->iso_title);
    al_destroy_font(fonts->iso_big_text);
}

/// load a image. If loading fails then throws an errors
ALLEGRO_BITMAP* load_or_crash(const char *filename){
    ALLEGRO_BITMAP * image = NULL;
    image = al_load_bitmap(filename);
    if (!image){
        fprintf(stderr,"Error loading %s\n",filename);
        exit(1);
    }
    return image;
}