////////////////////////
// PORT UTILS LIBRARY //
// ================== ///////////////
// Port structures, common defines //
// and bit editing functions.      //
/////////////////////////////////////
#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include <stdint.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define INPUT_ERR -1
#define INPUT_BIT -2
#define ALL_BITS_MASK 0xFF

enum {FALSE, TRUE};
// PORT STRUCTURE //
// -------------- //
/// A port has a direction 

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
// -------------- //

// PORT FUNCTIONS //
// -------------- //

static void initReg(port_t* port , uint16_t *dir, char name , int sz);

int initPorts(microPorts_t* mp); // initializate all port structure
void endPorts(microPorts_t* mp); // free ports memory

int portConfig(port_t *port, char c);

// The following functions recive a pointer to the port and the
// bit or the mask to configure.
void bitSet(port_t *port, uint16_t bit);
void bitClr(port_t *port, uint16_t bit);
int bitGet(port_t *port, uint16_t bit);

void maskOn(port_t *port, uint16_t mask);
void maskOff(port_t *port, uint16_t mask);
void maskToggle(port_t *port, uint16_t mask);
// -------------- //

#endif
