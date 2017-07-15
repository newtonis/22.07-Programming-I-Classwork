#include "rpi_hard.h"
#include "disp_msgs.h"
#include "snake_logic.h"

#define MODE_MSG 3
#define Y_TAB 2
#define CALL_TIME 0.5f

#define TEXT_FINISH 2

// inc_part: increments text part
static void inc_part(void);

// read_part: returns actual part
static int read_part(void);

// reset_part: resets to initial part value
static void reset_part(void);

// inc_column: increments message part
static void inc_column(void);

// read_column: returns actual column processing
static int read_column(void);

// reset_column: resets to initial part value
static void reset_column(void);

enum numbers {N_ONE, N_TWO, N_THREE};

static int part = ONE;
static int column = LINE_START;

static char *pNum[TEN+1]={&num0_txt[0][0],
                          &num1_txt[0][0],
                          &num2_txt[0][0],
                          &num3_txt[0][0],
                          &num4_txt[0][0],
                          &num5_txt[0][0],
                          &num6_txt[0][0],
                          &num7_txt[0][0],
                          &num8_txt[0][0],
                          &num9_txt[0][0]};

void clear_matrix(char disp[MAX_DISP][MAX_DISP]){
    int i,j;
    for(i = 0; i < MAX_DISP; i++){
        for(j = 0; j < MAX_DISP; j++){
            disp[i][j] = POINT_OFF;
        }
    }
}

void hard_initialize(void){
    
    clrscr();                   //Termlib Clear Screen (see termlib.h for more info)		
    joy_init();                 // Initialize Joystick Hardware
    display_init();             // Initialize Display Hardware 
    set_joy_axis(JOY_ROTATE);	// Set joystick axis orientaton  
    set_display_axis(NORMAL);	// Set display axis orientation 
    set_joy_direction(J_INV_TRUE,J_INV_TRUE); // Invert both x and y joystick axis direction
    
    // end of init
}

void turn_leds(char mat[MAX_DISP][MAX_DISP], char point, int operation){
    int i,j;
    for(i = 0; i < MAX_DISP; i++){
        for(j = 0; j < MAX_DISP; j++){
            if((mat[i][j]) == point){
            	display_write(i,j,operation);
            }
        }
    }
}

void turn_half_leds(char mat[MAX_DISP][MAX_DISP], char point, int operation){
    int i,j;
    for(i = 0; i < (MAX_DISP/2); i++){
        for(j = 0; j < MAX_DISP; j++){
            if((mat[i][j]) == point){
            	display_write(i,j,operation);
            }
        }
    }
}

int shift_text(char *pText, char aux_mat[MAX_DISP][MAX_DISP], int line_w){

    int i;
    
    turn_half_leds(aux_mat, POINT_ON, D_OFF);

    shift_mat_left(aux_mat); // shift previus data
    for(i = 0; i < LETTER_H; i++){ // copy new column data
        aux_mat[i + Y_TAB][MAX_DISP-1] = *(pText + (i*line_w) + read_column());

    }
    turn_leds(aux_mat, POINT_ON, D_ON);
    inc_column();

   
    if(read_column() == line_w){
        reset_column();
        return TEXT_FINISH;
    }
    
    else{
        return 0;
    }
}

void print_welcome(int highscore){
    static int txt_w;
    static int num_c = 0;
    static int num_d = 0;
    static int num_u = 0;
    static char *pMsg;
    int text_status;
    
    switch (read_part()){
        case (ONE):
            txt_w = (sizeof(snake_txt))/LETTER_H; // line with
            pMsg = &snake_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;
        case (TWO):
            txt_w = (sizeof(space_txt))/LETTER_H; // line with
            pMsg = &space_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;
        case (THREE):
            txt_w = (sizeof(high_txt))/LETTER_H; // line with
            pMsg = &high_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;
        case (FOUR):
            txt_w = (sizeof(score_txt))/LETTER_H; // line with
            pMsg = &score_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;           
        case (FIVE):
            num_c = highscore/100;
            num_d = (highscore%100)/10;
            num_u = (highscore%100)%10;
            text_status = shift_text(pNum[num_c], push_msg, NUM_W);
            break;
        case (SIX):
            text_status = shift_text(pNum[num_d], push_msg, NUM_W);
            break;
        case (SEVEN):
            text_status = shift_text(pNum[num_u], push_msg, NUM_W);
            break;
        case (EIGHT):
            txt_w = (sizeof(space_txt))/LETTER_H; // line with
            pMsg = &space_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;       
        case (NINE):
            txt_w = (sizeof(press_txt))/LETTER_H; // line with
            pMsg = &press_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;    
        case (TEN):
            txt_w = (sizeof(to_txt))/LETTER_H; // line with
            pMsg = &to_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;
        case (ELEVEN):
            txt_w = (sizeof(start_txt))/LETTER_H; // line with
            pMsg = &start_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;           
        case (TWELVE): 
            txt_w = (sizeof(space_txt))/LETTER_H; // line with
            pMsg = &space_txt[0][0];
            text_status = shift_text(pMsg, push_msg, txt_w);
            break;             
    }
    
    
    display_update(); 
    
    if(text_status == TEXT_FINISH){
        inc_part();
        if(read_part() == THIRTEEN){
            reset_part();
        }
    }
}

