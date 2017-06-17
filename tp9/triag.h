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
    
#include <stdio.h>
#include <stdlib.h>
    
#define MAX_CHILD 5

    
typedef struct {
    float x,y;
}c2d;

// a triangle is defined by it's center, and it's base direction rect
typedef struct{
    /// basic properties
    c2d center;
    float dir;
    float size;
    
    /// computed properties
    c2d vert[MAX_CHILD]; // vertex. vertex 0-1 is the base
    
    int n;
    int depth; // structure depth
    
}triangle_t;

typedef struct triangle_hd triangle_hd_t; // triangle structure handler

struct triangle_hd{
    triangle_t* my;
    triangle_hd_t* child[MAX_CHILD];
    int cnt_child; /// the base triangle has 3 childs
};

void compute_triangles_parameters(triangle_hd_t *thand);
void generate_triangles( triangle_hd_t *thand ,int (*end_func)(triangle_t *) , int depth ,int maxdepth);
void show_triangles(triangle_hd_t *thand,FILE *file);
static void destroy_triangle_hd(triangle_hd_t *inst);
static int compute_boundary_triangles(triangle_hd_t *thand,int cnt);

void destroy_structure(triangle_hd_t *thand);
void pol(float length,float angle,float *ans_x,float *ans_y);
float rotate(float dir);
float get_perimeter(int size,int depth);
float get_area(int size,int depth);

#ifdef __cplusplus
}
#endif

#endif /* TRIAG_H */

