#include <stdio.h>
#include "snake_pc.h"
#include "interface.h"
#include "snake_graphic_base.h"


void update_game( logic_vars* game_data , full_graphic_content* content ){
    
    ALLEGRO_MOUSE_STATE state;
    int status;
    
    switch (content->front_end_status){
        case INITIAL_MENU:
            
            //al_get_mouse_state(&state);
            status = update_button(content->intial_menu->play_button);
            if (status){
                content->front_end_status = PLAY;
            }
            update_reg_box(content->intial_menu->width_config_ui);
            update_reg_box(content->intial_menu->height_config_ui);
        break;
        
        case PLAY:
            if(content->key_pressed[KEY_UP]){
                content->key_press = KEY_UP;
            }else if(content->key_pressed[KEY_DOWN]){
                content->key_press = KEY_DOWN;
            }else if(content->key_pressed[KEY_LEFT]){
                content->key_press = KEY_LEFT;
            }else if(content->key_pressed[KEY_RIGHT]){
                content->key_press = KEY_RIGHT;
            }

            content->dir_control = validate_dir(content->direction, content->key_press);

            if(content->dir_control == DIR_ERR){
                content->key_press = NO_KEY;
            }
            status = game_status_refresh(game_data->pSnake,game_data->pFood);
            if (status == FOOD_EAT){

            }
            calculate_newPos(game_data->pSnake, content->direction, content->key_press);
            if(content->key_press != NO_KEY){
                content->direction = content->key_press;
                content->key_press = NO_KEY;
            }    
        break;
    }
}

void update_pc_graphic_screen( logic_vars* game_data , full_graphic_content* content){
    
    switch (content->front_end_status){
        case INITIAL_MENU:
            al_clear_to_color(BLACK);
            draw_button(content->intial_menu->play_button);
            draw_reg_box(content->intial_menu->width_config_ui);
            draw_reg_box(content->intial_menu->height_config_ui);
        break;
        case PLAY:
            al_clear_to_color(BLACK);
            set_snakePos(game_data->pSnake ,  content->images->snake);
            set_foodPos( game_data->pFood   , content->images->food);
            
        break;
    }
    al_flip_display();
}

void set_snakePos(snake_node_t *pSnake, ALLEGRO_BITMAP *snake[MAX_LENGTH]){
    int j, length;
    
    length = get_length(); // get actual snake length
    
    for(j = 0; j < length; j++){ // draws positions in buffer
        al_draw_bitmap(snake[j], ((pSnake+j)->polar_pos[X_COORD]), ((pSnake+j)->polar_pos[Y_COORD]), 0);
    }
   
    
}

void set_foodPos(food_t *pFood, ALLEGRO_BITMAP *food){
  
    al_draw_bitmap(food, pFood->pos[X_COORD], pFood->pos[Y_COORD], 0);
    
}
