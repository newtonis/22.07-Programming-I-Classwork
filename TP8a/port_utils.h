#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>

// PORT STRUCTURE //

/// un puerto esta compuesto por su direccion

typedef struct{
	uint16_t *dir;
} port_t;

typedef struct{
	port_t A;
	port_t B;
	port_t D;
} microPorts_t;


// PORT FUNCTIONS //
// ------------- //

void init_ports(microPorts* mp); // initializate all port structure

void bitSet(port_t *port, int bit);
void bitClr(port_t *port, int bit);
int bitGet(port_t *port, int bit);

void maskOn(port_t *port, int mask);
void maskOff(port_t *port, int mask);
void maskToggle(port_t *port, int mask);
// ------------- //