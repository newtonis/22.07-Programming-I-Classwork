#ifndef CONFIG_H
#define CONFIG_H

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT //arrow keys
};

enum {FALSE, TRUE};

// Seccion que se modifica segun sea allegro o la rpi 
// ---------------------------
#define CUADRADITO_SIZE	32
#define SCREEN_W 640
#define SCREEN_H 480
// ---------------------------

#define WORLD_TOP 0
#define WORLD_BOTTOM SCREEN_H
#define WORLD_MAX_RIGHT SCREEN_W

#define MIN_DIFF 1
#define MAX_DIFF 10

#define WORLD_MIN_LEFT 0

#define MOVE_RATE 32.0
#define MOVE_FREQ 3
#define NO_KEY -1

#define DIR_OK -1
#define DIR_ERR -2

#define FPS_A 20.0
#define FPS_B 60.0

#define MOVE_KEYS 4
#define MAX_LENGTH 100

#define BACKGROUND_COLOR al_map_rgb(0,0,50)
#define BOX_COLOR al_map_rgb(255,255,255)

#define START_BUTTON_CORR 100

#define FONT_SIZE_A 30
#define FONT_SIZE_B 100

#define DEF_SZ 20
#define DEF_ARR_SZ 10

#define MIN_TABLE_WIDTH 3
#define MAX_TABLE_WIDTH 20

#define MIN_TABLE_HEIGHT 3
#define MAX_TABLE_HEIGHT 50

#define TEXT_CONF_DISTANCE 100
#define GAME_TITLE_TEXT "SNAKE"
#define TITLE_DISTANCE_Y 20 

#define MAP_SIZE_TEXT "map size"

#define DIFF_TEXT "level"

#endif /* CONFIG_H */

