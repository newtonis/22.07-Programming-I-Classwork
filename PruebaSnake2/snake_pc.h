#ifndef SNAKE_PC_H
#define SNAKE_PC_H

#include "config.h"
#include "snake_logic.h"
#include "interface.h"
#include "snake_graphic_base.h"

#include <allegro5/allegro.h>

#define BLACK al_map_rgb(0,0,0)

void update_game( logic_vars_t* game_data , full_graphic_content* content );

void update_pc_graphic_screen( logic_vars_t* game_data , full_graphic_content* graphic_data);


void draw_game( logic_vars_t* game_vars, full_graphic_content* content);

void handle_start_game( logic_vars_t *game_data,full_graphic_content *content);

/// convert difficulty number to the second-valued period of the snake
static double get_speed_from_difficulty(int diff);

/// Handle game key presses
void handle_key_press( logic_vars_t * vars , full_graphic_content *content , ALLEGRO_EVENT *ev);


#endif /* SNAKE_PC_H */

