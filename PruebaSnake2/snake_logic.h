#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include "config.h"    

#define HEAD 0
#define X_COORD 0
#define Y_COORD 1

#define INIT_LIVES 3
#define POINT_RATE 10

#define INIT_LENGTH 5
#define MAX_LENGTH 10
#define POLAR 2
#define NUM_OK -1
#define NUM_ERR -2

#define FOOD_EAT 1
#define NO_EAT 0

#define GROW_UP -3

#define COLISION -4
#define NO_COL -5

typedef struct snake_nodeT{ // snake single node
    float polar_pos[POLAR];
    struct snake_nodeT *pNode; 
    
} snake_node_t;

typedef struct foodT{ // food struct
    float pos[POLAR];
    
} food_t;

// Game logic functions //
// -------------------- //
// init_snake_struct: inits standard snake with initial length with center coordenates
void init_snake_struct(int start_length, snake_node_t *pSnake);

// validate_dir: cheks if the previus direction and the new direction are not oposite
int validate_dir(int prev_dir, int new_dir);

// calculate_newPos: calculates the next position of the head, and the others are shifted
// considering that prev_dir and key_in are not oposite, it also needs the actual length
void calculate_newPos(snake_node_t *pSnake, int prev_dir, int new_dir);

// calculate_foodPos: sets a random position for the next food to apear
void calculate_foodPos(snake_node_t *pSnake, food_t *pFood);

// check_if_food_eaten: checks if snake eats food, returns 0 if no eat, else 1
int check_if_food_eaten(snake_node_t *pSnake, food_t *pFood);

// check_if_colission: checks if snake colisions with tail, if so, lives -1
void check_if_colision(snake_node_t *pSnake);

// add_snake_node: adds a new node to the snake 
void add_snake_node(snake_node_t *pSnake);
// -------------------- //

// Snake length management //
// ----------------------- //
// init_length: sets initial length value
void init_length(int data);

// get_length: returns actual length
int get_length(void);

// inc_length: increments actual length value
void inc_length(void);
// ----------------------- //

// Lives management functions // 
// -------------------------- // 
// init_lives: sets lives to start value, it must be called before starting game
void init_lives(void);

// read_lives: returns actual number of lives, 0 is game over
int read_lives(void);

// lose_lives: -1 live
void lose_live(void);

// reset_lives: reset lives to initial value
void reset_lives(void);
// -------------------------- //

// Points management //
// ----------------- //
// read_points: return points from previus game
int read_points(void);

// inc_points: adds 10 points to actual game
void inc_points(void);

// reset_points
void reset_points(void);

// write_points_file: in game finish, writes final points into file
void write_points_file(void);
//
// ----------------- //

#endif /* SNAKE_LOGIC_H */

