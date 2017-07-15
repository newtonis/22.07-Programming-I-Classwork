#ifndef CONFIG_H
#define CONFIG_H


enum {FALSE, TRUE};

// Seccion que se modifica segun sea allegro o la rpi 
// ---------------------------
#define CUADRADITO_SIZE	1
#define SCREEN_W 640
#define SCREEN_H 480
// ---------------------------

#define WORLD_TOP 0
#define WORLD_BOTTOM 10
#define WORLD_MAX_RIGHT 10

#define MIN_DIFF 1
#define MAX_DIFF 3

#define WORLD_MIN_LEFT 0

#define MOVE_RATE 32.0
#define MOVE_FREQ 3
#define NO_KEY -1

#define DIR_OK -1
#define DIR_ERR -2

#define FPS_A 100.0
#define FPS_B 30.0

#define MOVE_KEYS 4

#define BACKGROUND_COLOR al_map_rgb(0,0,50)
#define BOX_COLOR al_map_rgb(255,255,255)
#define SNAKE_COLOR al_map_rgb(255,100,100)
#define FOOD_COLOR al_map_rgb(100,255,255)
#define LIGHT_BOX_COLOR al_map_rgb(100,100,100)
#define GAME_OVER_COLOR al_map_rgb(200,200,255)
#define BORDER_COLOR al_map_rgb(100,100,255)

#define START_BUTTON_CORR 100


#define FONT_SIZE_A 30
#define FONT_SIZE_B 100
#define FONT_SIZE_C 60
#define FONT_SIZE_D 120

#define DEF_SZ 20
#define DEF_ARR_SZ 10

#define MIN_TABLE_WIDTH 3
#define MAX_TABLE_WIDTH 50

#define MIN_TABLE_HEIGHT 3
#define MAX_TABLE_HEIGHT 30

#define TEXT_CONF_DISTANCE 100
#define GAME_TITLE_TEXT "SNAKE"
#define TITLE_DISTANCE_Y 20 

#define DISTANCE_SCOREBOARD_Y 50
#define DISTANCE_SCOREBOARD_X 150
#define DISTANCE_HIGHSCORE_X 200
#define DISTANCE_NUMBER_HIGHSCORE 250

#define MAP_SIZE_TEXT "map size"

#define DIFF_TEXT "level"


#define DEFAULT_DIFFICULTY 2
#define DEFAULT_WIDTH 20
#define DEFAULT_HEIGHT 15

#define SCORE_NUMBERS 3

#define BLINK_TIME 0.8
#define TOTAL_PERIOD_TIME 1.0

#define BORDER_SIZE 10
#endif /* CONFIG_H */

