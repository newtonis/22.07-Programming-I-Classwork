#ifndef RPI_HARD_H
#define RPI_HARD_H

#include "config_rpi.h"
#include "snake_logic.h"

#define POINT_ON '#'
#define POINT_OFF '0'

#define JOY_AXIS_INVERT J_INV_TRUE 

// clear_matrix: sets input matrix with charater '0'
void clear_matrix(char disp[MAX_DISP][MAX_DISP]);

// hard_initialize: inits joystick and display
void hard_initialize(void);

// turn_leds_msg: puts matrix message into display, operation inputs: D_ON - D_OFF
void turn_leds(char mat[MAX_DISP][MAX_DISP], char point, int operation);

// turn_half_leds: puts matrix message into superior display, operation inputs: D_ON - D_OFF
void turn_half_leds(char mat[MAX_DISP][MAX_DISP], char point, int operation);

// shift_text: shifts displayed text to left showing complete
// input text, returns TEXT_FINISH when ready, else 0
int shift_text(char *pText, char aux_mat[MAX_DISP][MAX_DISP], int line_w);

// print_welcome: prints initial message in display
void print_welcome(int highscore);

// refresh_joy: refreshes joystick swith and coordenates data
void refresh_joy(game_control_t *pControl);

// update_menu: shows message into display
void update_menu_op(disp_fragment_t who_blinks[]);

// shift_mat_left: shifts all input matrix elements to left
void shift_mat_left(char mat[MAX_DISP][MAX_DISP]);

// copy_mat: copies data from source matrix to destiny matrix
void copy_mat(char source[MAX_DISP][MAX_DISP], char destiny[MAX_DISP][MAX_DISP]);

// update_menu_op: function for blinking number of dificult selected
void update_menu_op(disp_fragment_t who_blinks[]);

// print_score: end of game, shows score
void print_score(int points);

// reset_txt_fsm: resets variables an matrix for text showing
void reset_txt_fsm(void);

// set_config_data: configures game standards
void set_config_data(logic_vars_t *pLogic, game_control_t *pControl);
#endif /* RPI_HARD_H */

