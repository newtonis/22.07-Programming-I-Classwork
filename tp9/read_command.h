/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   read_command.h
 * Author: newtonis
 *
 * Created on June 16, 2017, 10:20 PM
 */

#ifndef READ_COMMAND_H
#define READ_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "front_end.h"
    
int read_input(int argc,char *argv[] , shared_vars_t* shared_vars);

#ifdef __cplusplus
}
#endif

#endif /* READ_COMMAND_H */

