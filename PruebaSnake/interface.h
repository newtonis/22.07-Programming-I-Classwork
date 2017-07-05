/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   interface.h
 * Author: sissi
 *
 * Created on July 5, 2017, 11:11 AM
 */

#ifndef INTERFACE_H
#define INTERFACE_H


#include "snake_logic.h"    
    
    
typedef struct { //// The game is defined by the pointers in this structure
    snake_node_t *pSnake;
    food_t *pFood;
    
}logic_vars;



#ifdef __cplusplus
}
#endif

#endif /* INTERFACE_H */

