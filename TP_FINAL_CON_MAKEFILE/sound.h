
#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "snake_graphic_base.h"
#define CANT_AUDIO_TRACKS 5

enum {MENU_AUDIO,SLOW_AUDIO,NORMAL_AUDIO,FAST_AUDIO,GAME_OVER_AUDIO};

typedef struct {
     /// music pointers 
    ALLEGRO_SAMPLE *audio_samples[CANT_AUDIO_TRACKS];
    ALLEGRO_SAMPLE_INSTANCE *audio_instances[CANT_AUDIO_TRACKS];
    const char* pt2str[CANT_AUDIO_TRACKS];
    
    
}music_vars_t;


void al_audio_init(music_vars_t * music);

void handle_audio(full_graphic_content* content, music_vars_t * music);

void reset_fsm(music_vars_t* music, int *p2state);

void destroy_music_vars(music_vars_t *music);

#endif /* SOUND_H */

