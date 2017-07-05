#include <stdio.h>
#include <allegro5/allegro.h>

#include "snake_graphic_base.h"

#include "snake_pc.h"

void init_snake_pc(full_graphic_content *content){

    int i = 0;
    
    for (i = 0;i < 4;i++){
        content->key_pressed[i] = 0;
    }
    
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
 
    content->timer = al_create_timer(1.0 / FPS);
    if(!content->timer) {
	fprintf(stderr, "failed to create timer!\n");
	exit(1);
    }
        
    for(i = 0; i < MAX_LENGTH; i++){ // snake create
        content->plot_game_graphic->snake[i] = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE);
        if(!content->plot_game_graphic->snake[i]) {
            fprintf(stderr, "failed to create snake bitmap!\n");
            al_destroy_timer(content->timer);
            while(i >= 0){
                al_destroy_bitmap(content->plot_game_graphic->snake[i]);
                i--;
            }
            exit(1);
        }
    }
        
    content->plot_game_graphic->food = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE); // food create
    if(!content->plot_game_graphic->food){
        fprintf(stderr, "failed to create food bitmap!\n");
        al_destroy_timer(content->timer);
        al_destroy_bitmap(content->plot_game_graphic->snake[i]);
        exit(1);
    }
    
    content->event_queue = al_create_event_queue();
    if(!content->event_queue) {
	fprintf(stderr, "failed to create event_queue!\n");
        for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
            al_destroy_bitmap(content->plot_game_graphic->snake[i]);
        }
        al_destroy_bitmap(content->plot_game_graphic->food);
	al_destroy_timer(content->timer);
	exit(1);
    }
 
    content->display = al_create_display(SCREEN_W, SCREEN_H);
    if(!content->display) {
	fprintf(stderr, "failed to create display!\n");
	al_destroy_timer(content->timer);
	for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
            al_destroy_bitmap(content->plot_game_graphic->snake[i]);
        }
        al_destroy_bitmap(content->plot_game_graphic->food);
	al_destroy_event_queue(content->event_queue);
        exit(1);
    }
	
    for(i = 0; i < MAX_LENGTH; i++){ // pink snake
        al_set_target_bitmap(content->plot_game_graphic->snake[i]);
        al_clear_to_color(al_map_rgb(255, 0, 255));
    }
	
    al_set_target_bitmap(content->plot_game_graphic->food); // Pink Food
    al_clear_to_color(al_map_rgb(255, 0, 255));
    
    al_set_target_bitmap(al_get_backbuffer(content->display));
  
    al_register_event_source(content->event_queue, al_get_display_event_source(content->display));
    al_register_event_source(content->event_queue, al_get_timer_event_source(content->timer));
    al_register_event_source(content->event_queue, al_get_keyboard_event_source()); 
 
    al_clear_to_color(al_map_rgb(0,0,0));
        
    al_start_timer(content->timer);
    
}


void handle_events(logic_vars* vars , full_graphic_content * content){

    ALLEGRO_EVENT ev;
    if( al_get_next_event(content->event_queue, &ev) ){ 
	if(ev.type == ALLEGRO_EVENT_TIMER){
            if(content->key_pressed[KEY_UP]){
                content->key_press = KEY_UP;
            }else if(content->key_pressed[KEY_DOWN]){
                content->key_press = KEY_DOWN;
            }else if(content->key_pressed[KEY_LEFT]){
                content->key_press = KEY_LEFT;
            }else if(content->key_pressed[KEY_RIGHT]){
                content->key_press = KEY_RIGHT;
            }
            content->refresh++;
            
            //if((content->refresh % MOVE_FREQ) == 0){
                update_graphic_game(vars,content);
            //}
        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            content->do_exit = true;
        }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
       
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    content->key_pressed[KEY_UP] = true;
                break;
                case ALLEGRO_KEY_DOWN:
                    content->key_pressed[KEY_DOWN] = true;
                break;
                case ALLEGRO_KEY_LEFT: 
                    content->key_pressed[KEY_LEFT] = true;
                break;

                case ALLEGRO_KEY_RIGHT:
                    content->key_pressed[KEY_RIGHT] = true;
                break;
            }
        }else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    content->key_pressed[KEY_UP] = false;
                break;
                case ALLEGRO_KEY_DOWN:
                    content->key_pressed[KEY_DOWN] = false;
                break;
                case ALLEGRO_KEY_LEFT: 
                    content->key_pressed[KEY_LEFT] = false;
                break;
                case ALLEGRO_KEY_RIGHT:
                    content->key_pressed[KEY_RIGHT] = false;
                break;
                case ALLEGRO_KEY_ESCAPE:
                    content->do_exit = true;
                break;
            }
        }
    }
}

void destroy_graphic_base(full_graphic_content * content){
    int i;
    for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
        al_destroy_bitmap(content->plot_game_graphic->snake[i]);
    }
    al_destroy_timer(content->timer);
    al_destroy_bitmap(content->plot_game_graphic->food);
    al_destroy_display(content->display);
}