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


typedef struct led_vars{
    uint16_t *led;
    int upd[CNT_LEDS];
}led_vars_t;


void led_init(int *led, led_vars_t* vars);
void led_flush(led_vars_t* vars);

 void init_led();
static void super_cat(char *dst , char *str1 ,char *str2,char *str3);

#ifdef __cplusplus
}
#endif

#endif /* LED_API_H */

