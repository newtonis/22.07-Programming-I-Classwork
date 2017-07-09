#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake_logic.h"
#include "utils.h"

#define STRING_MAX 10



double diff_array[CNT_DIFF][2] = { // difficulty levels speeds (in seconds) and grow rates
    { 0.100, 1 },
    { 0.070, 2 },
    { 0.050, 3 }
};

logic_vars_t* init_snake_struct(){
    logic_vars_t* logic_vars = malloc(sizeof(logic_vars_t));
    snake_node_t* pSnake = malloc(sizeof(pSnake)*MAX_LENGTH);
    logic_vars->pFood = malloc(sizeof(food_t));
    logic_vars->pSnake = pSnake;
    logic_vars->start_length = INIT_LENGTH;
    
    if (!logic_vars || !pSnake){
        fprintf(stderr,"Error, can't allocate memory");
        exit(1);
    }
    
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
    printf("Start! ");
    snake_node_t *pSnake = vars->pSnake;
    
    int j;
    for(j = 0; j < vars->start_length; j++){ 
        pSnake[j].polar_pos[X_COORD] = vars->start_length-j-1;//(((SCREEN_W/CUADRADITO_SIZE)/2)*CUADRADITO_SIZE) - (j*CUADRADITO_SIZE);
        pSnake[j].polar_pos[Y_COORD] = 0;//(((SCREEN_H/CUADRADITO_SIZE)/2)*CUADRADITO_SIZE);
    }  
    vars->game_status = LOGIC_STOP; // game is paused before starting
    vars->snake_dir = LOGIC_KEY_RIGHT;
    vars->time_ref  = 0;
    
    //calculate_foodPos(logic_vars); // first food 
    
    init_length(vars,vars->start_length);
    read_points(vars); // read scores
    
    vars->game_status = LOGIC_PLAY;
    vars->points = 0;
    
    calculate_foodPos(vars);
}
void stop_snake_logic(logic_vars_t* vars){
    vars->game_status = LOGIC_STOP;
}
int update_snake_logic(logic_vars_t* vars){
    int ans = -1;
    if (vars->game_status == LOGIC_PLAY){
        vars->time_ref += vars->call_time; 
        if (vars->time_ref >= vars->speed){
            vars->time_ref = 0; // reset counter
            
            /// Now advance snake
            calculate_newPos(vars );
            
            ans = game_status_refresh(vars);
            if (ans == DEAD){
                write_points_file(vars);
                stop_snake_logic(vars);
            }
        }
        
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
        loop ++;
    }
    if (loop == total_tiles){
        game_vars->game_status = LOGIC_WIN_GAME; /// very strange situation, the player wins!. Stop game in such case
        stop_snake_logic(game_vars);
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

int check_if_colision(logic_vars_t *vars){
    snake_node_t* pSnake = vars->pSnake;
    
    int i, x_col, y_col, length;
    x_col = NO_COL;
    y_col = NO_COL;
    
    length = get_length(vars);
    
    for(i = (HEAD+1); i < length; i++){
        if(pSnake[0].polar_pos[X_COORD] == pSnake[i].polar_pos[X_COORD]){
            if(pSnake[0].polar_pos[Y_COORD] == (pSnake[i].polar_pos[Y_COORD])){
                x_col = COLISION;
                y_col = COLISION;
              
            }
        }

    }
    if((x_col == COLISION) && (y_col == COLISION)){
        return 1;
    }else{
        return 0;
    }
}

void add_snake_node(logic_vars_t* vars){
    int aux_l;
    aux_l = get_length(vars);
    vars->pSnake[aux_l].polar_pos[0] = vars->pSnake[aux_l-1].polar_pos[0];
    vars->pSnake[aux_l].polar_pos[1] = vars->pSnake[aux_l-1].polar_pos[1];
    inc_length(vars);
}

int game_status_refresh(logic_vars_t * game_vars){
    
    int live_status, food_status;
    int col = check_if_colision(game_vars);
    
    int ans;
    if(col){
        ans = DEAD;
    }else{
        food_status = check_if_food_eaten(game_vars);
        if(food_status == GROW_UP){
            int i;
            for (i = 0;i < game_vars->snake_grow;i++){
                add_snake_node(game_vars);
            }
            inc_points(game_vars);
            calculate_foodPos(game_vars);
            ans =  FOOD_EAT;
        }else if(food_status == NO_EAT){
            ans = ALIVE;
        }else{
            ans = -1;
        }
    }
    return ans;
    
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
void set_game_level(logic_vars_t * game_vars , double speed,int snake_grow){
    game_vars->speed = speed;
    game_vars->snake_grow = snake_grow;
}


// Points management //


void read_points(logic_vars_t* vars){
    FILE* points_log = fopen(HIGHSCORES_FILE, "r");
    
    if (!points_log){
        fprintf(stderr, "Fail to open points data file");
        exit(1);
    }
    
    int i;
    for (i = 0;i < CNT_DIFF;i++){
        fscanf(points_log , "%d" , &vars->highscore[i]);
    }
    
    fclose(points_log);
}

int get_highscore(logic_vars_t* vars){
   return vars->highscore[vars->diff_level];
}
void inc_points(logic_vars_t* vars){
    vars->points += POINT_RATE;
    vars->highscore[vars->diff_level] = max( vars->highscore[vars->diff_level]  , vars->points ); // update highscore
}

void reset_points(logic_vars_t* vars){
    vars->points = 0;
}

void write_points_file(logic_vars_t* vars){

    //fprintf(points_log, "%d", vars->points);
    FILE* points_log = fopen(HIGHSCORES_FILE,"w+");
    
    int i;
    for (i = 0;i < CNT_DIFF;i++){
        fprintf(points_log,"%d\n",vars->highscore[i]);
    }
    
    fclose(points_log);
}

void set_logic_call_time(logic_vars_t* game_vars,double time){
    game_vars->call_time = time;
}

void set_game_difficulty(logic_vars_t* game_vars,int dif_level){
    
    if (dif_level <= CNT_DIFF && dif_level >= 1){
        dif_level--;
        game_vars->diff_level = dif_level;
        set_game_level(game_vars,diff_array[dif_level][0],diff_array[dif_level][1]);
    }else{
        fprintf(stderr,"Wrong usage of game logic\n");
        exit(1);
    }
}