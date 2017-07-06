/* 
 * File:   main.c
 * Author: joa
 *
 * Created on 5 de julio de 2017, 11:49
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "termlib.h"
#include "joydrv.h"
#include "disdrv.h"
#include <time.h>

#define MAX_DISP 16
#define JOY_AXIS_INVERT J_INV_TRUE 
#define JOY_THRESHOLD 40     // 10-100 Joystick threshold (sensitivity)
#define MAX_MODES 3

enum { START, MENU , PLAY };
enum { BLINK_OFF , BLINK_ON};

typedef struct {
        int number;
        int status;
    }disp_fragment_t;

    

void clear_disp(char disp[MAX_DISP][MAX_DISP]);
void show_disp(char disp[MAX_DISP][MAX_DISP]);
void turn_leds_msg(char mat[MAX_DISP][MAX_DISP]);
//void turn_numbers(char mat[MAX_DISP][MAX_DISP], int num);
void copy_mat(char source[MAX_DISP][MAX_DISP],char destiny[MAX_DISP][MAX_DISP]);
void update_menu(disp_fragment_t cuadrado[],char msg2[MAX_DISP][MAX_DISP],char mat_aux[MAX_DISP][MAX_DISP]);

int main(int argc, char** argv){

    char msg[MAX_DISP][MAX_DISP]={
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},  
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'#','#','#','0','#','#','#','0','#','0','#','0','#','#','#','0'},
        {'#','0','0','0','#','0','#','0','#','#','#','0','#','0','0','0'},
        {'#','#','#','0','#','#','#','0','#','0','#','0','#','#','#','0'},
        {'#','0','#','0','#','0','#','0','#','0','#','0','#','0','0','0'},
        {'#','#','#','0','#','0','#','0','#','0','#','0','#','#','#','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','#','0','#','#','0','0','#','#','#','0','0','0','0','0'},
        {'0','#','#','0','0','0','#','0','0','0','#','0','0','0','0','0'},
        {'0','0','#','0','0','#','0','0','0','#','#','0','0','0','0','0'},
        {'0','0','#','0','#','0','0','0','0','0','#','0','0','0','0','0'},
        {'0','0','#','0','#','#','#','0','#','#','#','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}};
    
   
    
    char msg2[MAX_DISP][MAX_DISP]={
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},  
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','#','0','0','#','0','#','#','#','0','#','#','#','0','0','0'},
        {'0','0','#','0','#','0','#','0','0','0','#','0','0','0','0','0'},
        {'0','#','#','0','#','0','#','#','0','0','#','#','0','0','0','0'},
        {'#','0','#','0','#','0','#','0','0','0','#','0','0','0','0','0'},
        {'0','#','0','0','#','0','#','0','0','0','#','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}};
   
    
    //Init 
    int ret=0;
    int i,j;
    jcoord_t joy_coordinates1;
    jswitch_t joy_switch1=J_NOPRESS;
    int8_t posx,posy,last_posx,last_posy;	
    clrscr();					//Termlib Clear Screen (see termlib.h for more info)		
    joy_init();					// Initialize Joystick Hardware
    display_init();				// Initialize Display Hardware 
    set_joy_axis(JOY_ROTATE);	// Set joystick axis orientaton  
    set_display_axis(NORMAL);	// Set display axis orientation 
    set_joy_direction(J_INV_TRUE,J_INV_TRUE); // Invert both x and y joystick axis direction
    
    // end of init
   
    disp_fragment_t cuad[MAX_MODES]={{0,BLINK_ON},{1,BLINK_OFF},{2,BLINK_OFF}};
    
char mat_aux[MAX_DISP][MAX_DISP];
    
copy_mat(msg2,mat_aux);
    turn_leds_msg(mat_aux);
    display_update();
    
    
    
    
    int status = START;
    
    int flag_release = 0;
    int mode=0;
    while (1){
        
        
        switch (status){
            case START:
                joystick_update(); // Read joystick Hardware
		joy_switch1=joystick_get_switch_value(); // And get switch value
                if (joy_switch1!=J_NOPRESS){
                    status = MENU;
                    printf("sali de start");
                    flag_release = 1;
                }                
            break;
            case MENU:
                printf("entre menu");
                joystick_update(); // Read joystick Hardware
		joy_switch1=joystick_get_switch_value(); // And get switch value
                
                //long long int timer=time(NULL);
                //if(timer%2==0) //500 ms! PONELE
                update_menu(cuad,msg,mat_aux);
              
               if(joy_coordinates1.y==126){
                   mode++;
                   int k;
                   if(mode<MAX_MODES){
                   for(k=0;k<MAX_MODES;k++){
                       if(k==mode){
                       cuad[mode].status=BLINK_ON;
                       }else{
                           cuad[k].status=BLINK_OFF;
                       }
                   }
                    
                   }else{
                       mode=0;
                       for(k=0;k<MAX_MODES;k++){
                       if(k==mode){
                       cuad[mode].status=BLINK_ON;
                       }else{
                           cuad[k].status=BLINK_OFF;
                       }
                    }
                       
                   }
               }
                if (joy_switch1==J_NOPRESS){
                    flag_release = 0;
                }
                if (flag_release == 0 && joy_switch1!=J_NOPRESS){
                    status = PLAY;
                    printf("sali de menu");
                }
                printf("procesemenu");
            break;
            case PLAY:
                 printf("aisjdoaisjd");
                
            break;
        }
    }
            
    display_clear();
    return (EXIT_SUCCESS);
}


void clear_disp(char disp[MAX_DISP][MAX_DISP]){
    int i,j;
    for(i=0;i<MAX_DISP; i++){
        for(j=0;j<MAX_DISP; j++){
            disp[i][j]='0';
        }
    }
}

void copy_mat(char source[MAX_DISP][MAX_DISP],char destiny[MAX_DISP][MAX_DISP]){
    int i,j;
    for(i=0;i<MAX_DISP; i++){
        for(j=0;j<MAX_DISP; j++){
            destiny[i][j]=source[i][j];
        }
    }
}

void show_disp(char mat[MAX_DISP][MAX_DISP]){
    int k,l;
	
	for(k=0;k<MAX_DISP;k++){
		for (l=0;l<MAX_DISP;l++)
			{	
				printf("%c ",mat[k][l]);
				if(l==MAX_DISP-1){
				printf("\n");
			}

		}			
	}
}

void turn_leds_msg(char mat[MAX_DISP][MAX_DISP]){
    int i,j;
    for(i=0;i<MAX_DISP; i++){
        for(j=0;j<MAX_DISP; j++){
            if((mat[i][j])=='#'){
            	display_write(i,j,D_ON);
                }else{
                display_write(i,j,D_OFF);
                }
            }
        }
    }

void    update_menu(disp_fragment_t cuadrado[],char msg2[MAX_DISP][MAX_DISP],char mat_aux[MAX_DISP][MAX_DISP]){
    int l;
    for(l=0;l<MAX_MODES;l++){
        if(cuadrado[l].status==BLINK_ON){
             // siempre empiezo con la origninal
            // ahora la modifico
            // y despues solo muestro la original y la cambiada
            int i,j;
           for(i=10;i<MAX_DISP-1; i++){
               for(j=0+4*(cuadrado[l].number);j<(4+4*(cuadrado[l].number)); j++){
                    if((mat_aux[i][j])=='#'){
            	
                        display_write(i,j,D_OFF);
              
                    }else{
               
                        display_write(i,j,D_ON);
                }
            }
        }
           display_update();
           copy_mat(msg2,mat_aux);
           turn_leds_msg(mat_aux);
           display_update();
            
            //escribo todo blinkeado updateo y lo doy vuelta y updateo
            // MUESTRO LA ORIGINAL Y DSP LA CAMBIADA
            
            //copy_mat()
        }
    }

}
