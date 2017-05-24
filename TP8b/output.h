#ifndef OUTPUT_H
#define OUTPUT_H

#include "port_utils.h"

void showPort(port_t *port);

void instruction_print(void);

void portSel_print(void);

void bitConfig_print(char port);

void initError_print(void);

#endif // OUTPUT_H