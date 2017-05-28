/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: newtonis
 *
 * Created on May 27, 2017, 8:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "game_logic.h"
#include "graphic.h"
#include "config.h"
/*
 * 
 */

void my_key_press(graphic_vars_t* vars, int key);

int main(int argc, char** argv) {
    graphic_vars_t g_vars; 
    game_vars_t logic_vars;
    
    game_init(&logic_vars);
    g_vars.key_press = my_key_press; // set callback
    g_vars.logic_ref = &logic_vars; // set logic reference for front end to make callbacks
    fe_init_graphic(&g_vars);
    
    g_vars.status_text    = fe_add_show_text(&g_vars , SCREEN_W/2 , SCREEN_H/4);
    g_vars.time_left_text = fe_add_show_text(&g_vars ,SCREEN_W/2 , SCREEN_H/4*3);
    
    copy_str("Press Enter to start" , g_vars.status_text->text);
    copy_str("-" ,g_vars.time_left_text->text);
    
    while (!g_vars.end){
        int status , sec;
        game_update(&logic_vars , &status , &sec);
        if (status == GAME_PLAYING){ // we need to update status text all the time if game is playing
            char new_char[DEF_SZ];
            new_char[0] = sec + '0';
            new_char[1] = '\0';
            strcat(new_char , " seconds left");
            copy_str( new_char , g_vars.status_text->text) ;
        }else if(status == TIME_OUT){
            copy_str("Time Out",g_vars.status_text->text);
            copy_str("Press Enter to continue",g_vars.time_left_text->text);
            game_init(&logic_vars);
        }
        
        
        fe_update_graphic(&g_vars);
        fe_update_events(&g_vars);
        
        
    }
    fe_end_graphic(&g_vars);
    
            
    return (EXIT_SUCCESS);
}



void my_key_press(graphic_vars_t* vars, int key){

    switch (vars->logic_ref->status){
        case LOSE:
        case WIN:
        case GAME_PAUSED:
            if (key == ALLEGRO_KEY_ENTER){
                game_start(vars->logic_ref); //// start to play game
            }
        break;
        case GAME_PLAYING:
            if (key >= ALLEGRO_KEY_0 && key <= ALLEGRO_KEY_9){
                int ans;
                game_guess(vars->logic_ref , key - ALLEGRO_KEY_0 , &ans);
                
                if (vars->logic_ref->status == WIN){
                    copy_str("Press Enter to continue",vars->status_text->text);
                }else{
                    copy_str("You lose!",vars->status_text->text);
                }
                char new_char[DEF_SZ] =  "press enter, answer: ";
                int sz = strlen(new_char);
                new_char[sz   ] = (char)ans + '0';
                new_char[sz +1] = '\0';
                copy_str( new_char,vars->time_left_text->text) ;
            }
        break;
        
        
    }
}