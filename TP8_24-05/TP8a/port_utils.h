////////////////////////
// PORT UTILS LIBRARY //
// ================== ///////////////
// Port structures, common defines //
// and bit editing functions.      //
/////////////////////////////////////
#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include <stdint.h>

// COMMON DEFINES //
// -------------- //
#define INPUT_ERR -1 // input error
#define INPUT_BIT -2 
#define ALL_BITS_MASK 0xFF
#define MASK_ON 0x05 		// default mask ON in 16 bits
#define MASK_OFF 0x06 		// default mask OFF in 16 bits
#define MASK_TOGGLE 0x0A 	// default mask TOGGLE in 16 bits

#define EXIT 'e' // char for terminate program 

enum {FALSE, TRUE};
enum{NOT_VALID, VALID};
// -------------- //

// PORT STRUCTURE //
// -------------- //
/// A port has a direction asigned
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
// initReg: inits port structure fields
// 	Input: pointer to port, pointer to dir field, letter name of the port,
//         size of the port (8 or 16 bits)
//  Output: (none)
static void initReg(port_t* port , uint16_t *dir, char name , int sz);

// get_input: gets user input, only one char, otherwise returns INPUT_ERR
// 	Input: (none)
//  Output: char with port letter
char get_input(void);

// get_input: gets user inpur number of bit, otherwise returns INPUT_ERR
// 	Input: (none)
//  Output: integer with number > 0 
int get_number(void); 

// initPorts: initializate all port structure
// 	Input: pointer to ports struct
//  Output: 0 if malloc fails,, 1 if init ok
int initPorts(microPorts_t* mp); 

// endPorts: free ports memory when program finishes
// 	Input: pointer to ports struct
//  Output: (none)
void endPorts(microPorts_t* mp); // free ports memory

// bit_setup: 
// 	Input: pointer to port, option selected, char letter of the port
//  Output: int with 1 if config ok or 0 if error
int bit_setup(port_t *port, char c, char port_letter);

// bitSet: sets to 1 a bit of the port
// 	Input: pointer to port, bit to set
//  Output: (none)
void bitSet(port_t *port, uint16_t bit);

// bitClr: clears to 0 a bit of the port
// 	Input: pointer to port, bit to clear
//  Output: (none)
void bitClr(port_t *port, uint16_t bit);

// bitGet: gets status of a port bit
// 	Input: pointer to port, bit to read
//  Output: state (0 or 1)
int bitGet(port_t *port, uint16_t bit);

// maskOn: sets the port bits correspondig to the marked in the mask 
// 	Input: pointer to port, mask in hex
//  Output: (none)
void maskOn(port_t *port, uint16_t mask);

// maskOff: clears the port bits correspondig to the marked in the mask 
// 	Input: pointer to port, mask in hex
//  Output: (none)
void maskOff(port_t *port, uint16_t mask);

// maskToggle: toggles the port bits correspondig to the marked in the mask 
// 	Input: pointer to port, mask in hex
//  Output: (none)
void maskToggle(port_t *port, uint16_t mask);

// -------------- //

#endif
