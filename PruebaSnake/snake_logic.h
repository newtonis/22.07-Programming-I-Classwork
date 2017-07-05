#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include "config.h"    

#define HEAD 0
#define X_COORD 0
#define Y_COORD 1

#define INIT_LENGTH 3
#define MAX_LENGTH 10
#define POLAR 2
#define NUM_OK -1
#define NUM_ERR -2

typedef struct snake_nodeT{ // snake single node
    float polar_pos[POLAR];
    struct snake_nodeT *pNode; 
    
} snake_node_t;

typedef struct foodT{ // food struct
    float pos[POLAR];
    
} food_t;

// init_snake_struct: inits standard snake with initial length with center coordenates
void init_snake_struct(int start_length, snake_node_t *pSnake);

// count_snake_length: returns actual number of nodes
int count_snake_length(snake_node_t *pSnake);

// validate_dir: cheks if the previus direction and the new direction are not oposite
int validate_dir(int prev_dir, int new_dir);

// calculate_newPos: calculates the next position of the head, and the others are shifted
// considering that prev_dir and key_in are not oposite, it also needs the actual length
void calculate_newPos(snake_node_t *pSnake, int prev_dir, int new_dir);

// calculate_foodPos: sets a random position for the next food to apear
void calculate_foodPos(snake_node_t *pSnake, food_t *pFood);

// check_if_food_eaten: checks if snake eats food
int check_if_food_eaten(snake_node_t *pSnake, food_t *pFood);

#endif /* SNAKE_LOGIC_H */

