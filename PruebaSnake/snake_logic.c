#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake_logic.h"

void init_snake_struct(int start_length, snake_node_t *pSnake){
    int j;
    
    for(j = 0; j < start_length; j++){ 
        
        (pSnake+j)->polar_pos[X_COORD] = (SCREEN_W/2) - (j*CUADRADITO_SIZE);
        (pSnake+j)->polar_pos[Y_COORD] = (SCREEN_H/2);
        if(j < start_length-1){
            (pSnake+j)->pNode = (pSnake+j+1); // point to next node
        }  
    }
    (pSnake+start_length-1)->pNode = NULL; // the last is the tail
}

void calculate_newPos(snake_node_t *pSnake, int prev_dir, int new_dir){
    
    int move, k, length;
    float x_head, y_head;
    // the first coordenates are for the head of the snake
    x_head = (pSnake)->polar_pos[X_COORD];
    y_head = (pSnake)->polar_pos[Y_COORD];
    
    if(new_dir == NO_KEY){
        move = prev_dir;
    }
    else{
        move = new_dir;
    }
    switch(move){ // gets new head pos
        case KEY_UP:
            y_head -= MOVE_RATE;
            if(y_head <= WORLD_TOP)
                y_head = WORLD_BOTTOM - CUADRADITO_SIZE;
            break;
        case KEY_DOWN:
            y_head += MOVE_RATE;
            if(y_head >= WORLD_BOTTOM)
                y_head = WORLD_TOP + CUADRADITO_SIZE;
            break;
        case KEY_LEFT:
            x_head -= MOVE_RATE;
            if(x_head <= WORLD_MIN_LEFT)
                x_head = WORLD_MAX_RIGHT - CUADRADITO_SIZE;
            break;
        case KEY_RIGHT:
            x_head += MOVE_RATE;
            if(x_head >= WORLD_MAX_RIGHT)
                x_head = WORLD_MIN_LEFT + CUADRADITO_SIZE;
            break;
    }
    
    length = count_snake_length(pSnake);
    
    for(k = length; k > 0; k--){ // shift all positions
        (pSnake+k)->polar_pos[X_COORD] = (pSnake+k-1)->polar_pos[X_COORD];
        (pSnake+k)->polar_pos[Y_COORD] = (pSnake+k-1)->polar_pos[Y_COORD];
        //snake_pos[X_COORD][k] = snake_pos[X_COORD][k-1];
        //snake_pos[Y_COORD][k] = snake_pos[Y_COORD][k-1];
    }
    pSnake->polar_pos[X_COORD] = x_head;
    pSnake->polar_pos[Y_COORD] = y_head;
    //snake_pos[X_COORD][HEAD] = x_head; // set new head pos after shifting
    //snake_pos[Y_COORD][HEAD] = y_head;
}

int count_snake_length(snake_node_t *pSnake){
    int length;
    snake_node_t *pCheck;
    
    if((pCheck = pSnake->pNode) == NULL)
        return 0;
    
    for(length = 0; (pCheck = (pSnake+length)->pNode) != NULL; length++){
        // counts actual length
    }
    return length+1; // we need total nodes
}

int validate_dir(int prev_dir, int new_dir){
    
    int aux;
    
    if((prev_dir == KEY_UP)&&(new_dir == KEY_DOWN)){
        aux = DIR_ERR;
    }
    else if((prev_dir == KEY_DOWN)&&(new_dir == KEY_UP)){
        aux = DIR_ERR;
    }
    else if((prev_dir == KEY_LEFT)&&(new_dir == KEY_RIGHT)){
        aux = DIR_ERR;
    }    
    else if((prev_dir == KEY_RIGHT)&&(new_dir == KEY_LEFT)){
        aux = DIR_ERR;
    }
    else{
        aux = DIR_OK;
    }
    
    return aux;
}

void calculate_foodPos(snake_node_t *pSnake, food_t *pFood){
    
    float x_pos, y_pos;
    int control = NUM_ERR, i, length;
    
    length = count_snake_length(pSnake); // we need snake length
    
    srand(time(NULL));
    
    while(control != NUM_OK){
        i = 0; // start
        x_pos = rand()%SCREEN_W; // generate random x coordenate
        while( (i < length) && (((pSnake+i)->polar_pos[X_COORD]) != x_pos)){
            i++;            
        }
        
        if(i == length){
            control = NUM_OK;
        }
    }
    
    control = NUM_ERR;
    i = 0;
    
    while(control != NUM_OK){
        i = 0; // start
        y_pos = rand()%SCREEN_W; // generate random x coordenate
        while( (i < length) && (((pSnake+i)->polar_pos[Y_COORD]) != y_pos)){
            i++;            
        }
        
        if(i == length){
            control = NUM_OK;
        }
    }
   
}
