/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game_logic.h
 * Author: newtonis
 *
 * Created on May 27, 2017, 8:39 PM
 */

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"       
    
enum { GAME_PAUSED , GAME_PLAYING , TIME_OUT , WIN , LOSE }; 
    
typedef struct {
    rev_clock_t clock;
    int number;
    int status;
}game_vars_t;
    

void game_init(game_vars_t *game);
void game_start(game_vars_t * game); // generte random number and start clock
void game_guess(game_vars_t * game, int number ,int *answer); // user guesses a number, return game status
void game_update(game_vars_t * game, int *status , int *sec );

#ifdef __cplusplus
}
#endif

#endif /* GAME_LOGIC_H */

