/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game_logic.c
 * Author: newtonis
 *
 * Created on May 27, 2017, 8:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "game_logic.h"
#include "utils.h"

void game_init(game_vars_t *game){
    game->status = GAME_PAUSED;
    clock_reset_to(&game->clock , GAME_TIME );
}
void game_start(game_vars_t * game){
    srand(time(NULL));
    
    clock_run(&game->clock);
    game->status = GAME_PLAYING;
    game->number = rand() % MAX_NUMBER + 1;
    
} // genertae random number and start clock
void  game_guess(game_vars_t * game, int number ,int *answer){
    if (game->status == GAME_PLAYING){
        if (number == game->number){
            game->status = WIN;
        }else{
            game->status = LOSE;
        }
    }
    *answer = game->number;
} // user guesses a number, return game status
void  game_update(game_vars_t * game, int *status , int *sec ){
    if (game->status == GAME_PLAYING){    if (clock_update(&game->clock)){
            clock_get_values(&game->clock,sec);
        }else{
            game->status = TIME_OUT;
        }
    }
    *status = game->status;
}
