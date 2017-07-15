#ifndef SNAKE_RPI_H
#define SNAKE_RPI_H

#include "config.h"
#include "rpi_hard.h"
#include "snake_logic.h"

#define JOY_THRESHOLD 20     // 10-100 Joystick threshold (sensitivity)
#define JOY_AXES_MIN 1
#define JOY_AXES_MAX 10

// mode_change: changes selected difficulty for blinking
void mode_change(disp_fragment_t *pFrag, int mode);

// mode_fsm: state machine for mode changing selection
void mode_fsm(game_control_t *pControl);

// refresh_welcome_display: manages welcome display update
void refresh_welcome_display(time_blink_t *pClock, logic_vars_t *pLogic, game_control_t *pControl);

// refresh_menu_display: manages dificulty selection display
void refresh_menu_display(time_blink_t *pClock, game_control_t *pControl);

// refresh_points_display: manages game over and points section display
void refresh_points_display(time_blink_t *pClock, logic_vars_t *pLogic, game_control_t *pControl);

// process_snake_move: gets new direction for snake
void process_snake_move(game_control_t *pControl);

// process_snake_status: process the result from update snake logic, it must be called
// after getting updated the snake logic
void process_snake_status(game_control_t *pControl, logic_vars_t *pLogic);

#endif /* SNAKE_RPI_H */

