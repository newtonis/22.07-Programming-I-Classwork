/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "triag.h"

int end_func(triangle_t *triag){
    return triag->depth <= 4;
}

int main(){
    triangle_hd_t base_struct;
    triangle_t base_triag;
    base_triag.center.x = 0;
    base_triag.center.y = 0;
    base_triag.size = 100;
    base_triag.depth = 0;
    base_triag.n = 0;
    base_triag.dir = 180;
    
    base_struct.my = &base_triag;
    
    generate_triangles( &base_struct , end_func , 1);
    compute_triangles_parameters( &base_struct);

    show_triangles(&base_struct);
    destroy_structure(&base_struct);
}