#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include "snake_pc.h"
#include "interface.h"
#include "config.h"
#include "snake_graphic_base.h"
#include "utils.h"

/*
 * snake_pc.c
 * In this file everything related to screen-drawing and front-end actions is written
 * Most things used in this file are declared/initialized in snake_graphic_base.h/snake_graphic_base.c
 */


void update_game( logic_vars_t* game_data , full_graphic_content* content ){
    
    ALLEGRO_MOUSE_STATE state;
    int status;
    
    /// Main front end Machine
    switch (content->front_end_status){ 
        case INITIAL_MENU:
            //al_get_mouse_state(&state);
            status = update_button(content->intial_menu->play_button);
            if (status){
                content->front_end_status = PLAY;
                handle_start_game( game_data , content );
            }
            update_reg_box(content->intial_menu->width_config_ui);
            update_reg_box(content->intial_menu->height_config_ui);
            update_reg_box(content->intial_menu->diff_ui);
        break;
        
        case PLAY:
            status = update_snake_logic(game_data);
            if (status == FOOD_EAT){
                update_scoreboard(game_data,content);
            }else if(status == DEAD){
                set_scoreboard_to_white(content);
                content->front_end_status = GAME_OVER;
            }
        break;
        case GAME_OVER:
            status = update_button(content->scoreboard->restart_button);
            if (status){
                set_scoreboard_to_grey(content);
                content->front_end_status = INITIAL_MENU;
            }
        break;
    }
}

