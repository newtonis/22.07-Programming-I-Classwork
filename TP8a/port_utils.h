#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include <stdint.h>


#define INPUT_ERR -1
#define INPUT_BIT -2
#define ALL_BITS_MASK 0xFF
#define MASK_ON 0x05 // default mask in 16 bits
#define MASK_OFF 0x06 // default mask in 16 bits
#define MASK_TOGGLE 0x0A // default mask in 16 bits

#define EXIT 'e'

enum {FALSE, TRUE};
enum{NOT_VALID, VALID};

// PORT STRUCTURE //

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


// PORT FUNCTIONS //
// ------------- //

static void initReg(port_t* port , uint16_t *dir, char name , int sz);

char get_input(void); // gets user input, only one char, otherwise returns INPUT_ERR
int get_number(void); // gets user inpur number of bit, otherwise returns INPUT_ERR

int maskvalid(port_t *port, int random_mask);

int initPorts(microPorts_t* mp); // initializate all port structure
void endPorts(microPorts_t* mp); // free ports memory

int portConfig(port_t *port, char c);
int bit_setup(port_t *port, char c, char port_letter);

void bitSet(port_t *port, uint16_t bit);
void bitClr(port_t *port, uint16_t bit);
int bitGet(port_t *port, uint16_t bit);

void maskOn(port_t *port, uint16_t mask);
void maskOff(port_t *port, uint16_t mask);
void maskToggle(port_t *port, uint16_t mask);


#endif
