/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   led_api.h
 * Author: marcecq
 *
 * Created on 31 de mayo de 2017, 21:23
 */

#ifndef LED_API_H
#define LED_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CNT_LEDS 7
#define MAX_CNT_LEDS 20
    
typedef struct led_vars{
    int cnt_leds;
    char *led_db[MAX_CNT_LEDS];
    uint16_t *led;
    int upd[MAX_CNT_LEDS];
}led_vars_t;


void led_flush(led_vars_t* vars);
void led_api_init(led_vars_t* vars , uint16_t *led_handler, char * codes[],int cnt_leds);

void led_init(char *led_pin);
void led_end(char *codes[]);
void led_update(char *led_pin,unsigned int status); // update a single led
static void super_cat(char *dst , char *str1 ,char *str2,char *str3);

#ifdef __cplusplus
}
#endif

#endif /* LED_API_H */