void update_scoreboard(logic_vars_t * vars , full_graphic_content *content){
    int_to_str(vars->points,content->scoreboard->score_number_text->text,SCORE_NUMBERS);
    int_to_str(get_highscore(vars),content->scoreboard->high_score_number_text->text,SCORE_NUMBERS);
}
void set_scoreboard_to_white(full_graphic_content *content){
    set_show_text_color(content->scoreboard->high_score,BOX_COLOR);
    set_show_text_color(content->scoreboard->high_score_number_text,BOX_COLOR);
    set_show_text_color(content->scoreboard->score_number_text,BOX_COLOR);
    set_show_text_color(content->scoreboard->score_text,BOX_COLOR);
}
void set_scoreboard_to_grey(full_graphic_content *content){
    set_show_text_color(content->scoreboard->high_score,LIGHT_BOX_COLOR);
    set_show_text_color(content->scoreboard->high_score_number_text,LIGHT_BOX_COLOR);
    set_show_text_color(content->scoreboard->score_number_text,LIGHT_BOX_COLOR);
    set_show_text_color(content->scoreboard->score_text,LIGHT_BOX_COLOR);
}
void handle_start_game( logic_vars_t *game_data,full_graphic_content *content){
    set_snake_game_size( game_data , content->intial_menu->width_config_ui->value , content->intial_menu->height_config_ui->value);
    //set_speed( game_data , get_speed_from_difficulty(content->intial_menu->diff_ui->value)  );
    set_game_difficulty(game_data , content->intial_menu->diff_ui->value);
    
    start_snake_logic(game_data); // start game
    update_scoreboard(game_data,content); // start scoreboard
    
    // printf("Game started %f %f\n",(double)game_data->speed,(double)game_data->game_status);
}
void handle_key_press( logic_vars_t * vars , full_graphic_content *content , ALLEGRO_EVENT *ev){
    
    if (content->front_end_status == PLAY){
        switch(ev->keyboard.keycode){
            case ALLEGRO_KEY_UP:
                handle_game_key_press(vars,LOGIC_KEY_UP);
            break;
            case ALLEGRO_KEY_DOWN:
                handle_game_key_press(vars,LOGIC_KEY_DOWN);
            break;
            case ALLEGRO_KEY_LEFT: 
                handle_game_key_press(vars,LOGIC_KEY_LEFT);
            break;
            case ALLEGRO_KEY_RIGHT:
                handle_game_key_press(vars,LOGIC_KEY_RIGHT);
            break;
        }
    }
}
//// All drawing loop content
void update_pc_graphic_screen( logic_vars_t* game_data , full_graphic_content* content){
    
    al_clear_to_color(BACKGROUND_COLOR);
    
    /// Graphical front-end machine (here we draw everything!)
    switch (content->front_end_status){
        case INITIAL_MENU:
            draw_button(content->intial_menu->play_button);
            draw_reg_box(content->intial_menu->width_config_ui);
            draw_reg_box(content->intial_menu->height_config_ui);
            draw_reg_box(content->intial_menu->diff_ui);
            
            draw_show_text(content->intial_menu->text_config_size);
            draw_show_text(content->intial_menu->extra_text_config);
            draw_show_text(content->intial_menu->title_text);
            draw_show_text(content->intial_menu->diff_text);
            
        break;
        case PLAY:
            draw_show_text(content->scoreboard->score_text);
            draw_show_text(content->scoreboard->score_number_text);
            
            draw_show_text(content->scoreboard->high_score);
            draw_show_text(content->scoreboard->high_score_number_text);
            
            draw_game(game_data,content);
        break;
        case GAME_OVER:
            
           
            
            draw_game(game_data,content);
            
            if (content->time_counter < BLINK_TIME){
                draw_show_text(content->scoreboard->score_text);
                draw_show_text(content->scoreboard->score_number_text);

                draw_show_text(content->scoreboard->high_score);
                draw_show_text(content->scoreboard->high_score_number_text);
            }else if(content->time_counter > TOTAL_PERIOD_TIME){
                content->time_counter = 0; 
            }
            draw_show_text(content->scoreboard->game_over_text);
            draw_button(content->scoreboard->restart_button);
            
        break;
    }
    update_display_cursor(content->cursor_handler); /// Update current shown cursor
    al_acknowledge_resize(content->display);
    al_flip_display();
}
void draw_game( logic_vars_t* game_vars, full_graphic_content* content){
    int screen_width = al_get_display_width(content->display);
    int screen_height = al_get_display_height(content->display);
    
    
    double sz_x = (double)screen_width / (double)game_vars->world_width;
    double sz_y = (double)screen_height / (double)game_vars->world_height;
    
    /// This calculation is to make all snake tiles to be squares.
    double mult_x = min(sz_x , sz_y);
    double mult_y = min(sz_x,  sz_y);
    
    /// Center game screen position
    double start_x = (double)screen_width/2-mult_x*game_vars->world_width/2;
    double start_y = (double)screen_height/2-mult_y*game_vars->world_height/2;
    
    int i,j, length;
    length = get_length(game_vars); // get actual snake length
    snake_node_t *pSnake = game_vars->pSnake;
    
    
    ///// Only A test
    /*for (i = 0;i < game_vars->world_height;i++){
        for (j = 0;j < game_vars->world_width;j++){
            if ( game_vars->used_tiles[ i ][ j ] ){
                al_draw_filled_rectangle(
                start_x + j*mult_x, \
                start_y + i*mult_y, \
                start_x + (j+1)*(mult_x),\
                start_y +(i+1)*(mult_y),\
                SNAKE_COLOR);
            }
        }
    }*/
    for(j = 0; j < length; j++){ // draws positions in buffer
        //al_draw_bitmap(content->images->snake[j], pSnake[j].polar_pos[X_COORD]*mult_x , pSnake[j].polar_pos[Y_COORD]*mult_y, 0);
        al_draw_filled_rectangle(
                start_x + pSnake[j].polar_pos[X_COORD]*mult_x, \
                start_y + pSnake[j].polar_pos[Y_COORD]*mult_y, \
                start_x + (pSnake[j].polar_pos[X_COORD]+1)*(mult_x),\
                start_y +(pSnake[j].polar_pos[Y_COORD]+1)*(mult_y),\
                SNAKE_COLOR);
        
    }
    /// draw food
    food_t *pFood = game_vars->pFood;
    
    al_draw_filled_rectangle(
            start_x + pFood->pos[X_COORD]*mult_x,\
            start_y + pFood->pos[Y_COORD]*mult_y,\
            start_x + (pFood->pos[X_COORD]+1)*mult_x,\
            start_y + (pFood->pos[Y_COORD]+1)*mult_y,\
            FOOD_COLOR);
   // al_draw_bitmap(food, pFood->pos[X_COORD], pFood->pos[Y_COORD], 0);
}

