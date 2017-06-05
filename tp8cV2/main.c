/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: marcecq
 *
 * Created on 31 de mayo de 2017, 21:22
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "led_api.h"

/*
 * 
 */
int main(int argc, char** argv) {
    led_vars_t led_vars;
    uint16_t led_manager;
    led_api_init(&led_vars , &led_manager , led_codes , CNT_LEDS);
    led_manager = 0x01;
    led_flush( &led_vars);
    
    //return (EXIT_SUCCESS);
}

