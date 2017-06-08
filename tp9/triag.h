/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   triag.h
 * Author: newtonis
 *
 * Created on June 7, 2017, 11:16 PM
 */

#ifndef TRIAG_H
#define TRIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#define CNT_CHILDS 3


    
typedef struct {
    int x,y;
}c2d;

// a triangle is defined by it's center, and it's base direction rect
typedef struct{
    /// basic properties
    c2d center;
    int dir;
    int size;
    
    /// computed properties
    c2d vert[CNT_CHILDS]; // vertex. vertex 0-1 is the base
    
    int n;
    int depth; // structure depth
}triangle_t;

typedef struct triangle_hd triangle_hd_t; // triangle structure handler

struct triangle_hd{
    triangle_t* my;
    triangle_hd_t* child[CNT_CHILDS];
    int cnd_childs; /// the base triangle has 3 childs
};

void compute_triangles_parameters(triangle_hd_t *thand);
void generate_triangles( triangle_hd_t *thand ,int (*end_func)(triangle_t *) , int depth);
void show_triangles(triangle_hd_t *thand);
static void destroy_triangle_hd(triangle_hd_t *inst);

void destroy_structure(triangle_hd_t *thand);
void pol(int length,int angle,int *ans_x,int *ans_y);
int rotate(int dir);

#ifdef __cplusplus
}
#endif

#endif /* TRIAG_H */

