#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>

// PORT STRUCTURE //



typedef union{
	uint16_t D;
	struct{
		uint8_t B;
		uint8_t A;
	} Dbytes;
} port_t;


// PORT FUNCTIONS //
// ------------- //
void bitSet(port_t *port, int bit);
void bitClr(port_t *port, int bit);
int bitGet(port_t *port, int bit);

void maskOn(port_t *port, int mask);
void maskOff(port_t *port, int mask);
void maskToggle(port_t *port, int mask);
// ------------- //