#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rpi_hard.h"
#include "snake_rpi.h"
#include "snake_logic.h"

int main(int argc, char** argv){
  
    game_control_t control_vars={START, FALSE, FALSE, EASY, FALSE, LOGIC_KEY_RIGHT, 
                                 {FALSE,FALSE}, 
                                 J_NOPRESS,
                                 {{EASY, BLINK_ON},{MED, BLINK_OFF},{HARD, BLINK_OFF}}};
    
    game_control_t *pControl = &control_vars;
    
    time_blink_t blink_control;
    blink_control.start = clock();
    time_blink_t *pTime = &blink_control;
    
    logic_vars_t *pLogicRpi = init_snake_struct();
    
    set_config_data(pLogicRpi, pControl);
    start_snake_logic(pLogicRpi); // call for updating highscore pointer
    stop_snake_logic(pLogicRpi);
    
    hard_initialize();
    
    while (1){
        
        switch (pControl->status){
            case START:
                
                refresh_welcome_display(pTime, pLogicRpi, pControl);
             
            break;
            case MENU:
                
                refresh_menu_display(pTime, pControl);
                
                mode_fsm(pControl);
            
            break;
            case INIT_GAME:
                
                display_clear();
                set_config_data(pLogicRpi, pControl);
                start_snake_logic(pLogicRpi);
                pControl->status = PLAY;
                
            break;
            case PLAY:
                
                process_snake_move(pControl); // get new direction
                handle_game_key_press(pLogicRpi, pControl->direction); 
                pControl->snake_status = update_snake_logic(pLogicRpi);
                process_snake_status(pControl, pLogicRpi);
                
            break;
            case END:
                
                refresh_points_display(pTime, pLogicRpi, pControl);
                
            break;
        }
    }
            
    display_clear();
    return (0);
}
