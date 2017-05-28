/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "utils.h"
#include <time.h>

void clock_reset_to(rev_clock_t *clock , int sec){
    clock->on = false;
    clock->duration_set = sec;
} // reset clock to 'sec' seconds
void clock_run(rev_clock_t *clock){
    clock->end_time = (int)time(NULL) + clock->duration_set;
    clock->on = true;
}
int clock_update(rev_clock_t *clock){
    int dif = clock->end_time - (int)time(NULL);
    int ans;
    if (dif < 0){
        ans = 0; // clock has reach 0
        clock->seconds = 0;
    }else{
        ans = 1;
        clock->seconds = dif;
    }
   
    return ans;
} // update and check if clock reaches 0
void clock_get_values(rev_clock_t *clock,int *sec){
    *sec = clock->seconds;
} // get clock seconds and miliseconds

