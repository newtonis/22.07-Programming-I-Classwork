#ifndef SNAKE_PC_H
#define SNAKE_PC_H

#include "config.h"
#include "snake_logic.h"
#include "interface.h"
#include "snake_graphic_base.h"

#include <allegro5/allegro.h>

#define BLACK al_map_rgb(0,0,0)

void update_game( logic_vars* game_data , full_graphic_content* content );

void update_pc_graphic_screen( logic_vars* game_data , graphic_vars* graphic_data);

// set_newPos: sets the new position of the snake into allegro display
void set_snakePos(snake_node_t *pSnake, ALLEGRO_BITMAP *snake[MAX_LENGTH]);

// set_foodPos: sets the new food in allegro display
void set_foodPos(food_t *pFood, ALLEGRO_BITMAP *food);

#endif /* SNAKE_PC_H */

