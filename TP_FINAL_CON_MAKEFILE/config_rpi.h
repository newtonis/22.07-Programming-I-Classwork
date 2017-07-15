#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <time.h>
#include "termlib.h"
#include "joydrv.h"
#include "disdrv.h"

#define MAX_DISP 16
#define MAX_MODES 3

enum {FALSE , TRUE};
enum GAME_STATES {START, MENU , INIT_GAME, PLAY, END};
enum LED_STATES {BLINK_OFF , BLINK_ON};
enum DIFICULTIES {EASY, MED, HARD};

typedef struct {
    int number;
    int status;
    
} disp_fragment_t;

typedef struct {
    int status; // Fsm status
    int switch_flag; // Switch flag
    int joy_flag; // Joy coord flag
    int mode; // Difficult mode
    int snake_status; // Snake actual status
    int direction; // Snake direction
    jcoord_t joy_coordinates1; // Joy Coordenates
    jswitch_t joy_switch1; // Joy Switch
    disp_fragment_t num_frag[MAX_MODES]; // Numbers of difficulties
    
} game_control_t;

typedef struct {
    clock_t start; // Start time when init
    clock_t end;   // End for update time
    clock_t total; // Total time for update display
} time_blink_t;

#endif /* CONFIG_H */

