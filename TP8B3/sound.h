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
#include "front_end.h"
    
int fe_init_audio(graphic_vars_t* vars);
void fe_end_audio(graphic_vars_t * vars);
   

   

#ifdef __cplusplus
}
#endif

#endif /* SOUND_H */
