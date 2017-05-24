#ifndef INPUT_H
#define INPUT_H

#include "port_utils.h"
enum {NORMAL , BLINK };

void userInput(microPorts_t *mp,int *end,int *mode,long time);
static void fsmUpdate(int *mode,microPorts_t *mp,long time);

#endif