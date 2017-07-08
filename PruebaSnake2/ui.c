#include "ui.h"
#include "config.h"
#include "utils.h"
#include <math.h>

#define SIZE_DISTANCE 40



//// Create a dynamic button with two surfaces (one for each state)
button_t *init_button( ALLEGRO_BITMAP* surface_a , ALLEGRO_BITMAP* surface_b ,cursor_handler_t* cursor ,int x ,int y ){ /// create a dinamic button
    button_t *new_button = malloc(sizeof(button_t));
    new_button->x = x; 
    new_button->y = y;
    new_button->w = al_get_bitmap_width(surface_a);
    new_button->h = al_get_bitmap_height(surface_a);
    new_button->cursor = cursor;
    new_button->surface_a = surface_a;
    new_button->surface_b = surface_b;
    
    new_button->status = RELEASE;
    return new_button;
}
void update_button_position(button_t* button, int x,int y){
    button->x = x;
    button->y = y;
}
void draw_button(button_t* button){
    if (button->status == RELEASE){     
        al_draw_bitmap(button->surface_a , button->x - button->w / 2 , button->y - button->h / 2 , 0);
    }else if(button->status == HOLD){
        set_current_cursor(button->cursor,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(button->surface_b , button->x - button->w / 2, button->y - button->h / 2, 0);
    }
}
int update_button(button_t* button){
    ALLEGRO_MOUSE_STATE press;
    al_get_mouse_state(&press);
    int mx = press.x;
    int my = press.y;
    int status = al_mouse_button_down(&press,1);
    
    int ans = 0;
    if (mx > button->x - button->w/2 && mx < button->x + button->w/2 && my > button->y - button->h/2 && my < button->y + button->h/2){
        
        button->status = HOLD;
        if (status){
            ans = 1;
        }
    }else{
        button->status = RELEASE;
    }
    
    return ans;
}
void destroy_button(button_t* button){
    free(button);
}

reg_box_t *init_reg_box(ALLEGRO_BITMAP* surfaces[] ,cursor_handler_t* cursor,ALLEGRO_FONT* font,int x,int y,int default_value,int min_value,int max_value){
    
    reg_box_t *new_box = malloc(sizeof(reg_box_t));
    new_box->up = init_button(surfaces[0],surfaces[1],cursor,x , y - SIZE_DISTANCE);
    new_box->down = init_button(surfaces[2],surfaces[3],cursor,x,y + SIZE_DISTANCE);
    
    new_box->font = font;
    new_box->value = default_value;
    new_box->min_value = min_value;
    new_box->max_value = max_value;
    
    new_box->x = x;
    new_box->y = y;
    new_box->flag_down = 0;
    new_box->flag_up = 0;
    
    return new_box;
}
void update_reg_box_position(reg_box_t* reg_box,int x,int y){
    reg_box->x = x;
    reg_box->y = y;
    update_button_position(reg_box->up  ,x,y-SIZE_DISTANCE);
    update_button_position(reg_box->down,x,y+SIZE_DISTANCE);
}
void update_reg_box(reg_box_t *reg_box){
    int up_status   = update_button(reg_box->up);
    int down_status = update_button(reg_box->down);
    if (!up_status) reg_box->flag_up = 0;
    if (!down_status) reg_box->flag_down = 0;
    
    if (up_status && !reg_box->flag_up){
        reg_box->flag_up = 1;
        reg_box->value ++;
    }
    if (down_status && !reg_box->flag_down){
        reg_box->flag_down = 1;
        reg_box->value --;
    }
    /// make value respect min and max
    reg_box->value = fix_value(reg_box->value , reg_box->min_value , reg_box->max_value);
}
void draw_reg_box(reg_box_t *reg_box){
   
    draw_button(reg_box->up);
    draw_button(reg_box->down);
    
    char str[DEF_ARR_SZ];
    
    int_to_str(reg_box->value,str);
    al_draw_text(reg_box->font,BOX_COLOR,reg_box->x,reg_box->y-DEF_SZ/2,ALLEGRO_ALIGN_CENTER,str);
}
void destroy_reg_box(reg_box_t *reg_box){
    destroy_button(reg_box->up);
    destroy_button( reg_box->down );
            
}
cursor_handler_t* init_cursor_handler(ALLEGRO_DISPLAY *display){
    cursor_handler_t * cursor_handler = malloc(sizeof(cursor_handler_t));
    cursor_handler->display_ref = display;
    cursor_handler->default_cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT;
    cursor_handler->next_cursor = cursor_handler->default_cursor;
    return cursor_handler;
}
void set_current_cursor(cursor_handler_t* handler, ALLEGRO_SYSTEM_MOUSE_CURSOR cursor){
    handler->next_cursor = cursor;
}
void update_display_cursor(cursor_handler_t* handler){
    if (handler->next_cursor != handler->default_cursor){
        al_set_system_mouse_cursor(handler->display_ref, handler->next_cursor);
        handler->next_cursor = handler->default_cursor; // we need another call in next iteration to change cursor
    }
}
void destroy_handler(cursor_handler_t* cursor){
    free(cursor);
}

show_text_t * init_show_text(const char *text,ALLEGRO_COLOR color,ALLEGRO_FONT* font,int x,int y){
    show_text_t *new_text = malloc(sizeof(show_text_t));
    new_text->x = x;
    new_text->y = y;
    new_text->color = color;
    new_text->font = font;
    new_text->text = text;
}
void draw_show_text(show_text_t* show_text){
    al_draw_text(show_text->font,show_text->color,show_text->x,show_text->y,ALLEGRO_ALIGN_CENTER,show_text->text);
}
void destroy_text(show_text_t* text){
    free(text);
}
void update_show_text_position(show_text_t* show_text,int x,int y){
    show_text->x = x;
    show_text->y = y;
}