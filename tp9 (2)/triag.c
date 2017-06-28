/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <math.h>
#include <stdlib.h>
#include "triag.h"
#include <stdio.h>

#define min(a,b) ((a)<(b)?(a):(b))

#define PI 3.141592
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
#define EXTRA_TRI 2

#define CNT_CHILD 4
#define BASE_CNT_CHILD 3

void pol(float length,float angle,float *ans_x,float *ans_y){
    *ans_x += cos(angle * PI / 180.0) * length;
    *ans_y += sin(angle * PI / 180.0) * length;
}

float rotate(float dir){
    dir += 180.0;
    if (dir > 180.0){
        return dir - 360;
    }
}
// needs parent triangle; generates triangles and inserts in the list

void generate_triangles( triangle_hd_t *thand ,int (*end_func)(triangle_t *) , int depth , int maxdepth){ 
    thand->cnt_child = 0;
    if (!end_func(thand->my)) return ;
    if (depth == maxdepth) return;
    
    int i;
    int it = (depth == 0) ? BASE_CNT_CHILD : CNT_CHILD ; // the base has two descendents
    
    
    for (i = 0;i < it;i++){
        
        triangle_t *child = malloc(sizeof(triangle_t)); // create triangle instance
        
        //// init child
        child->n = i;
        child->depth = depth+1; /// set basic triangle properties
       
        
        triangle_hd_t *cont = malloc(sizeof(triangle_hd_t)); //create its structure container
        cont->my = child; // set its triangle
        cont->cnt_child = 0;
         
        thand->child[i] = cont; // insert in the parent structure
        thand->cnt_child++;
        
        
        generate_triangles(thand->child[i] , end_func , depth + 1 , maxdepth);
        
    }
}

int compute_sided_triangles(int pnt,triangle_hd_t *thand){
    triangle_t *parent = thand->my;
    
    int i;
    for (i = pnt;i < pnt+2;i++){
        triangle_t *act = thand->child[i]->my;
        
        act->size = parent->size / DIVIDE_FACTOR;
        act->dir = parent->dir;
        
        float incx = 0 , incy = 0;
        
        pol( parent->size * TG30  / 2 ,parent->dir-90,&incx,&incy);
        if (i == pnt){
            pol(   parent->size,parent->dir   ,&incx,&incy);
        }else{
            pol( - parent->size,parent->dir   ,&incx,&incy);
        }
        pol( act->size * TG30 / 2 ,parent->dir+90,&incx,&incy);
        
        act->center.x = parent->center.x + incx;
        act->center.y = parent->center.y + incy;
    }
    
    
    return 0;
}

int compute_boundary_triangles(triangle_hd_t *thand,int cnt){ // compute N boundary triangles around thand
    if (cnt > thand->cnt_child){
        fprintf(stderr , "Internal logic error");
        exit(1);
        return 0;
    }
    
    triangle_t *parent = thand->my;
    
    float k_angle = parent->dir + ANGLE_BASE; // perpendicular angle
    float w_angle = parent->dir + ANGLE_THIRD; // paralel angle
    
    int i;
    for (i = 0;i < cnt;i++){
        triangle_t *act = thand->child[i]->my;
        
        /// SET SIZE
        act->size = parent->size / DIVIDE_FACTOR;
        
        /// SET CENTER
        float incx = 0, incy = 0;
        pol(SIZE_FACT * parent->size , k_angle , &incx, &incy);
        
        act->center.x = parent->center.x + incx;
        act->center.y = parent->center.y + incy;
      
        /// SET DIRECTOR VECTOR
        
        act->dir = rotate( w_angle );
        
        k_angle += ANGLE_THIRD; 
        w_angle += ANGLE_THIRD; 
        
        
    }
    
    return 0;
}


void compute_triangles_parameters(triangle_hd_t *thand){
    
    triangle_t *parent = thand->my;
   
    
    if (thand->my->depth == 0){
        if (thand->cnt_child >= 3){
            compute_boundary_triangles(thand,3);
        }
    }else{
        if (thand->cnt_child >= 4){
            compute_boundary_triangles(thand,2);
            compute_sided_triangles(2,thand); 
        }
    }
    
    /// now compute triangle vertex
    int i = 0;
    float k_angle = parent->dir + ANGLE_VERTEX_CONST;
    
    for (i = 0;i < SIDES;i++){
        float incx = 0, incy = 0;
        pol(H_TRIAG_CNST * parent->size , k_angle , &incx,&incy);
        parent->vert[i].x = parent->center.x + incx;
        parent->vert[i].y = parent->center.y + incy;
        k_angle += ANGLE_THIRD;
    }
    
    for (i = 0;i < thand->cnt_child;i++){
        compute_triangles_parameters(thand->child[i]);
    }
}
void show_triangles(triangle_hd_t *thand,FILE *file){
    
    triangle_t *act = thand->my;
    
    fprintf(file,"Triangle %d %d : " , act->depth , act->n );
    fprintf(file,"Center: (%f %f) ", act->center.x , act->center.y );
    fprintf(file,"Vertex: ");
    int i;
    for (i = 0;i < CNT_CHILD;i++){
        fprintf(file,"(%f, %f) ,",act->vert[i].x,act->vert[i].y);
    }
    fprintf(file,"\n");
    for (i = 0;i < thand->cnt_child;i++){
        show_triangles(thand->child[i],file);
    }
}
void destroy_triangle_hd(triangle_hd_t *inst){
    free(inst->my);
    free(inst);
}

void destroy_structure(triangle_hd_t *thand){
    int i;
    for (i = 0;i < thand->cnt_child;i++){
        destroy_structure(thand->child[i]);
        destroy_triangle_hd(thand->child[i]);
    }
}

float get_perimeter(int size,int depth){
    float ans = 3 * size;
    int i;
    for (i = 0;i < depth;i++){
        ans *= 4.0/3.0;
    }
    return ans;
}
float get_area(int size,int depth){
    float mult = 3;
    int i;
    for (i = 0;i < depth;i++){
        mult *= (4.0/9.0);
    }
    return (sqrt(3.0)/4*size*size)/5.0 * (5 - mult);
}