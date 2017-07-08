#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include <time.h>
#include "config.h"    

#define HEAD 0
#define X_COORD 0
#define Y_COORD 1

#define INIT_LIVES 3
#define POINT_RATE 1
#define DEAD 0
#define ALIVE 1

#define INIT_LENGTH 5
#define MAX_LENGTH 300

#define MAX_LOGIC_WIDTH 100
#define MAX_LOGIC_HEIGHT 100

#define POLAR 2
#define NUM_OK -1
#define NUM_ERR -2

#define FOOD_EAT 7
#define NO_EAT 0

#define GROW_UP -3

#define COLISION -4
#define NO_COL -5


enum {LOGIC_STOP , LOGIC_PLAY , LOGIC_WIN_GAME};

enum {LOGIC_KEY_UP , LOGIC_KEY_RIGHT , LOGIC_KEY_DOWN , LOGIC_KEY_LEFT};

typedef struct snake_nodeT{ // snake single node
    int polar_pos[POLAR];
    
} snake_node_t;

typedef struct foodT{ // food struct
    int pos[POLAR];
    
} food_t;

typedef struct { /// game logic variables
    snake_node_t *pSnake;
    food_t *pFood;
    int world_height;
    int world_width;
    double speed; /// snake speed in seconds
    
    int snake_dir;
    int effective_dir;
    int game_status;
    double time_ref; 
    double call_time;
    
    
    int length; // snake length
    int lives; // snake lives
    int points; // actual game points
    int highscore; //highscore
}logic_vars_t;


// Game logic functions //
// -------------------- //
// init_snake_struct: inits standard snake with initial length with center coordenates
logic_vars_t* init_snake_struct(int start_length);

 /// al game logic managment. Must be called in periods of the configured period time.
int update_snake_logic(logic_vars_t* vars);

/// Configure snake size
void set_snake_game_size(logic_vars_t* game_vars,int width,int height);

/// destroy all logic game dynamic memory
void destroy_game(logic_vars_t* logic);

// calculate_newPos: calculates the next position of the head, and the others are shifted
// considering that prev_dir and key_in are not oposite, it also needs the actual length
void calculate_newPos(logic_vars_t* vars);

// calculate_foodPos: sets a random position for the next food to apear
void calculate_foodPos(logic_vars_t* vars);

// check_if_food_eaten: checks if snake eats food, returns NO_EAT if no eat, else GROW_UP
int check_if_food_eaten(logic_vars_t* vars);

// check_if_colission: checks if snake colisions with tail, if so, lives -1
void check_if_colision(logic_vars_t *vars);

// add_snake_node: adds a new node to the snake 
void add_snake_node(logic_vars_t* vars);
// -------------------- //

// game_status_refresh: refresh snake status, if lose returns DEAD, if lives ALIVE,
// and for food eaten FOOD_EAT
int game_status_refresh(logic_vars_t * game_vars);

/// Make game to handle new key pressed.
void handle_game_key_press(logic_vars_t* logic , int key);

// Snake length management //
// ----------------------- //
// init_length: sets initial length value
void init_length(logic_vars_t* vars,int data);

// get_length: returns actual length
int get_length(logic_vars_t* vars);

// inc_length: increments actual length value
int inc_length(logic_vars_t* vars);
// ----------------------- //

// Lives management functions // 
// -------------------------- // 
// init_lives: sets lives to start value, it must be called before starting game
void init_lives(logic_vars_t* vars);

// read_lives: returns actual number of lives, 0 is game over
int read_lives(logic_vars_t* vars);

// lose_lives: -1 live
void lose_live(logic_vars_t* vars);
// -------------------------- //

// Points management //
// ----------------- //
// read_points: return points from previus game
char *read_points(void);

// inc_points: adds 10 points to actual game
void inc_points(logic_vars_t* vars);

// reset_points
void reset_points(logic_vars_t* vars);

// write_points_file: in game finish, writes final points into file
void write_points_file(logic_vars_t* vars);
//
// ----------------- //
//// Configure game speed
void set_speed(logic_vars_t * game_vars , double speed);

/// Configure how fast will the logic update function be called
void set_logic_call_time(logic_vars_t* game_vars,double time);

/// Make game play!
void start_snake_logic(logic_vars_t* vars);

/// Stop game!
void stop_snake_logic(logic_vars_t* vars);

#endif /* SNAKE_LOGIC_H */

