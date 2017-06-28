/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   triag_plot.c
 * Author: newtonis
 *
 * Created on June 12, 2017, 11:31 PM
 */

#include <allegro5/allegro_primitives.h>
#include "triag_plot.h"
#include "triag.h"
#include "front_end.h"
#include "utils.h"

#define RED_DEFAULT 0
#define GREEN_DEFAULT 0
#define BLUE_DEFAULT 0
#define alpha 0.9f

void draw_default(triangle_t* tri, shared_vars_t* shared){ // default triangle drawing function

    ALLEGRO_COLOR color = al_map_rgba_f( shared->color[RED] ,  shared->color[GREEN], shared->color[BLUE], alpha);
    
    al_draw_filled_triangle(tri->vert[0].x, tri->vert[0].y, tri->vert[1].x, tri->vert[1].y, tri->vert[2].x,  tri->vert[2].y, color);
    
}

void fe_triag_plot(triangle_hd_t *triag_st , int depth, shared_vars_t* shared){ /// plot triangle structure in screen
    if (triag_st->my->size < shared->max_tol) return;
    if (depth >= shared->fract_count) return;
    
    draw_default(triag_st->my,shared);
    int i;
    for (i = 0;i < triag_st->cnt_child;i++){
        fe_triag_plot(triag_st->child[i],depth+1,shared);
    }
}

void write_triangle_data(shared_vars_t *shared_vars,FILE *file){
    fprintf(file,"Triangle plot data: \n");
    fprintf(file,"Order: %d \n",shared_vars->fract_count);
    fprintf(file,"Tolerance: %.2f px\n",shared_vars->max_tol);
    fprintf(file,"Perimeter: %.2f px\n", get_perimeter(shared_vars->base_struct->my->size,shared_vars->fract_count));
    fprintf(file,"Area: %.2f px\n", get_area(shared_vars->base_struct->my->size,shared_vars->fract_count));
    
}