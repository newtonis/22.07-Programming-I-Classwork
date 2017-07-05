#include <stdio.h>
#include "snake_pc.h"

void set_newPos(snake_node_t *pSnake, ALLEGRO_BITMAP *snake[MAX_LENGTH]){
    
    int j, length;
    
    length = count_snake_length(pSnake); // get actual snake length
    
    al_clear_to_color(BLACK);
    
    for(j = 0; j < length; j++){ // draws positions in buffer
        al_draw_bitmap(snake[j], ((pSnake+j)->polar_pos[X_COORD]), ((pSnake+j)->polar_pos[Y_COORD]), 0);
    }
   
    al_flip_display();
}

void set_foodPos(food_t *pFood, ALLEGRO_BITMAP *food){
    
    
}