#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include "config.h"
#include "snake_logic.h"
#include "snake_pc.h"
#include "snake_graphic_base.h"
#include "interface.h"
 
/*
 * Snake, PC version: 
 * Ariel Nowik
 * Marcelo Regeira
 * Joaquin Mestanza
 */

/*
 Important note:
 * In this program we used exit(1) several times in case of errors.
 * There is no risk of memory leak as OS takes all allocated memory back when exit(1) is called
 * https://stackoverflow.com/questions/10588014/what-happens-to-the-malloced-memory-when-exit1-is-encountered
 */


int main(void){
    full_graphic_content content;
    images_t plot_basic_vars;
    fonts_t fonts;
    
    content.images = &plot_basic_vars;
    content.fonts = &fonts;

    init_snake_pc(&content);
    
    logic_vars_t *logic = init_snake_struct(); // set snake position coordinates
    set_logic_call_time(logic, 1.0f/FPS_A); /// give to the logic module the period of game updates
    
    while(!content.do_exit){ 
        
        handle_events(logic , &content );
        
    }
    
    destroy_game(logic);
    destroy_graphic_base(&content);
    return 0;
}
