/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <math.h>
#include "front_end.h"
#include "utils.h"
#include "config.h"

char *color_strings[3] =  {"Red","Green","Blue"};    

enum {READ_COMMAND , READ_ARGS  };
enum {ORDER , TOL , COLOR , REPORT , READ_COLOR_VALUE};



int read_input(int argc,char *argv[] , shared_vars_t* shared_vars){
    

    int status = READ_COMMAND;
    int wait_com , num , color_select; 
    int rs;
    
    int i;
    for (i = 1;i < argc;i++){
        switch (status){
            case READ_COMMAND:
                if ( (strcmp(argv[i],"-order")) == 0 ){
                    wait_com = ORDER;
                }else if( (strcmp(argv[i],"-tol")) == 0){
                    wait_com = TOL;
                }else if( (strcmp(argv[i],"-color")) == 0){
                    wait_com = COLOR; 
                }else if( (strcmp(argv[i],"-report")) == 0){
                    wait_com = REPORT;
                }else{
                    fprintf(stderr , "Invalid command inserted\n");
                    exit(1);
                }
                status = READ_ARGS;
            break;
            case READ_ARGS:
                switch (wait_com){
                    case ORDER:
                        rs = str_to_int(argv[i],&num);
                        if (rs || num < 1 || num > MAX_COMPUTED_LVL){
                            fprintf(stderr , "Invalid number inserted. Must be [1-6]\n");
                            exit(1);
                        }
                        printf("Set max depth to %d \n",num);
                        shared_vars->max_fract_count = num;
                        status = READ_COMMAND;
                    break;
                    case TOL:
                        rs = str_to_int(argv[i],&num);
                        if (rs || num < MIN_TOL || num > MAX_TOL){
                            fprintf(stderr , "Invalid tolerance inserted. Must be [0-200]\n");
                            exit(1);
                        }
                        printf("Set max tolerace to %d \n",num);
                        shared_vars->max_tol = num;
                        status = READ_COMMAND;
                    break;
                    case COLOR:
                        if (strcmp(argv[i],"r") == 0){
                            color_select = RED;
                        }else if(strcmp(argv[i],"-g") == 0){
                            color_select = GREEN;
                        }else if(strcmp(argv[i],"b") == 0){
                            color_select = BLUE;
                        }else{
                            fprintf(stderr,"Invalid color argument inserted\n");
                            exit(1);
                        }
                        wait_com = READ_COLOR_VALUE;
                    break;
                    case REPORT:
                        if (strlen(argv[i]) > DEF_SZ){
                            fprintf(stderr, "File name is too long!\n");
                            exit(1);
                        }
                        printf("Set file to save data \n");
                        copy_str( argv[i] , shared_vars->file_to_save);
                        shared_vars->save_data = 1;
                        status = READ_COMMAND;
                    break;
                    case READ_COLOR_VALUE:
                        rs = str_to_int(argv[i],&num);
                        if (rs){
                            fprintf(stderr,"Invalid number inserted\n");
                            exit(1);
                        }
                        printf("Set %s color to %d \n",color_strings[color_select] , num);
                        shared_vars->color[color_select] = rgb_to_unit(num);
                        status = READ_COMMAND;
                    break;
                }
            break;
            
        }
       
    }
    if (status == READ_ARGS){ /// missing arguments
        fprintf(stderr,"Missing arguments !");
        exit(1);
    }
}
