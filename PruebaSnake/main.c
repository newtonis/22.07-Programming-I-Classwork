#include <stdio.h>
#include <allegro5/allegro.h>
#include "config.h"
#include "snake_logic.h"
#include "snake_pc.h"
 
#define FPS 60.0
#define MOVE_KEYS 4
 
int main(void)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *snake[MAX_LENGTH] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        ALLEGRO_BITMAP *food = NULL;
	
        int i = 0;
	
	bool key_pressed[MOVE_KEYS] = { false, false, false, false }; //Estado de teclas, true cuando esta apretada
	bool redraw = false;
	bool do_exit = false; 
 
        snake_node_t snake_H[MAX_LENGTH]; // initial snake
        snake_node_t *pHead = snake_H; // pointer to snake
        
        food_t gameFood; // food in game
        food_t *pGameFood = &gameFood; // pointer to food struct
        
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
 
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
 
	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
        
        for(i = 0; i < MAX_LENGTH; i++){ // snake create
            snake[i] = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE);
            if(!snake[i]) {
                    fprintf(stderr, "failed to create snake bitmap!\n");
                    al_destroy_timer(timer);
                    while(i >= 0){
                        al_destroy_bitmap(snake[i]);
                    }
                    return -1;
            }
        }
        
        food = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE); // food create
        if(!food){
            fprintf(stderr, "failed to create food bitmap!\n");
            al_destroy_timer(timer);
            for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
                al_destroy_bitmap(snake[i]);
            }
            return -1;
        }
        
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
                for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
                    al_destroy_bitmap(snake[i]);
                }
                al_destroy_bitmap(food);
		al_destroy_timer(timer);
		return -1;
	}
 
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
                    al_destroy_bitmap(snake[i]);
                }
                al_destroy_bitmap(food);
		al_destroy_event_queue(event_queue);
		return -1;
	}
	
        for(i = 0; i < MAX_LENGTH; i++){ // pink snake
            al_set_target_bitmap(snake[i]);
            al_clear_to_color(al_map_rgb(255, 0, 255));
        }
	
        al_set_target_bitmap(food); // Pink Food
        al_clear_to_color(al_map_rgb(255, 0, 255));
        
	al_set_target_bitmap(al_get_backbuffer(display));
  
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
 
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
        
        init_snake_struct(INIT_LENGTH, pHead); // set snake position coordenates
        
	al_start_timer(timer);

        // test variables
        int key_press = NO_KEY;
        int direction = KEY_RIGHT, dir_control;
        
        unsigned int refresh = 0;       
        
	while(!do_exit)
	{
		ALLEGRO_EVENT ev;
		if( al_get_next_event(event_queue, &ev) ) //Toma un evento de la cola
		{ 
			if(ev.type == ALLEGRO_EVENT_TIMER) 
			{
                            if(key_pressed[KEY_UP]){
                                key_press = KEY_UP;
                            }
                            else if(key_pressed[KEY_DOWN]){
                                key_press = KEY_DOWN;
                            }
                            else if(key_pressed[KEY_LEFT]){
                                key_press = KEY_LEFT;
                            }
                            else if(key_pressed[KEY_RIGHT]){
                                key_press = KEY_RIGHT;
                            }
                            
                            refresh++;
                            if((refresh % MOVE_FREQ) == 0)
                                redraw = true;
			}

			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
				do_exit = true;

			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) 
			{
				switch(ev.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						key_pressed[KEY_UP] = true;
						break;

					case ALLEGRO_KEY_DOWN:
						key_pressed[KEY_DOWN] = true;
						break;

					case ALLEGRO_KEY_LEFT: 
						key_pressed[KEY_LEFT] = true;
						break;

					case ALLEGRO_KEY_RIGHT:
						key_pressed[KEY_RIGHT] = true;
						break;
				}
			}

			else if(ev.type == ALLEGRO_EVENT_KEY_UP) 
			{
				switch(ev.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						key_pressed[KEY_UP] = false;
						break;

					case ALLEGRO_KEY_DOWN:
						key_pressed[KEY_DOWN] = false;
						break;

					case ALLEGRO_KEY_LEFT: 
						key_pressed[KEY_LEFT] = false;
						break;

					case ALLEGRO_KEY_RIGHT:
						key_pressed[KEY_RIGHT] = false;
						break;

					case ALLEGRO_KEY_ESCAPE:
						do_exit = true;
						break;
				}
			}
		}
 
		if(redraw && al_is_event_queue_empty(event_queue)) 
		{  
			redraw = false;                       
                        dir_control = validate_dir(direction, key_press);
                        if(dir_control == DIR_ERR){
                            key_press = NO_KEY;
                        }
                        calculate_newPos(pHead, direction, key_press);
                        set_newPos(pHead, snake);
                        if(key_press != NO_KEY){
                            direction = key_press;
                            key_press = NO_KEY;
                        }
                        
		}
	}
 
        for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
            al_destroy_bitmap(snake[i]);
        }
	al_destroy_timer(timer);
        al_destroy_bitmap(food);
	al_destroy_display(display);
	return 0;
}