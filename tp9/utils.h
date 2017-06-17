/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: newtonis
 *
 * Created on May 27, 2017, 8:44 PM
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

enum {RED , GREEN , BLUE };

typedef struct{
    int end_time; // time when clock started running
    int duration_set; // how much will the clock count when it is run.
    int seconds;
    bool on; // is clock running?
}rev_clock_t;
 
void clock_reset_to(rev_clock_t *clock , int sec); // set clock to 'sec' seconds
void clock_run(rev_clock_t *clock); 
int clock_update(rev_clock_t *clock); // update and check if clock reaches 0
void clock_get_values(rev_clock_t *clock,int *sec); // get clock seconds

bool is_num(int keycode);
int get_num(int keycode);
void copy_str(char *a,char *b);
int str_to_int(char *str,int *target);
float rgb_to_unit(int num);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */

