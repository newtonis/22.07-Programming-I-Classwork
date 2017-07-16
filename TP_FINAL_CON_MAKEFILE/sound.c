

#include <stdio.h>
#include "sound.h"

void al_audio_init(music_vars_t * music){

    int i=0;
    for(i=0;i<CANT_AUDIO_TRACKS;i++){
        music->audio_samples[i]=NULL;        // We initialize pointers with NULL for debugging purposes
        music->audio_instances[i]=NULL; 
    }
    
    music->pt2str[MENU_AUDIO]="menu2.wav";
    music->pt2str[SLOW_AUDIO]="slow.wav";
    music->pt2str[NORMAL_AUDIO]="normal.wav";
    music->pt2str[FAST_AUDIO]="fast.wav";
    music->pt2str[GAME_OVER_AUDIO]="game_over.wav";
    
    
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        exit (1);
    }
    if(!al_init_acodec_addon()){
       fprintf(stderr, "failed to initialize audio codecs!\n");
       exit (1);
    }
    
    if (!al_reserve_samples(CANT_AUDIO_TRACKS)){
       fprintf(stderr, "failed to reserve samples!\n");
       exit (1);
    }

    int l;
    for(l=0;l<CANT_AUDIO_TRACKS;l++){
       
        music->audio_samples[l] = al_load_sample(music->pt2str[l]);
        
        if(!music->audio_samples[l]){
            printf("sample number %d not loaded!\n",l);
            exit(1);
        }
        
        music->audio_instances[l]=al_create_sample_instance(music->audio_samples[l]);
        if(!music->audio_instances[l]){
            printf("instance %d not created!\n",l);
            exit (1);        
        }
        
        if (!(al_attach_sample_instance_to_mixer(music->audio_instances[l],al_get_default_mixer()))){
        
            printf( "instance %d could not be attached!\n",l ); 
            exit (1);
        }
    
    }
    
}    
    

    
void handle_audio(full_graphic_content* content, music_vars_t * music ){
  
        
       
        switch(content->audio_state){
            case MENU_AUDIO:
                if(content->audio_state != content->last_audio_state){
                    content->last_audio_state = content->audio_state;
                    al_stop_samples();
                    al_play_sample(music->audio_samples[MENU_AUDIO], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                }
                break;

            case SLOW_AUDIO:
    
                if(content->audio_state != content->last_audio_state){
                    content->last_audio_state = content->audio_state;
                    al_stop_samples();
                    al_play_sample(music->audio_samples[SLOW_AUDIO], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                }
                
                break;
                
            case NORMAL_AUDIO:
 
                if(content->audio_state != content->last_audio_state){
                    content->last_audio_state = content->audio_state;
                    al_stop_samples();
                    al_play_sample(music->audio_samples[NORMAL_AUDIO], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                }
                
                break;
            case FAST_AUDIO:
    
                if(content->audio_state != content->last_audio_state){
                    content->last_audio_state = content->audio_state;
                    al_stop_samples();
                    al_play_sample(music->audio_samples[FAST_AUDIO], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                }    
                break;
                
            case GAME_OVER_AUDIO:
                if(content->audio_state != content->last_audio_state){
                    content->last_audio_state = content->audio_state;
                    al_stop_samples();
                    al_play_sample(music->audio_samples[GAME_OVER_AUDIO], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                }
                //deberia haber un delay quiza o recien cuando se aprieta el boton de restart
                break;
        }
        
        
        
        
        
    
}
void destroy_music_vars(music_vars_t *music){
    
    for(int l=0;l<CANT_AUDIO_TRACKS;l++){

        al_destroy_sample(music->audio_samples[l]);
        al_destroy_sample_instance(music->audio_instances[l]);
        
    }
}
 