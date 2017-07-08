#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake_logic.h"
#include "utils.h"

#define STRING_MAX 10


static FILE *points_log = NULL;


logic_vars_t* init_snake_struct(int start_length){
    logic_vars_t* logic_vars = malloc(sizeof(logic_vars_t));
    snake_node_t* pSnake = malloc(sizeof(pSnake)*MAX_LENGTH);
    logic_vars->pFood = malloc(sizeof(food_t));
    logic_vars->pSnake = pSnake;
    
    if (!logic_vars || !pSnake){
        fprintf(stderr,"Error, can't allocate memory");
        exit(1);
    }
    int j;
    for(j = 0; j < start_length; j++){ 
        pSnake[j].polar_pos[X_COORD] = start_length-j-1;//(((SCREEN_W/CUADRADITO_SIZE)/2)*CUADRADITO_SIZE) - (j*CUADRADITO_SIZE);
        pSnake[j].polar_pos[Y_COORD] = 0;//(((SCREEN_H/CUADRADITO_SIZE)/2)*CUADRADITO_SIZE);
    }  
    logic_vars->game_status = LOGIC_STOP; // game is paused before starting
    logic_vars->snake_dir = LOGIC_KEY_RIGHT;
    logic_vars->time_ref = 0;
    
    //calculate_foodPos(logic_vars); // first food 
    init_lives(logic_vars);
    init_length(logic_vars,start_length);
    
    return logic_vars;
}
void set_snake_game_size(logic_vars_t* game_vars,int width,int height){
    game_vars->world_width = width;
    game_vars->world_height = height;
}
void destroy_game(logic_vars_t* logic){
    free(logic->pFood);
    free(logic->pSnake);
    free(logic);
}
void handle_game_key_press(logic_vars_t* logic , int key){
    if (logic->game_status == LOGIC_PLAY){ // is the game playing?
        if ( (key+2)%4 != logic->effective_dir ){ // check if key pressed represent the opposed direction
            logic->snake_dir = key;
        }
    }
}
void start_snake_logic(logic_vars_t* vars){
    vars->game_status = LOGIC_PLAY;
    vars->points = 0;
    
    calculate_foodPos(vars);
}
void stop_snake_logic(logic_vars_t* vars){
    vars->game_status = LOGIC_STOP;
}
int update_snake_logic(logic_vars_t* vars){
    int ans;
    if (vars->game_status == LOGIC_PLAY){
        vars->time_ref += vars->call_time; 
        if (vars->time_ref >= vars->speed){
            vars->time_ref = 0; // reset counter
            
            /// Now advance snake
            calculate_newPos(vars );
            
            ans = game_status_refresh(vars);
            if (ans == DEAD){
                stop_snake_logic(vars);
            }
        }
    }else{
        ans = -1;
    }
    
    return ans;
}

void calculate_newPos(logic_vars_t* vars){
    snake_node_t *pSnake = vars->pSnake;
    int move, k, length;
    float x_head, y_head;
    // the first coordenates are for the head of the snake
    x_head = pSnake[0].polar_pos[X_COORD];
    y_head = pSnake[0].polar_pos[Y_COORD];
    
    move = vars->snake_dir;
    vars->effective_dir = vars->snake_dir;
    
    switch(move){ // gets new head pos
        case LOGIC_KEY_UP:
            y_head --;
            if(y_head < 0)
                y_head = vars->world_height - 1;
        break;
        case LOGIC_KEY_DOWN:
            y_head ++;
            if(y_head >= vars->world_height) y_head = 0;
        break;
        case LOGIC_KEY_LEFT:
            x_head --;
            if(x_head < 0) {
                x_head = vars->world_width - 1;
            }
        break;
        case LOGIC_KEY_RIGHT:
            x_head ++;
            if(x_head >= vars->world_width) x_head = 0;
        break;
    }
    
    length = get_length(vars);
    
    
    for(k = length; k > 0; k--){ // shift all positions
        pSnake[k].polar_pos[X_COORD] = pSnake[k-1].polar_pos[X_COORD];
        pSnake[k].polar_pos[Y_COORD] = pSnake[k-1].polar_pos[Y_COORD];
        //snake_pos[X_COORD][k] = snake_pos[X_COORD][k-1];
        //snake_pos[Y_COORD][k] = snake_pos[Y_COORD][k-1];
    }
    pSnake[0].polar_pos[X_COORD] = x_head;
    pSnake[0].polar_pos[Y_COORD] = y_head;
    //snake_pos[X_COORD][HEAD] = x_head; // set new head pos after shifting
    //snake_pos[Y_COORD][HEAD] = y_head;
}


