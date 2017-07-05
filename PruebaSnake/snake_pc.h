#ifndef SNAKE_PC_H
#define SNAKE_PC_H

#include "config.h"
#include "snake_logic.h"
#include <allegro5/allegro.h>

// set_newPos: sets the new position of the snake into allegro display
void set_newPos(snake_node_t *pSnake, ALLEGRO_BITMAP *snake[MAX_LENGTH]);

#endif /* SNAKE_PC_H */

