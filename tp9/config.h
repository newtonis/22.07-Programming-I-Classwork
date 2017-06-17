/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   config.h
 * Author: newtonis
 *
 * Created on May 27, 2017, 9:18 PM
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define BASE_FONT "fonts/isocpeur.ttf"
#define BASE_SIZE 50
#define SCREEN_W 1000
#define SCREEN_H 800
    
#define FPS 60.0
#define GAME_TIME 5
#define MAX_NUMBER 10
    
#define CENTER_X 460
#define CENTER_Y 430
#define TRIANGLE_SIZE 600
    
#define DEFAULT_DIRECTION 180  
    
#define DEFAULT_RED 0
#define DEFAULT_BLUE 0.3f
#define DEFAULT_GREEN 0.3f

#define DEFAULT_TOL 2.0
#define DEFAULT_CNT_FRACT 5
    
#define MIN_TOL 0
#define MAX_TOL 200
#define MAX_COMPUTED_LVL 6
    
#define DEF_SZ 50 // default auxiliar text size
    
#define FREQ_FRACTAL 1 // seconds
    
#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H */

