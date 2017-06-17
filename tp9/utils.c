/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "utils.h"
#include <time.h>
#include <math.h>

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

bool is_num(int keycode){
    return keycode >= ALLEGRO_KEY_0 && keycode <= ALLEGRO_KEY_9;
}
int get_num(int keycode){
    return keycode - ALLEGRO_KEY_0;
}
void copy_str(char *a,char *b){
    int i = 0;
    while (a[i]){
        b[i] = a[i];
        i++;
    }
    b[i] = a[i];
}
int str_to_int(char *str,int *target){
    int j = 0;
    int good = 1;
    while (str[j] != '\0'){
        if (str[j] < '0' || str[j] > '9'){
            good = 0;
        }
        j++;
    }
    
    if (good){
        int i = 0;
        int ans = 0;
        while (str[i] != '\0'){
            ans *= 10;
            ans += str[i] - '0';
            i++;
        }
        *target = ans;
        return 0;
    }else{
        return 1;
    }
}
float rgb_to_unit(int num){
    return (float)num / 256.0;
}