void print_score(int points){
    static int txt_w = 0;
    int text_stat = 0;
    static int num_c;
    static int num_d;
    static int num_u;
    static char *pMsg;

    
    switch (read_part()){
        case (ONE):
            txt_w = (sizeof(game_txt))/LETTER_H; // line with
            pMsg = &game_txt[0][0];
            text_stat = shift_text(pMsg, end_msg, txt_w);
            break;
        case (TWO):
            txt_w = (sizeof(over_txt))/LETTER_H; // line with
            pMsg = &over_txt[0][0];
            text_stat = shift_text(pMsg, end_msg, txt_w);
            break;
        case (THREE):
            txt_w = (sizeof(space_txt))/LETTER_H; // line with
            pMsg = &space_txt[0][0];
            text_stat = shift_text(pMsg, end_msg, txt_w);
            break;
        case (FOUR):
            txt_w = (sizeof(score_txt))/LETTER_H; // line with
            pMsg = &score_txt[0][0];
            text_stat = shift_text(pMsg, end_msg, txt_w);
            break; 
        case (FIVE):
            num_c = points/100;
            num_d = (points%100)/10;
            num_u = (points%100)%10;
            text_stat = shift_text(pNum[num_c], end_msg, NUM_W);
            break;
        case (SIX):
            text_stat = shift_text(pNum[num_d], end_msg, NUM_W);
            break;
        case (SEVEN):
            text_stat = shift_text(pNum[num_u], end_msg, NUM_W);
            break;
        case (EIGHT):
            txt_w = (sizeof(space_txt))/LETTER_H; // line with
            pMsg = &space_txt[0][0];
            text_stat = shift_text(pMsg, end_msg, txt_w);
            break;
    }
    display_update();
    
    if(text_stat == TEXT_FINISH){
        inc_part();
        if(read_part() == NINE){
            reset_part();
        }
    } 
}

void shift_mat_left(char mat[MAX_DISP][MAX_DISP]){
    int i,j;
    for(i = 0; i < (MAX_DISP/2); i++){
        for(j = 1; j < MAX_DISP; j++){
            mat[i][j-1] = mat[i][j];
        }
    }
}

void copy_mat(char source[MAX_DISP][MAX_DISP],char destiny[MAX_DISP][MAX_DISP]){
    int i,j;
    for(i=0;i<MAX_DISP; i++){
        for(j=0;j<MAX_DISP; j++){
            destiny[i][j]=source[i][j];
        }
    }
}

void refresh_joy(game_control_t *pControl){
    joystick_update(); // Read joystick Hardware
    pControl->joy_switch1 = joystick_get_switch_value(); // get switch status
    pControl->joy_coordinates1 = joystick_get_coord(); // And get coordenates value
}


void update_menu_op(disp_fragment_t who_blinks[]){
    static int p = 0;
    static int txt_w;
    static char* pMsg;
    int l, i, j, text_stat;
    
    switch (read_part()){
        case (ONE):
            txt_w = (sizeof(choose_txt))/LETTER_H; // line with
            pMsg = &choose_txt[0][0];
            text_stat = shift_text(pMsg, basic_disp, txt_w);
            break;
        case (TWO):
            txt_w = (sizeof(game_txt))/LETTER_H; // line with
            pMsg = &game_txt[0][0];
            text_stat = shift_text(pMsg, basic_disp, txt_w);
            break;
        case (THREE):
            txt_w = (sizeof(dificult_txt))/LETTER_H; // line with
            pMsg = &dificult_txt[0][0];
            text_stat = shift_text(pMsg, basic_disp, txt_w);
            break;
        case (FOUR):
            txt_w = (sizeof(space_txt))/LETTER_H; // line with
            pMsg = &space_txt[0][0];
            text_stat = shift_text(pMsg, basic_disp, txt_w);            
    }
    
    if(text_stat == TEXT_FINISH){
        inc_part();
        if(read_part() == FIVE){
            reset_part();
        }
    }
    
    for(l = 0; l < MAX_MODES; l++){
        if(who_blinks[l].status == BLINK_ON){

            if(p%2 == 0){
            
                switch(who_blinks[l].number){
                    case N_ONE:
                        turn_leds(num1_msg, POINT_ON, D_OFF);
                        break;
                    case N_TWO:
                        turn_leds(num2_msg, POINT_ON, D_OFF);
                        break;
                    case N_THREE:
                        turn_leds(num3_msg, POINT_ON, D_OFF);
                        break;
                }
                
                p++;
            }
            else{
                turn_leds(num1_msg, POINT_ON, D_ON);
                turn_leds(num2_msg, POINT_ON, D_ON);
                turn_leds(num3_msg, POINT_ON, D_ON);
                p++;
            }

        }
    }
    
    display_update();

}

void inc_part(void){
    part++;
}

int read_part(void){
    return part;
}

void reset_part(void){
    part = ONE;
}

void inc_column(void){
    column++;
}

int read_column(void){
    return column;
}

void reset_column(void){
    column = LINE_START;
}

void reset_txt_fsm(void){
    reset_part();
    reset_column();
    turn_half_leds(push_msg, POINT_ON, D_OFF);
    turn_half_leds(end_msg, POINT_ON, D_OFF);
    turn_half_leds(basic_disp, POINT_ON, D_OFF);
}

void set_config_data(logic_vars_t *pLogic, game_control_t *pControl){
    set_snake_game_size(pLogic, MAX_DISP, MAX_DISP);
    set_game_difficulty(pLogic, (pControl->mode)+1);
    set_logic_call_time(pLogic, CALL_TIME);

}