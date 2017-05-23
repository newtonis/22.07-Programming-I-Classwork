#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include <stdint.h>

// PORT STRUCTURE //

/// un puerto esta compuesto por su direccion

typedef struct{
	char name;
	uint16_t *dir;
	int sz; // can be, 8 or 16 bits
} port_t;

typedef struct{
	port_t A;
	port_t B;
	port_t D;
} microPorts_t;


// PORT FUNCTIONS //
// ------------- //

int initPorts(microPorts_t* mp); // initializate all port structure
void end_ports(microPorts_t* mp); //free ports memory


void bitSet(port_t *port, uint16_t bit);
void bitClr(port_t *port, uint16_t bit);
int bitGet(port_t *port, uint16_t bit);

void maskOn(port_t *port, uint16_t mask);
void maskOff(port_t *port, uint16_t mask);
void maskToggle(port_t *port, uint16_t mask);


#endif
