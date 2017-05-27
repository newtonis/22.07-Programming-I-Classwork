#include <stdio.h>
#include <stdlib.h>
// Allegro libraries
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <time.h>
#include "nonblock.h"
#include "graphic.h"
#include "port_utils.h"
#include "output.h"
#include "input.h"

ALLEGRO_FONT *iso_title = NULL;

int main(){
    ALLEGRO_DISPLAY *disp_a = NULL;
    
    FILE *fp = NULL;
    
    fp = fopen("event_log","w");
    
    if(!al_init()){
        fprintf(fp, "ERROR - allegro init\n");
        fclose(fp);
        return -1;
    }
    fprintf(fp, "OK - allegro init\n");
    
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    
    disp_a = al_create_display(SCREEN_W, SCREEN_H);
    
    if(!disp_a){
        fprintf(fp, "ERROR - display init\n");
        fclose(fp);
        return -1;
    }
    
    fprintf(fp, "OK - display init\n");
    
    iso_title = al_load_font("isocpeur.ttf", TITLE_W, 0); // title font
    
    if(!iso_title){
        fprintf(fp, "ERROR - font init\n");
        al_destroy_display(disp_a);
        fclose(fp);
        return -1;
    }
    
    fprintf(fp, "OK - font init\n");
    
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    
    microPorts_t  mp;
    int err = initPorts(&mp);

    if (err == 1){
            fprintf(fp, "ERROR - Can't port heap memory\n");
            fclose(fp);
            return -1;
    }else{	
        instruct_print();
        
        al_rest(5.0);
        
        /*
            int end = 0;
            int mode = NORMAL;

            nonblock(NB_ENABLE);
            while (!end){
                    long tm = (long)time(NULL);
                    update_display(&mp,&mode);
                    userInput(&mp,&end,&mode,tm);
                    //while (tm == (long)time(NULL)); // wait to next second
            }
            nonblock(NB_DISABLE);
            system("clear");
                   */
    }
    al_destroy_display(disp_a);
    return 0;
}