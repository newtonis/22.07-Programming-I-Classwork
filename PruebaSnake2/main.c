#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include "config.h"
#include "snake_logic.h"
#include "snake_pc.h"
#include "snake_graphic_base.h"
#include "interface.h"
 
int main(void){
    full_graphic_content content;
    images_t plot_basic_vars;
    fonts_t fonts;
    initial_menu_vars_t inital_menu;
    
    content.images = &plot_basic_vars;
    content.intial_menu = &inital_menu;
    content.fonts = &fonts;

    init_snake_pc(&content);
    
    logic_vars_t *logic = init_snake_struct(INIT_LENGTH); // set snake position coordenates
    
    
    content.key_press = NO_KEY;
    content.direction = KEY_RIGHT;
    content.dir_control = 0;
    content.refresh = 0;

    while(!content.do_exit){ 
        //clock_t t1;
        //t1 = clock();
        
        //printf("%f ",(double)t1 / CLOCKS_PER_SEC * 1000.0);
        
        handle_events(logic , &content );
        
    }
    
    destroy_game(logic);
    destroy_graphic_base(&content);
    return 0;
}
