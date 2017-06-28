/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/***** TP9: Fractales *****
 * Ariel Nowik
 * Joaquin Mestanza
 * Marcelo Regueira
 * 
 * Commands available :
 * '-order n','-tol x','-color c val','-report filename'
 */

#include "triag.h"
#include "front_end.h"
#include "triag_plot.h"
#include "config.h"
#include "utils.h"
#include "read_command.h"

#define TEXT_POS 20
#define INC_FACT 0.1



void my_key_press(graphic_vars_t* vars, int key); 
void draw_func(graphic_vars_t* vars);
void fractal_update_event(graphic_vars_t* vars);

int end_func(triangle_t *triag);

int main(int argc ,char *argv[]){
    shared_vars_t shared_vars;
    
    
    /// Set default
    shared_vars.report_flag = 0; // no report by default
    shared_vars.max_tol = DEFAULT_TOL;
    shared_vars.max_fract_count = DEFAULT_CNT_FRACT;
    shared_vars.color[RED] = DEFAULT_RED;
    shared_vars.color[GREEN] = DEFAULT_GREEN;
    shared_vars.color[BLUE] = DEFAULT_BLUE;
    shared_vars.save_data = 0;
    
    //// Read input
    read_input(argc,argv , &shared_vars);
    
    /// Generate base triangle
    
    triangle_hd_t base_struct;
    triangle_t base_triag;
    base_triag.center.x = CENTER_X;
    base_triag.center.y = CENTER_Y;
    base_triag.size = TRIANGLE_SIZE;
    base_triag.depth = 0;
    base_triag.n = 0;
    base_triag.dir = DEFAULT_DIRECTION;
    
    base_struct.my = &base_triag;
    base_struct.cnt_child = 0;
    
    generate_triangles( &base_struct , end_func , 0 , MAX_COMPUTED_LVL );
    //// Create graphic environment
    
    graphic_vars_t g_vars; 
    
    shared_vars.w_rot = 0;
    shared_vars.fract_count = 0;
    
    shared_vars.base_struct = &base_struct;
    g_vars.key_press = my_key_press; // set callback
    g_vars.extra_draw_func = draw_func;
    g_vars.fractal_update = fractal_update_event;
    
    g_vars.logic_ref = (void*)(&shared_vars); // set logic reference for front end to make callbacks
    fe_init_graphic(&g_vars);
    
    g_vars.status_text = fe_add_show_text(&g_vars,SCREEN_W/2 , TEXT_POS);
    copy_str("Press Left/Right to generate rotation" , g_vars.status_text->text);
  
    
    //// Start loop!
    while (!g_vars.end){
        fe_update_events(&g_vars); 
        
    }
    if (shared_vars.save_data){
        FILE *file = fopen(shared_vars.file_to_save,"w+");
        write_triangle_data( &shared_vars , file);
        printf("Plot data successfully writen to %s \n",shared_vars.file_to_save);
        fclose(file);
    }
    fe_end_graphic(&g_vars);
    destroy_structure(&base_struct);
}

/// Update graphic fractal
void draw_func(graphic_vars_t* vars){
    shared_vars_t* shared_access = (shared_vars_t*)(vars->logic_ref);
    
    shared_access->base_struct->my->dir += shared_access->w_rot;
    compute_triangles_parameters( shared_access->base_struct );
      
    fe_triag_plot( ((shared_vars_t*)(vars->logic_ref))->base_struct,0 , shared_access);
}

/// Handle fractal computation
void fractal_update_event(graphic_vars_t* vars){
    shared_vars_t* shared_access = (shared_vars_t*)(vars->logic_ref);
    
    triangle_hd_t *base_struct = shared_access->base_struct;
    
    if (shared_access->fract_count < shared_access->max_fract_count ){
        shared_access->fract_count ++;
    }
    
}

void my_key_press(graphic_vars_t* vars, int key){
    shared_vars_t* shared_access = (shared_vars_t*)(vars->logic_ref);
    if (key == ALLEGRO_KEY_LEFT){
        ((shared_vars_t*)(vars->logic_ref))->w_rot += INC_FACT;
    }
    if (key == ALLEGRO_KEY_RIGHT){
        ((shared_vars_t*)(vars->logic_ref))->w_rot -= INC_FACT;
    }
}

int end_func(triangle_t *triag){ /// NOT IN USE
    return 1;
}