void calculate_foodPos(logic_vars_t* game_vars){
    
    snake_node_t* pSnake = game_vars->pSnake;
    
    float x_pos, y_pos;
    
    int length = get_length(game_vars); // we need snake length
    
    srand(time(NULL));
    
    int x_candidates[MAX_LOGIC_WIDTH];
    int y_candidates[MAX_LOGIC_HEIGHT]; 
    
    init_empty_array(x_candidates,game_vars->world_width);
    init_empty_array(y_candidates,game_vars->world_height);
    
    /// Mark all invalid places
    int i;
    for (i = 0;i < length;i++){
        x_candidates[ game_vars->pSnake[i].polar_pos[0] ] = 1;
        y_candidates[ game_vars->pSnake[i].polar_pos[1] ] = 1;
    }
    
    int x_cand = rand() % game_vars->world_width;
    int y_cand = rand() % game_vars->world_height;
    
    int loop = 0;
    int total_tiles = game_vars->world_height * game_vars->world_width;
    while (x_candidates[x_cand] && y_candidates[y_cand] && loop < total_tiles){
        x_cand ++;
        if (x_cand >= game_vars->world_width){
            x_cand = 0;
            y_cand ++;
            if (y_cand >= game_vars->world_height){
                y_cand = 0;
            }
        }
        loop = 0;
    }
    if (loop == total_tiles){
        game_vars->game_status = LOGIC_WIN_GAME;
    }else{
        game_vars->pFood->pos[X_COORD] = x_cand;
        game_vars->pFood->pos[Y_COORD] = y_cand;
    }
   
    
}

int check_if_food_eaten(logic_vars_t* vars){
    
    food_t *pFood = vars->pFood;
    snake_node_t *pSnake = vars->pSnake;
    
    int i, length, x_match, y_match;

    
    length = get_length(vars);
    
    
    if(pSnake[0].polar_pos[X_COORD] == pFood->pos[X_COORD] && pSnake[0].polar_pos[Y_COORD] == pFood->pos[Y_COORD]){
           return GROW_UP;
    }else{
        return NO_EAT;
    }
}

void check_if_colision(logic_vars_t *vars){
    snake_node_t* pSnake = vars->pSnake;
    
    int i, x_col, y_col, length;
    x_col = NO_COL;
    y_col = NO_COL;
    
    length = get_length(vars);
    
    for(i = (HEAD+1); i < length; i++){
        if((pSnake[0].polar_pos[X_COORD]) == (pSnake[i].polar_pos[X_COORD])){
            if((pSnake->polar_pos[Y_COORD]) == ((pSnake+i)->polar_pos[Y_COORD])){
                x_col = COLISION;
                y_col = COLISION;
            }
        }

    }
    
    if((x_col == COLISION)&&(y_col == COLISION)){
        lose_live(vars);
    }
}

void add_snake_node(logic_vars_t* vars){
    
    int aux_l;
    
    aux_l = get_length(vars);
   
    
    inc_length(vars);
}

int game_status_refresh(logic_vars_t * game_vars){
    
    int live_status, food_status;
    check_if_colision(game_vars);
    
    live_status = read_lives(game_vars);
    if(live_status == 0){
        return DEAD;
    }
    
    food_status = check_if_food_eaten(game_vars);
    if(food_status == GROW_UP){
        add_snake_node(game_vars);
        inc_points(game_vars);
        calculate_foodPos(game_vars);
        return FOOD_EAT;
    }else if(food_status == NO_EAT){
        return ALIVE;
    }
    
}

// Snake length management //

void init_length(logic_vars_t* vars,int data){
    vars->length = data;
}

int get_length(logic_vars_t* vars){
    return vars->length;
}

int inc_length(logic_vars_t* vars){
    vars->length++;
}

// Live management functions //

void init_lives(logic_vars_t* vars){
   vars->lives = INIT_LIVES; 
}

int read_lives(logic_vars_t* vars){
    return vars->lives;
}

void lose_live(logic_vars_t* vars){
    if(vars->lives > 0){
        vars->lives--;
    }
}

/// configure game speed
void set_speed(logic_vars_t * game_vars , double speed){
    game_vars->speed = speed;
}


// Points management //


char *read_points(void){
    points_log = fopen("game_points.txt", "r");
    char *msj_points = fgets(msj_points, STRING_MAX, points_log);
    return msj_points;
}

void inc_points(logic_vars_t* vars){
    vars->points += POINT_RATE;
}

void reset_points(logic_vars_t* vars){
    vars->points = 0;
}

void write_points_file(logic_vars_t* vars){
    points_log = fopen("game_points.txt", "w");
    fprintf(points_log, "%d", vars->points);
    fclose(points_log);
}

void set_logic_call_time(logic_vars_t* game_vars,double time){
    game_vars->call_time = time;
}