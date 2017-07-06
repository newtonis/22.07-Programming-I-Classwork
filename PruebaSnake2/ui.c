#include "ui.h"
#include "config.h"
#include "utils.h"

#define SIZE_DISTANCE 40

/**** Create a dynamic button with two surfaces (one for each state) ****/
button_t *init_button( ALLEGRO_BITMAP* surface_a , ALLEGRO_BITMAP* surface_b , int x ,int y ){ /// create a dinamic button
    button_t *new_button = malloc(sizeof(button_t));
    new_button->x = x; 
    new_button->y = y;
    new_button->w = al_get_bitmap_width(surface_a);
    new_button->h = al_get_bitmap_height(surface_a);

    new_button->surface_a = surface_a;
    new_button->surface_b = surface_b;
    
    new_button->status = RELEASE;
    return new_button;
}

void draw_button(button_t* button){
    if (button->status == RELEASE){
        al_draw_bitmap(button->surface_a , button->x - button->w / 2 , button->y - button->h / 2 , 0);
    }else if(button->status == HOLD){
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

reg_box_t *init_reg_box(ALLEGRO_BITMAP* surface_a , ALLEGRO_BITMAP* surface_b,ALLEGRO_FONT* font,int x,int y,int default_value,int size){
    reg_box_t *new_box = malloc(sizeof(reg_box_t));
    new_box->up = init_button(surface_a,surface_a,x , y + SIZE_DISTANCE);
    new_box->down = init_button(surface_b,surface_b,x,y - SIZE_DISTANCE);
    
    new_box->value = default_value;
    new_box->text_size = size;
    new_box->font = font;
    new_box->x = x;
    new_box->y = y;
    
    return new_box;
}
void update_reg_box(reg_box_t *reg_box){
    int up_status   = update_button(reg_box->up);
    int down_status = update_button(reg_box->down);
}
void draw_reg_box(reg_box_t *reg_box){
    draw_button(reg_box->up);
    draw_button(reg_box->down);
    
    char str[DEF_SZ];
    
    int_to_str(reg_box->value,str);
    al_draw_text(reg_box->font,BOX_COLOR,reg_box->x,reg_box->y-DEF_SZ/2,ALLEGRO_ALIGN_CENTER,str);
}
void destroy_reg_box(reg_box_t *reg_box){
    destroy_button(reg_box->up);
    destroy_button( reg_box->down );
            
}