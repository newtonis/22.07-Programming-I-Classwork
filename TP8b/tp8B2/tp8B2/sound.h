/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sound.h
 * Author: j
 *
 * Created on May 28, 2017, 8:50 PM
 */

#ifndef SOUND_H
#define SOUND_H

#ifdef __cplusplus
extern "C" {
#endif  
#include <stdio.h>
    #include <allegro5/allegro5.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>

    
   int init_audio(void);
   void fe_end_audio(void);
   
   ALLEGRO_SAMPLE *win_audio;
   ALLEGRO_SAMPLE *lose_audio;
   ALLEGRO_SAMPLE *loop_audio;
   ALLEGRO_SAMPLE_INSTANCE *instance1;
   ALLEGRO_SAMPLE_INSTANCE *instance2;
   ALLEGRO_SAMPLE_INSTANCE *instance3;
   

#ifdef __cplusplus
}
#endif

#endif /* SOUND_H */
