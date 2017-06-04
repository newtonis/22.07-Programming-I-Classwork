/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "led_api.h"

#define DEF_SZ 30

void super_cat(char *dst , char *str1 ,char *str2,char *str3){
    strcat(dst , str1);
    strcat(dst , str2);
    strcat(dst , str3);
}


void init_led( char * pin_code){
    FILE *handle_export;
    FILE *handle_direction;
    FILE *handle;
    
    char dst1[DEF_SZ];
    
    //= "/sys/class/gpio/gpio17/value";
    
    super_cat(dst1 , "/sys/class/gpio/gpio" , pin_code , "/value");
    
    printf("%s \n",dst1);
    
    int nWritten;
    if ((handle_export = fopen("/sys/class/gpio/export","w")) == NULL){
	printf("Cannot open EXPORT File. Try again later.\n");
	exit(1);
    }
    nWritten=fputs(pin_code,handle_export);
    fflush(handle_export);
    if (nWritten==-1){
	printf ("Cannot EXPORT PIN . Try again later.\n");
	exit(1);
    }else{
        printf("EXPORT File opened succesfully \n");
    }
    
    
    char dst2[DEF_SZ];
    super_cat(dst2 , "/sys/class/gpio/gpio" , pin_code , "/direction");
    
    if ((handle_direction = fopen(dst2,"w")) == NULL){
	printf("Cannot open DIRECTION File");
        exit(1);
    }
    // Set pin Direction
    if ((nWritten=fputs("out",handle_direction)) == -1){
	printf("Cannot open DIRECTION pin. Try again later.\n");
	exit(1);
    }else{
	printf("DIRECTION File for PIN opened succesfully\n");
    }
    fflush(handle_direction);
    
   
    if ((handle = fopen(dst1,"w")) == NULL){
	printf("Cannot open device. Try again later.\n");
	exit(1);
    }else{
	printf("Device successfully opened\n");
    }
    
}

void led_init(int *led, led_vars_t* vars){
    
}

void led_flush(led_vars_t* vars){
    
}



