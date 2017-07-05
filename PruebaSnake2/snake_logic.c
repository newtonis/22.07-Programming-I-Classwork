#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake_logic.h"

static int length; // snake length
static int lives; // snake lives
static int points; // actual game points
static FILE *points_log = NULL;

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
    
    init_length(start_length);
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
            if(y_head <= (WORLD_TOP -1))
                y_head = WORLD_BOTTOM - CUADRADITO_SIZE;
            break;
        case KEY_DOWN:
            y_head += MOVE_RATE;
            if(y_head >= WORLD_BOTTOM)
                y_head = WORLD_TOP +1;
            break;
        case KEY_LEFT:
            x_head -= MOVE_RATE;
            if(x_head <= (WORLD_MIN_LEFT -1))
                x_head = WORLD_MAX_RIGHT - CUADRADITO_SIZE;
            break;
        case KEY_RIGHT:
            x_head += MOVE_RATE;
            if(x_head >= WORLD_MAX_RIGHT)
                x_head = WORLD_MIN_LEFT +1;
            break;
    }
    
    length = get_length();
    
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
/*
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
*/
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
    
    length = get_length(); // we need snake length
    
    srand(time(NULL));
    
    while(control != NUM_OK){
        i = 0; // start
        x_pos = rand()%(SCREEN_W - CUADRADITO_SIZE); // generate random x coordenate
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
        y_pos = rand()%(SCREEN_H - CUADRADITO_SIZE); // generate random x coordenate
        while( (i < length) && (((pSnake+i)->polar_pos[Y_COORD]) != y_pos)){
            i++;            
        }
        
        if(i == length){
            control = NUM_OK;
        }
    }
   
    pFood->pos[X_COORD] = x_pos;
    pFood->pos[Y_COORD] = y_pos;
    
}

int check_if_food_eaten(snake_node_t *pSnake, food_t *pFood){
    
    int i, length, x_match, y_match;
    x_match = NO_EAT;
    y_match = NO_EAT;
    
    length = get_length();
    
    for(i = 0; i < length; i++){
        if((pSnake+i)->polar_pos[X_COORD] == (pFood->pos[X_COORD])){
            x_match = FOOD_EAT;
        }
        if((pSnake+i)->polar_pos[Y_COORD] == (pFood->pos[Y_COORD])){
            y_match = FOOD_EAT;
        }
    }
    
    if((x_match == FOOD_EAT)&&(y_match == FOOD_EAT)){
        return GROW_UP;
    }
    else{
        return NO_EAT;
    }
}

void check_if_colision(snake_node_t *pSnake){
    
    int i, x_col, y_col, length;
    x_col = NO_COL;
    y_col = NO_COL;
    
    length = get_length();
    
    for(i = (HEAD+1); i < length; i++){
        if((pSnake->polar_pos[X_COORD]) == ((pSnake+i)->polar_pos[X_COORD])){
            x_col = COLISION;
        }
        if((pSnake->polar_pos[Y_COORD]) == ((pSnake+i)->polar_pos[Y_COORD])){
            y_col = COLISION;
        }
    }
    
    if((x_col == COLISION)&&(y_col == COLISION)){
        lose_live();
    }
}

void add_snake_node(snake_node_t *pSnake){
    
    int aux_l;
    
    aux_l = get_length();
    (pSnake+aux_l-1)->pNode = (pSnake+aux_l);
    (pSnake+aux_l)->pNode = NULL;
    
    inc_length();
}

int game_status_refresh(snake_node_t *pSnake, food_t *pFood){
    
    int live_status, food_status;
    check_if_colision(pSnake);
    
    live_status = read_lives();
    if(live_status == 0){
        return DEAD;
    }
    
    food_status = check_if_food_eaten(pSnake, pFood);
    if(food_status == GROW_UP){
        add_snake_node(pSnake);
        calculate_foodPos();
        return FOOD_EAT;
    }else if(food_status == NO_EAT){
        return ALIVE;
    }
    
}

// Snake length management //

void init_length(int data){
    length = data;
}

int get_length(void){
    return length;
}

void inc_length(void){
    length++;
}

// Live management functions //

void init_lives(void){
   lives = INIT_LIVES; 
}

int read_lives(void){
    return lives;
}

void lose_live(void){
    if(lives > 0){
        lives--;
    }
}

// Points management //

int read_points(void){
    
}

void inc_points(void){
    points += POINT_RATE;
}

void reset_points(void){
    points = 0;
}

void write_points_file(void){
    points_log = fopen("game_points.txt", "w");
    fprintf(points_log, "%d", points);
    fclose(points_log);
}

