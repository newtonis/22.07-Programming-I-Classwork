#include <stdio.h>
#include "snake_pc.h"
#include "interface.h"
#include "snake_graphic_base.h"


void update_graphic_game( logic_vars* game_data , full_graphic_content* content ){
    if(content->redraw && al_is_event_queue_empty(content->event_queue)) {  
        content->redraw = false;                       
        content->dir_control = validate_dir(content->direction, content->key_press);
    }
    if(content->dir_control == DIR_ERR){
        content->key_press = NO_KEY;
    }
    calculate_newPos(game_data->pSnake, content->direction, content->key_press);
    set_snakePos(game_data->pSnake, content->plot_game_graphic->snake);
    if(content->key_press != NO_KEY){
        content->direction = content->key_press;
        content->key_press = NO_KEY;
    }         
}

void update_pc_graphic_screen( logic_vars* game_data , graphic_vars* graphic_data){
    set_snakePos(game_data->pSnake ,  graphic_data->snake);
    set_foodPos(game_data->pFood    , graphic_data->food);
}

void set_snakePos(snake_node_t *pSnake, ALLEGRO_BITMAP *snake[MAX_LENGTH]){
    
    int j, length;
    
    length = count_snake_length(pSnake); // get actual snake length
    
    al_clear_to_color(BLACK);
    
    for(j = 0; j < length; j++){ // draws positions in buffer
        al_draw_bitmap(snake[j], ((pSnake+j)->polar_pos[X_COORD]), ((pSnake+j)->polar_pos[Y_COORD]), 0);
    }
   
    al_flip_display();
}

void set_foodPos(food_t *pFood, ALLEGRO_BITMAP *food){
    al_clear_to_color(BLACK);
    al_draw_bitmap(food, pFood->pos[X_COORD], pFood->pos[Y_COORD], 0);
    al_flip_display();
}