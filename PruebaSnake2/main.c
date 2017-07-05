#include <stdio.h>
#include <allegro5/allegro.h>
#include "config.h"
#include "snake_logic.h"
#include "snake_pc.h"
#include "snake_graphic_base.h"
#include "interface.h"
 
int main(void){
    
    logic_vars logic;
    full_graphic_content content;
    graphic_vars plot_basic_vars;
    
    
    content.plot_game_graphic = &plot_basic_vars;
    
    logic.pSnake = malloc(sizeof(snake_node_t)*MAX_LENGTH);
    if (logic.pSnake == NULL){
        fprintf(stderr,"Fatal error");
        exit(1);
    }
    logic.pFood = malloc(sizeof(food_t));
    if (logic.pFood == NULL){
        fprintf(stderr,"Fatal error");
        exit(1);
    }
    
    init_snake_pc(&content);
    
    
    init_snake_struct(INIT_LENGTH, logic.pSnake); // set snake position coordenates
    
    
    content.key_press = NO_KEY;
    content.direction = KEY_RIGHT;
    content.dir_control = 0;
    content.refresh = 0;

    while(!content.do_exit){ 
        handle_events(&logic , &content );
        
    }
    
    free(logic.pSnake);
    destroy_graphic_base(&content);
    return 0;
}
