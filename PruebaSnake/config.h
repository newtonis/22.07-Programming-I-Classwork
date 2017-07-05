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
#define WORLD_MIN_LEFT 0

#define MOVE_RATE 32.0
#define MOVE_FREQ 3
#define NO_KEY -1

#define DIR_OK -1
#define DIR_ERR -2



#endif /* CONFIG_H */

