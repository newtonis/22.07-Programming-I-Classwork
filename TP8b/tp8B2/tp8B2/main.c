#include <stdio.h>
#include "game_logic.h"
#include "graphic.h"
#include "config.h"
#include "sound.h"


/*
 * 
 */

void my_key_press(graphic_vars_t* vars, int key); //


    ALLEGRO_SAMPLE *win_audio=NULL;         
    ALLEGRO_SAMPLE *lose_audio=NULL;
    ALLEGRO_SAMPLE *loop_audio=NULL;
    ALLEGRO_SAMPLE_INSTANCE *instance1=NULL;
    ALLEGRO_SAMPLE_INSTANCE *instance2=NULL;
   

int main(int argc, char** argv) {

    
     ALLEGRO_SAMPLE_INSTANCE *instance3=NULL;
      
     init_audio();

    al_play_sample(loop_audio, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL); // we turn on the loop audio 

  
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
        

        fe_update_events(&g_vars); 
        
    }
    
    fe_end_graphic(&g_vars);
    fe_end_audio();
    
    
            
    return (EXIT_SUCCESS);
}



void my_key_press(graphic_vars_t* vars, int key){

    switch (vars->logic_ref->status){
        case LOSE: //
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
                    copy_str("You Win!",vars->status_text->text);
                    
                   al_play_sample_instance(instance1);
                    
                }else{
                    copy_str("You lose!",vars->status_text->text);
                    
                    al_play_sample_instance(instance2);
                    
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
