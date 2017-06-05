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

void led_api_init(led_vars_t* vars , uint16_t *led_handler, char * codes[],int cnt_leds){
    // copy led codes
    vars->cnt_leds = cnt_leds;
    vars->led = led_handler; // set led manager
    int i;
    for (i = 0;i < cnt_leds;i++){
        vars->led_db[i] = codes[i];
    }
    // init each led
    for (i = 0;i < cnt_leds;i++){
        led_init(vars->led_db[i]);
    }
}
void led_flush(led_vars_t* vars){
    int i;
    for (i = 0;i < vars->cnt_leds;i++){
        int status = (vars->led && (1<<i)) != 0;
        if ( status != vars->upd[i]){ // we need to update!
            led_update( vars->led_db[i] , status);
            vars->upd[i] = status;
        }
    }
}

void led_init( char * pin_code){
    FILE *handle_export;
    FILE *handle_direction;
    FILE *handle;
    
    char dst1[DEF_SZ];
    
    //= "/sys/class/gpio/gpio17/value";
    
    super_cat(dst1 , "/sys/class/gpio/gpio" , pin_code , "/value");
    
    printf("%s \n",dst1);
    
    int nWritten;
    if ((handle_export = fopen("/sys/class/gpio/export","w")) == NULL){
	fprintf(stderr,"Cannot open EXPORT File. Try again later.\n");
	exit(1);
    }
    nWritten=fputs(pin_code,handle_export);
    fflush(handle_export);
    if (nWritten==-1){
	fprintf(stderr,"Cannot EXPORT PIN . Try again later.\n");
	exit(1);
    }else{
        fprintf(stderr,"EXPORT File opened succesfully \n");
    }
    
    
    char dst2[DEF_SZ];
    super_cat(dst2 , "/sys/class/gpio/gpio" , pin_code , "/direction");
    
    if ((handle_direction = fopen(dst2,"w")) == NULL){
	fprintf(stderr,"Cannot open DIRECTION File");
        exit(1);
    }
    // Set pin Direction
    if ((nWritten=fputs("out",handle_direction)) == -1){
	fprintf(stderr,"Cannot open DIRECTION pin. Try again later.\n");
	exit(1);
    }else{
	fprintf(stderr,"DIRECTION File for PIN opened succesfully\n");
    }
    fflush(handle_direction);
    
   
    if ((handle = fopen(dst1,"w")) == NULL){
	fprintf(stderr,"Cannot open device. Try again later.\n");
	exit(1);
    }else{
	fprintf(stderr,"Device successfully opened\n");
    }
    
}
void led_update(char *led_pin,int status){
    FILE *handle;
    char file_path[DEF_SZ];
    super_cat(file_path , "/sys/class/gpio/gpio",led_pin,"/value");
    if (file_path == NULL){
        fprintf(stderr,"Cannot write led %s. Try again later.\n",led_pin);
        exit(1);
    }
    int ans;
    if (status == 0){
        fputc('0',handle);
    }else if (status == 1){
        fputc('1',handle);
    }else{
        fprintf(stderr,"Invalid led update call");
    }
    if (ans == -1){
        fprintf(stderr,"Cannot write to led \n");
        exit(1);
    }
    fclose(handle);
}

