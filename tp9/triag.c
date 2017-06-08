/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <math.h>
#include <stdlib.h>
#include "triag.h"
#include <stdio.h>

#define PI 3.141595
#define TG30 0.57355    
#define SIZE_FACT TG30*2.0/3.0

#define COS30 0.866
#define H_TRIAG_CNST 1.0/(2.0*COS30)

#define DIVIDE_FACTOR 3.0

#define ANGLE_BASE 30
#define ANGLE_THIRD 120
#define ANGLE_SIXTH 60
#define ANGLE_VERTEX_CONST 210

#define SIDES 3

void pol(int length,int angle,int *ans_x,int *ans_y){
    *ans_x = cos(angle * PI / 180) * length;
    *ans_y = sin(angle * PI / 180) * length;
   
}

int rotate(int dir){
    return (dir + 180 + 180) % 360 - 180; 
}
// needs parent triangle; generates triangles and inserts in the list

void generate_triangles( triangle_hd_t *thand ,int (*end_func)(triangle_t *) , int depth){
    if (!end_func(thand->my)) return ; // no more!
    int i;
    int it = depth == 0 ? CNT_CHILDS : CNT_CHILDS -1; // the base has two descendents
    thand->cnd_childs = 0;
    
    for (i = 0;i < it;i++){
        
        triangle_t *child = malloc(sizeof(triangle_t)); // create triangle instance
        
        child->n = i;
        child->depth = depth; /// set basic triangle properties
        
        triangle_hd_t *cont = malloc(sizeof(triangle_hd_t)); //create its structure container
        cont->my = child; // set its triangle
        
        thand->child[i] = cont; // insert in the parent structure
        thand->cnd_childs++;
        generate_triangles(thand->child[i] , end_func , depth + 1);
    }
}

void compute_triangles_parameters(triangle_hd_t *thand){
    triangle_t *parent = thand->my;
    int i;
    
    int k_angle = parent->dir + ANGLE_BASE; // perpendicular angle
    int w_angle = parent->dir + ANGLE_SIXTH; // paralel angle
    
    
    for (i = 0;i < thand->cnd_childs;i++){
        triangle_t *act = thand->child[i]->my;
        
        /// SET SIZE
        act->size = parent->size / DIVIDE_FACTOR;
        
        /// SET CENTER
        int incx, incy;
        pol(SIZE_FACT * parent->size , k_angle , &incx, &incy);
        
        act->center.x = parent->center.x + incx;
        act->center.y = parent->center.y + incy;
      
        /// SET DIRECTOR VECTOR
        
        act->dir = rotate( w_angle );
        
        k_angle += ANGLE_THIRD; 
        w_angle += ANGLE_SIXTH; 
        
        
    }
    
    /// now compute triangle vertex
    k_angle = parent->dir + ANGLE_VERTEX_CONST;
    
    for (i = 0;i < SIDES;i++){
        int incx, incy;
        pol(H_TRIAG_CNST * parent->size , k_angle , &incx,&incy);
        parent->vert[i].x = parent->center.x + incx;
        parent->vert[i].y = parent->center.y + incy;
        k_angle += ANGLE_THIRD;
    }
    
    for (i = 0;i < thand->cnd_childs;i++){
        compute_triangles_parameters(thand->child[i]);
    }
}
void show_triangles(triangle_hd_t *thand){
    triangle_t *act = thand->my;
    /*printf("Triangle %d %d :" , act->depth , act->n );
    printf("Center: (%d %d)", act->center.x , act->center.y );
    printf("Vertex: ");*/
    printf("(%d, %d) ,",act->center.x,act->center.y);
    /*int i;
    for (i = 0;i < CNT_CHILDS;i++){
        printf("(%d, %d) ,",act->vert[i].x,act->vert[i].y);
    }*/
    //printf(")");
    //printf("\n");
    int i;
    for (i = 0;i < thand->cnd_childs;i++){
        show_triangles(thand->child[i]);
    }
}

void destroy_triangle_hd(triangle_hd_t *inst){
    free(inst->my);
    free(inst);
}

void destroy_structure(triangle_hd_t *thand){
    int i;
    for (i = 0;i < thand->cnd_childs;i++){
        destroy_structure(thand->child[i]);
        destroy_triangle_hd(thand->child[i]);
    }
}